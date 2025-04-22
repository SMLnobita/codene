#!/bin/bash

# ✅ Kiểm tra và tự động cài curl nếu chưa có
if ! command -v curl &> /dev/null; then
    echo "❗ curl chưa được cài. Đang tiến hành cài đặt..."
    sudo apt update
    sudo apt install -y curl
fi

# ✅ Cài libfuse2 (dùng cho AppImage)
echo "🔧 Đang cài libfuse2 nếu cần..."
sudo apt install -y libfuse2

# ✅ Tìm bản mới nhất của Arduino IDE
echo "🌐 Tìm phiên bản mới nhất của Arduino IDE..."
DOWNLOAD_URL=$(curl -s https://www.arduino.cc/en/software | grep -oP 'https://downloads.arduino.cc/arduino-ide/arduino-ide_[^"]+_Linux_64bit.AppImage' | head -n 1)

if [[ -z "$DOWNLOAD_URL" ]]; then
  echo "❌ Không lấy được link tải Arduino IDE."
  exit 1
fi

FILE_NAME=$(basename "$DOWNLOAD_URL")
VERSION=$(echo "$FILE_NAME" | grep -oP '[0-9]+\.[0-9]+\.[0-9]+')

echo "⬇️  Đang tải Arduino IDE phiên bản $VERSION..."

# ✅ Tải AppImage
mkdir -p ~/opt/arduino-ide
cd ~/opt/arduino-ide
wget "$DOWNLOAD_URL" -O arduino-ide
chmod +x arduino-ide

# ✅ Tải icon không chữ về cùng thư mục
echo "🎨 Tải icon Arduino không chữ..."
wget https://raw.githubusercontent.com/github/explore/main/topics/arduino/arduino.png -O arduino.png

# ✅ Tạo shortcut launcher trong menu
echo "📌 Tạo shortcut trong menu..."
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

# ✅ Cập nhật menu
echo "🔄 Làm mới menu ứng dụng..."
update-desktop-database ~/.local/share/applications/

echo "✅ Đã cài Arduino IDE (v$VERSION)! Bạn có thể tìm 'Arduino IDE' trong menu 🎉"
