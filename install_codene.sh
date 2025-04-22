#!/bin/bash

set -e

function install_arduino() {
    clear
    echo "🛠️ Đang cài Arduino IDE..."

    if ! command -v curl &> /dev/null; then
        echo "❗ curl chưa được cài. Đang tiến hành cài đặt..."
        sudo apt update
        sudo apt install -y curl
    fi

    sudo apt install -y libfuse2

    DOWNLOAD_URL=$(curl -s https://www.arduino.cc/en/software | grep -oP 'https://downloads.arduino.cc/arduino-ide/arduino-ide_[^"]+_Linux_64bit.AppImage' | head -n 1)
    if [[ -z "$DOWNLOAD_URL" ]]; then
        echo "❌ Không lấy được link tải Arduino IDE."
        exit 1
    fi

    FILE_NAME=$(basename "$DOWNLOAD_URL")
    VERSION=$(echo "$FILE_NAME" | grep -oP '[0-9]+\.[0-9]+\.[0-9]+')

    echo "⬇️ Đang tải Arduino IDE phiên bản $VERSION..."
    mkdir -p ~/opt/arduino-ide
    cd ~/opt/arduino-ide
    wget "$DOWNLOAD_URL" -O arduino-ide
    chmod +x arduino-ide

    wget https://raw.githubusercontent.com/github/explore/main/topics/arduino/arduino.png -O arduino.png

    mkdir -p ~/.local/share/applications/
    cat <<EOF > ~/.local/share/applications/arduino-ide.desktop
[Desktop Entry]
Name=Arduino IDE
Comment=Arduino IDE AppImage
Exec=/home/$USER/opt/arduino-ide/arduino-ide --no-sandbox
Icon=/home/$USER/opt/arduino-ide/arduino.png
Terminal=false
Type=Application
Categories=Development;IDE;
EOF

    update-desktop-database ~/.local/share/applications/
    echo "✅ Đã cài Arduino IDE (v$VERSION)! Bạn có thể tìm 'Arduino IDE' trong menu 🎉"
}

function install_cisco() {
    clear
    echo "💽 Đang cài Cisco Packet Tracer 8.2.2..."

    wget -c https://archive.ubuntu.com/ubuntu/pool/universe/m/mesa/libgl1-mesa-glx_23.0.4-0ubuntu1~22.04.1_amd64.deb -O /tmp/libgl1-mesa-glx.deb
    sudo dpkg -i /tmp/libgl1-mesa-glx.deb || sudo apt -f install -y

    wget -c https://archive.org/download/packet-tracer-822-amd-64-signed_202504/Packet_Tracer822_amd64_signed.deb -O /tmp/packettracer.deb
    sudo dpkg -i /tmp/packettracer.deb || sudo apt -f install -y

    echo "✅ Đã cài Cisco Packet Tracer 8.2.2!"
    echo "🚀 Gõ 'packettracer' để chạy."
}

function uninstall_menu() {
    clear
    echo "🧹 Gỡ cài đặt phần mềm"
    echo "1️⃣ Gỡ Arduino IDE"
    echo "2️⃣ Gỡ Cisco Packet Tracer"
    echo "0️⃣ Quay lại menu chính"
    read -p "👉 Nhập lựa chọn [0-2]: " opt
    clear

    if [[ "$opt" == "1" ]]; then
        echo "🗑️ Đang gỡ Arduino IDE..."
        rm -rf ~/opt/arduino-ide
        rm -f ~/.local/share/applications/arduino-ide.desktop
        update-desktop-database ~/.local/share/applications/
        echo "✅ Đã gỡ Arduino IDE."

    elif [[ "$opt" == "2" ]]; then
        echo "🗑️ Đang gỡ Cisco Packet Tracer..."
        sudo apt remove --purge -y packettracer
        sudo apt autoremove -y
        echo "✅ Đã gỡ Cisco Packet Tracer."

    elif [[ "$opt" == "0" ]]; then
        echo "↩️ Quay lại menu chính..."

    else
        echo "❌ Lựa chọn không hợp lệ!"
    fi
}

### --- MAIN MENU ---

while true; do
    echo
    echo "🌟 Trình cài đặt phần mềm 'codene' 🌟"
    echo "1️⃣  Cài đặt Arduino IDE"
    echo "2️⃣  Cài đặt Cisco Packet Tracer"
    echo "3️⃣  Gỡ cài đặt phần mềm"
    echo "0️⃣  Thoát"
    read -p "👉 Nhập lựa chọn của bạn [0-3]: " choice
    clear

    case "$choice" in
        1) install_arduino ;;
        2) install_cisco ;;
        3) uninstall_menu ;;
        0) echo "👋 Tạm biệt!"; exit 0 ;;
        *) echo "❌ Lựa chọn không hợp lệ!" ;;
    esac
done
