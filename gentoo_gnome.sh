#!/bin/bash
set -e

# ==== LINK STAGE3 TỪ DROPBOX ====
STAGE3_URL="https://www.dropbox.com/scl/fi/pth68tuk3ozuq1l4nj1zk/stage3-amd64-desktop-systemd-20250420T121009Z.tar.xz?rlkey=nkcgqjqqxyicz736suuhuiamt&st=82ulje4b&dl=1"

echo "[1/8] Format phân vùng..."
mkfs.ext4 /dev/sda1
mkfs.ext4 /dev/sda3
mkswap /dev/sda2
swapon /dev/sda2

echo "[2/8] Mount hệ thống..."
mount /dev/sda3 /mnt/gentoo
mkdir -p /mnt/gentoo/boot
mount /dev/sda1 /mnt/gentoo/boot

echo "[3/8] Tải Stage3 từ Dropbox..."
cd /mnt/gentoo
wget "$STAGE3_URL" -O stage3.tar.xz
tar xpvf stage3.tar.xz --xattrs-include='*.*' --numeric-owner

echo "[4/8] Mount môi trường chroot..."
cp --dereference /etc/resolv.conf /mnt/gentoo/etc/
mount -t proc /proc /mnt/gentoo/proc
mount --rbind /sys /mnt/gentoo/sys
mount --rbind /dev /mnt/gentoo/dev

echo "[5/8] Ghi script cài GNOME vào trong chroot..."
cat > /mnt/gentoo/root/install-gnome.sh <<'INSIDECHROOT'
#!/bin/bash
set -e

emerge-webrsync
emerge --sync

eselect profile set $(eselect profile list | grep -m1 'gnome.*systemd' | awk '{print $1}' | tr -d '[]')

CORES=$(nproc)
cat >> /etc/portage/make.conf <<EOF
CFLAGS="-march=native -O2 -pipe"
CXXFLAGS="\${CFLAGS}"
MAKEOPTS="-j$((CORES + 1))"
USE="X gnome gtk introspection pulseaudio dbus policykit udev bluetooth systemd pipewire ffmpeg vlc -qt5 -kde"
EOF

emerge --ask gentoo-sources genkernel grub vim sudo eix
genkernel all

emerge --ask gnome gdm firefox networkmanager alsa-utils \
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

emerge --ask x11-drivers/xf86-video-intel \
  x11-drivers/xf86-video-amdgpu \
  media-libs/mesa media-libs/libva media-libs/libvdpau media-libs/vulkan-loader \
  app-emulation/open-vm-tools
systemctl enable vmtoolsd

emerge --ask media-video/ffmpeg \
  media-libs/x264 media-libs/x265 \
  media-libs/libvpx media-libs/libmpeg2 \
  media-libs/fdk-aac media-sound/flac \
  media-libs/libvorbis media-sound/lame \
  media-sound/wavpack

echo "[*] Hoàn tất cài Gentoo GNOME! 🎉"
INSIDECHROOT

chmod +x /mnt/gentoo/root/install-gnome.sh

echo "[6/8] Chroot và bắt đầu cài GNOME..."
chroot /mnt/gentoo /bin/bash /root/install-gnome.sh

echo "[7/8] Thoát và dọn hệ thống..."
exit
umount -l /mnt/gentoo/dev{/shm,/pts,}
umount -R /mnt/gentoo

echo "[8/8] Reboot hệ thống!"
reboot
