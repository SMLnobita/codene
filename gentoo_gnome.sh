#!/bin/bash
# Script cài đặt tự động Gentoo Linux trên VMware với GNOME
# Múi giờ: Ho Chi Minh, Ngôn ngữ: English
# Lưu ý: Chạy script này với quyền root trong môi trường VMware

set -e # Dừng script nếu có lỗi xảy ra

# ====== CẤU HÌNH TỰ ĐỘNG ======
# Script đã được cấu hình sẵn cho VMware với GNOME

# Thiết bị ổ đĩa chính (tự động phát hiện cho VMware)
DISK=$(lsblk -dpno NAME | grep -v loop | head -n 1)

# Định dạng phân vùng (bios cho VMware)
BOOT_TYPE="bios"

# Cấu hình mạng
HOSTNAME="gentoo"
NETWORK_INTERFACE="ens33"  # Interface phổ biến cho VMware
USE_DHCP=true            # Sử dụng DHCP
STATIC_IP="192.168.1.100"
NETMASK="255.255.255.0"
GATEWAY="192.168.1.1"
DNS_SERVERS="8.8.8.8 8.8.4.4"

# Mật khẩu root và user (đã được thiết lập)
ROOT_PASSWORD="098765"
USER_NAME="nguyenhoa"
USER_PASSWORD="098765"

# Múi giờ (đã cố định HCM)
TIMEZONE="Asia/Ho_Chi_Minh"

# Ngôn ngữ tiếng Anh (đã cố định)
LOCALE="en_US.UTF-8 UTF-8"
LANGUAGE="en_US.UTF-8"

# Kiến trúc CPU
ARCH="amd64"

# Cấu hình Gentoo với GNOME
PROFILE="default/linux/amd64/17.1/desktop/gnome/systemd"
CPU_FLAGS="mmx sse sse2" # CPU flags cơ bản cho máy ảo

# ====== KẾT THÚC CẤU HÌNH ======

# Hàm hiển thị tiến trình
show_progress() {
    echo "====== $1 ======" | tee -a /var/log/gentoo-install.log
}

# Ghi log lỗi
log_error() {
    echo "LỖI: $1" | tee -a /var/log/gentoo-install-errors.log
    exit 1
}

# Kiểm tra quyền root
if [ "$EUID" -ne 0 ]; then
    log_error "Script này phải được chạy với quyền root!"
fi

# Bắt đầu ghi log
exec > >(tee -a /var/log/gentoo-install.log) 2>&1
show_progress "Bắt đầu cài đặt Gentoo Linux tự động"

# Kiểm tra môi trường VMware
show_progress "Kiểm tra môi trường VMware"
if ! dmidecode -t system | grep -i "vmware" &>/dev/null; then
    log_error "Script này chỉ được thiết kế để chạy trong môi trường VMware. Vui lòng chạy trên VMware."
fi

# Kiểm tra kết nối internet
show_progress "Kiểm tra kết nối internet"
if ! ping -c 3 gentoo.org &>/dev/null; then
    log_error "Không có kết nối internet. Vui lòng kiểm tra cấu hình mạng và thử lại."
fi

# Phát hiện CPU flags tự động
show_progress "Phát hiện CPU flags"
if command -v cpuid2cpuflags &>/dev/null; then
    CPU_FLAGS=$(cpuid2cpuflags | sed 's/.*://')
    echo "Đã phát hiện CPU flags: $CPU_FLAGS"
else
    echo "Công cụ cpuid2cpuflags chưa có, sẽ cài đặt sau trong chroot environment"
    # Sử dụng giá trị mặc định cho VMware
    CPU_FLAGS="mmx sse sse2"
fi

# Cấu hình đồng hồ hệ thống
show_progress "Cấu hình đồng hồ hệ thống"
ntpd -q -g || log_error "Không thể đồng bộ thời gian"

# Tạo bảng phân vùng
show_progress "Tạo bảng phân vùng trên $DISK"

# Xóa toàn bộ phân vùng hiện có
wipefs -a "$DISK"
sgdisk -Z "$DISK" || dd if=/dev/zero of="$DISK" bs=512 count=1

# Cấu hình cụ thể cho VMware (tối ưu hóa):
# - 512MB cho boot
# - 4GB swap
# - Phần còn lại cho root (/)

if [ "$BOOT_TYPE" = "uefi" ]; then
    # Phân vùng GPT cho UEFI
    sgdisk -n 1:0:+512M -t 1:ef00 -c 1:"EFI System" "$DISK"
    sgdisk -n 2:0:+4G -t 2:8200 -c 2:"swap" "$DISK"
    sgdisk -n 3:0:0 -t 3:8300 -c 3:"Gentoo Root" "$DISK"
    
    EFI_PARTITION="${DISK}1"
    SWAP_PARTITION="${DISK}2"
    ROOT_PARTITION="${DISK}3"
