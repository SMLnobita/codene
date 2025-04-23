#!/bin/bash
set -e

STAGE3_URL="https://www.dropbox.com/scl/fi/pth68tuk3ozuq1l4nj1zk/stage3-amd64-desktop-systemd-20250420T121009Z.tar.xz?rlkey=nkcgqjqqxyicz736suuhuiamt&st=82ulje4b&dl=1"

echo "[1/9] ⚠️ XÓA & chia lại phân vùng /dev/sda..."
sleep 3
sfdisk /dev/sda <<EOF
label: dos
device: /dev/sda
unit: sectors

/dev/sda1 : start=2048, size=+512M, type=83, bootable
/dev/sda2 : size=+4G, type=82
/dev/sda3 : type=83
EOF

sleep 3 && partprobe /dev/sda || true && sleep 2

echo "[2/9] Format các phân vùng..."
mkfs.ext4 /dev/sda1
mkfs.ext4 /dev/sda3
mkswap /dev/sda2 && swapon /dev/sda2

echo "[3/9] Mount root & boot..."
mount /dev/sda3 /mnt/gentoo
mkdir -p /mnt/gentoo/boot
mount /dev/sda1 /mnt/gentoo/boot

echo "[4/9] Tải & giải nén stage3..."
cd /mnt/gentoo
wget "$STAGE3_URL" -O stage3.tar.xz
tar xpvf stage3.tar.xz --xattrs-include='*.*' --numeric-owner

echo "[5/9] Mount chroot env..."
cp --dereference /etc/resolv.conf /mnt/gentoo/etc/
mount -t proc /proc /mnt/gentoo/proc
mount --rbind /sys /mnt/gentoo/sys
mount --rbind /dev /mnt/gentoo/dev

echo "[6/9] Ghi script cài GNOME vào chroot..."
cat > /mnt/gentoo/root/install-gnome.sh <<'EOF2'
#!/bin/bash
set -e

emerge-webrsync
emerge --sync

eselect profile set $(eselect profile list | grep -m1 'gnome.*systemd' | awk '{print $1}' | tr -d '[]')

CORES=$(nproc)
echo 'ACCEPT_LICENSE="*"' >> /etc/portage/make.conf
cat >> /etc/portage/make.conf <<EOF
CFLAGS="-march=native -O2 -pipe"
CXXFLAGS="\${CFLAGS}"
MAKEOPTS="-j$((CORES + 1))"
USE="X gnome gtk introspection pulseaudio dbus policykit udev bluetooth systemd pipewire ffmpeg extra vlc -qt5 -kde"
EOF

# ✅ FIX vòng lặp phụ thuộc giữa ffmpeg ↔ pipewire ↔ libsdl2
mkdir -p /etc/portage/package.use
echo "media-video/pipewire -ffmpeg" >> /etc/portage/package.use/pipewire
echo "media-video/ffmpeg -pipewire" >> /etc/portage/package.use/ffmpeg

emerge --verbose --yes gentoo-sources genkernel grub vim sudo eix
emerge --verbose --yes sys-kernel/linux-firmware
genkernel all

emerge --verbose --yes gnome gdm firefox networkmanager alsa-utils \
  gnome-extra/gnome-tweaks gnome-extra/gnome-shell-extensions \
  gnome-base/gvfs sys-fs/udisks sys-fs/udisks:2 \
  www-plugins/chrome-gnome-shell gnome-extra/nm-applet \
  media-video/pipewire media-video/wireplumber \
  media-plugins/pipewire-alsa media-plugins/pipewire-pulse \
  sys-apps/flatpak media-sound/pavucontrol \
  media-fonts/noto media-video/vlc app-misc/neofetch \
  app-arch/unzip app-arch/p7zip app-arch/unrar \
  media-gfx/flameshot gnome-extra/gthumb x11-misc/clipman

flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install -y flathub com.github.tchx84.Flatseal

echo "gentoo-vm" > /etc/hostname
cat > /etc/fstab <<EOF
/dev/sda1  /boot     ext4  defaults  0 2
/dev/sda3  /         ext4  noatime   0 1
/dev/sda2  none      swap  sw        0 0
EOF

grub-install /dev/sda
grub-mkconfig -o /boot/grub/grub.cfg
systemctl enable NetworkManager
systemctl enable gdm

passwd
useradd -m -G users,wheel,audio,video,plugdev -s /bin/bash nguyenhoa
passwd nguyenhoa
sed -i 's/^# %wheel ALL=(ALL:ALL) ALL/%wheel ALL=(ALL:ALL) ALL/' /etc/sudoers
loginctl enable-linger nguyenhoa

emerge --verbose --yes x11-drivers/xf86-video-intel \
  x11-drivers/xf86-video-amdgpu \
  media-libs/mesa media-libs/libva media-libs/libvdpau media-libs/vulkan-loader \
  app-emulation/open-vm-tools
systemctl enable vmtoolsd

emerge --verbose --yes media-video/ffmpeg \
  media-libs/x264 media-libs/x265 \
  media-libs/libvpx media-libs/libmpeg2 \
  media-libs/fdk-aac media-sound/flac \
  media-libs/libvorbis media-sound/lame \
  media-sound/wavpack
EOF2

chmod +x /mnt/gentoo/root/install-gnome.sh

echo "[7/9] Chroot và bắt đầu cài GNOME..."
chroot /mnt/gentoo /bin/bash /root/install-gnome.sh

echo "[8/9] Thoát chroot và dọn..."
exit
umount -l /mnt/gentoo/dev{/shm,/pts,}
umount -R /mnt/gentoo

echo "[9/9] Reboot vào GNOME!"
reboot