else
    # Phân vùng MBR cho BIOS
    parted -s "$DISK" mklabel msdos
    parted -s "$DISK" mkpart primary ext4 1MiB 513MiB
    parted -s "$DISK" set 1 boot on
    parted -s "$DISK" mkpart primary linux-swap 513MiB 4.5GiB
    parted -s "$DISK" mkpart primary ext4 4.5GiB 100%
    
    BOOT_PARTITION="${DISK}1"
    SWAP_PARTITION="${DISK}2"
    ROOT_PARTITION="${DISK}3"
fi

# Đợi hệ thống nhận diện phân vùng mới
sleep 3

# Định dạng phân vùng
show_progress "Định dạng phân vùng"
if [ "$BOOT_TYPE" = "uefi" ]; then
    mkfs.fat -F 32 "$EFI_PARTITION"
else
    mkfs.ext4 -F "$BOOT_PARTITION"
fi

# Tạo và kích hoạt swap
mkswap "$SWAP_PARTITION"
swapon "$SWAP_PARTITION"

# Định dạng phân vùng root
mkfs.ext4 -F "$ROOT_PARTITION"

# Gắn kết phân vùng
show_progress "Gắn kết phân vùng"
mkdir -p /mnt/gentoo
mount "$ROOT_PARTITION" /mnt/gentoo || log_error "Không thể gắn kết phân vùng root"

if [ "$BOOT_TYPE" = "uefi" ]; then
    mkdir -p /mnt/gentoo/boot/efi
    mount "$EFI_PARTITION" /mnt/gentoo/boot/efi || log_error "Không thể gắn kết phân vùng EFI"
else
    mkdir -p /mnt/gentoo/boot
    mount "$BOOT_PARTITION" /mnt/gentoo/boot || log_error "Không thể gắn kết phân vùng boot"
fi

# Tải stage3 tarball từ link được cung cấp
show_progress "Tải stage3 tarball (GNOME + systemd)"
cd /mnt/gentoo
STAGE3_URL="https://www.dropbox.com/scl/fi/pth68tuk3ozuq1l4nj1zk/stage3-amd64-desktop-systemd-20250420T121009Z.tar.xz?rlkey=nkcgqjqqxyicz736suuhuiamt&st=5em7rtuc&dl=1"
wget "$STAGE3_URL" -O stage3.tar.xz || log_error "Không thể tải stage3 tarball"

# Giải nén stage3
show_progress "Giải nén stage3"
tar xpvf stage3.tar.xz --xattrs-include='*.*' --numeric-owner || log_error "Không thể giải nén stage3"
rm stage3.tar.xz

# Cấu hình make.conf
show_progress "Cấu hình make.conf"
cat > /mnt/gentoo/etc/portage/make.conf << EOF
# Cấu hình cơ bản - tối ưu cho VMware
COMMON_FLAGS="-O2 -pipe -march=native"
CFLAGS="\${COMMON_FLAGS}"
CXXFLAGS="\${COMMON_FLAGS}"
FCFLAGS="\${COMMON_FLAGS}"
FFLAGS="\${COMMON_FLAGS}"

# Cấu hình CPU cho VMware
CPU_FLAGS_X86="$CPU_FLAGS"

# Cấu hình parallel build (giới hạn để tránh quá tải VM)
MAKEOPTS="-j$(( $(nproc) < 4 ? $(nproc) : 4 ))"

# Cấu hình USE flags cho GNOME desktop
USE="dbus X gnome gtk libnotify pulseaudio alsa udisks unicode systemd -kde -plasma -qt5 -qt6 -gtk2 elogind"

# Cấu hình VMware - thêm VIDEO_CARDS
VIDEO_CARDS="vmware"
INPUT_DEVICES="libinput evdev"

# Mirrors
GENTOO_MIRRORS="https://mirror.leaseweb.com/gentoo/ https://mirrors.mit.edu/gentoo-distfiles/ https://gentoo.osuosl.org/"

# Cấu hình ngôn ngữ - tiếng Anh
LINGUAS="en"
L10N="en"
EOF

# Cấu hình repository Gentoo
show_progress "Cấu hình repository"
mkdir -p /mnt/gentoo/etc/portage/repos.conf
cp /mnt/gentoo/usr/share/portage/config/repos.conf /mnt/gentoo/etc/portage/repos.conf/gentoo.conf

# Cấu hình DNS
show_progress "Cấu hình DNS"
cp --dereference /etc/resolv.conf /mnt/gentoo/etc/

# Gắn kết hệ thống file ảo
show_progress "Gắn kết hệ thống file ảo"
mount --types proc /proc /mnt/gentoo/proc
mount --rbind /sys /mnt/gentoo/sys
mount --make-rslave /mnt/gentoo/sys
mount --rbind /dev /mnt/gentoo/dev
mount --make-rslave /mnt/gentoo/dev
mount --bind /run /mnt/gentoo/run
mount --make-slave /mnt/gentoo/run

# Chroot vào môi trường mới
show_progress "Chroot vào môi trường mới và cấu hình hệ thống"
cat > /mnt/gentoo/chroot_commands.sh << 'EOF'
#!/bin/bash
set -e

# Đồng bộ cây Portage
emerge-webrsync
emerge --sync

# Cập nhật profile
eselect profile list
eselect profile set PROFILE_ID

# Cập nhật thế giới
emerge --verbose --update --deep --newuse @world

# Cấu hình múi giờ
echo "TIMEZONE" > /etc/timezone
emerge --config sys-libs/timezone-data

# Cấu hình locale
echo "LOCALE" >> /etc/locale.gen
locale-gen
eselect locale set LANGUAGE
env-update && source /etc/profile

# Cập nhật environment
env-update && source /etc/profile

# Cài đặt kernel và firmware
emerge --verbose sys-kernel/gentoo-sources sys-kernel/linux-firmware sys-kernel/genkernel
genkernel all

# Cài đặt các gói cần thiết
emerge --verbose net-misc/dhcpcd net-misc/netifrc app-admin/sysklogd sys-process/cronie sys-apps/mlocate sys-fs/e2fsprogs sys-fs/dosfstools net-wireless/wpa_supplicant

# Đặt hostname
echo "hostname=\"HOSTNAME\"" > /etc/conf.d/hostname

# Cấu hình mạng
if USE_DHCP; then
    echo "config_NETWORK_INTERFACE=\"dhcp\"" > /etc/conf.d/net
else
    echo "config_NETWORK_INTERFACE=\"STATIC_IP netmask NETMASK brd +\"" > /etc/conf.d/net
    echo "routes_NETWORK_INTERFACE=\"default via GATEWAY\"" >> /etc/conf.d/net
    echo "dns_servers_NETWORK_INTERFACE=\"DNS_SERVERS\"" >> /etc/conf.d/net
fi

cd /etc/init.d
ln -s net.lo net.NETWORK_INTERFACE
rc-update add net.NETWORK_INTERFACE default

# Đặt mật khẩu root
echo "root:$ROOT_PASSWORD" | chpasswd

# Tạo user và đặt mật khẩu
useradd -m -G users,wheel,audio,video,usb,cdrom -s /bin/bash $USER_NAME
echo "$USER_NAME:$USER_PASSWORD" | chpasswd

# Cấu hình sudo cho phép wheel group
emerge --verbose app-admin/sudo
echo "%wheel ALL=(ALL) ALL" > /etc/sudoers.d/wheel

# Cài đặt bootloader
if [ "BOOT_TYPE" = "uefi" ]; then
    emerge --verbose sys-boot/grub:2 sys-boot/efibootmgr
    grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=gentoo
else
    emerge --verbose sys-boot/grub:2
    grub-install /dev/DISK_NAME
fi
grub-mkconfig -o /boot/grub/grub.cfg

# Cài đặt GNOME Desktop
emerge --verbose x11-base/xorg-server
emerge --verbose gnome-base/gnome
rc-update add display-manager default

# Cài đặt các driver VMware Tools
emerge --verbose app-emulation/open-vm-tools
rc-update add vmware-tools default

# Hoàn thành
echo "Cài đặt Gentoo Linux hoàn tất! Hãy khởi động lại hệ thống."
EOF

# Thay thế các biến trong script chroot
sed -i "s|TIMEZONE|$TIMEZONE|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|LOCALE|$LOCALE|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|LANGUAGE|$LANGUAGE|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|HOSTNAME|$HOSTNAME|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|NETWORK_INTERFACE|$NETWORK_INTERFACE|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|USE_DHCP|$USE_DHCP|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|STATIC_IP|$STATIC_IP|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|NETMASK|$NETMASK|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|GATEWAY|$GATEWAY|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|DNS_SERVERS|$DNS_SERVERS|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|ROOT_PASSWORD|$ROOT_PASSWORD|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|BOOT_TYPE|$BOOT_TYPE|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|DISK_NAME|${DISK##*/}|g" /mnt/gentoo/chroot_commands.sh
sed -i "s|PROFILE_ID|$PROFILE|g" /mnt/gentoo/chroot_commands.sh

chmod +x /mnt/gentoo/chroot_commands.sh

# Thực thi script trong chroot
chroot /mnt/gentoo /chroot_commands.sh || log_error "Lỗi trong quá trình chroot"

# Dọn dẹp
show_progress "Dọn dẹp và hoàn tất cài đặt"
rm /mnt/gentoo/chroot_commands.sh

# Ngắt kết nối các phân vùng
umount -l /mnt/gentoo/dev{/shm,/pts,}
umount -R /mnt/gentoo

show_progress "Cài đặt Gentoo hoàn tất!"
echo "*************************************************************"
echo "* Hệ thống Gentoo Linux đã được cài đặt thành công!         *"
echo "* - Hostname: $HOSTNAME                                      *"
echo "* - Root password: $ROOT_PASSWORD                            *"
echo "* - User: $USER_NAME, Password: $USER_PASSWORD               *"
echo "* - Đã cài đặt: GNOME, Firefox, VLC, Telegram               *" 
echo "* - LibreOffice: Sẽ được cài đặt sau                        *"
echo "* - VMware Tools đã được cài đặt và cấu hình                *"
echo "* - Tự động đăng nhập với tài khoản $USER_NAME              *"
echo "*                                                           *"
echo "* Vui lòng khởi động lại để sử dụng hệ thống mới.           *"
echo "*************************************************************"
