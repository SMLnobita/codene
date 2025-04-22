#!/bin/bash

echo "🛠️ Cài đặt Arduino IDE (phiên bản mới nhất)..."

# 1. Cài libfuse2 nếu chưa có
echo "🔧 Đang cài libfuse2..."
sudo apt update
sudo apt install -y libfuse2

# 2. Lấy link bản mới nhất từ Arduino website
echo "🌐 Tìm phiên bản mới nhất của Arduino IDE..."
DOWNLOAD_URL=$(curl -s https://www.arduino.cc/en/software | grep -oP 'https://downloads.arduino.cc/arduino-ide/arduino-ide_[^"]+_Linux_64bit.AppImage' | head -n 1)

if [[ -z "$DOWNLOAD_URL" ]]; then
  echo "❌ Không lấy được link tải Arduino IDE. Hãy kiểm tra kết nối mạng hoặc website Arduino."
  exit 1
fi

FILE_NAME=$(basename "$DOWNLOAD_URL")
VERSION=$(echo "$FILE_NAME" | grep -oP '[0-9]+\.[0-9]+\.[0-9]+')

echo "⬇️  Tải Arduino IDE phiên bản $VERSION..."

# 3. Tạo thư mục cài đặt
mkdir -p ~/opt/arduino-ide
cd ~/opt/arduino-ide

# 4. Tải AppImage
wget "$DOWNLOAD_URL" -O arduino-ide
chmod +x arduino-ide

# 5. Tải icon không chữ
echo "🎨 Tải icon Arduino không chữ..."
wget https://raw.githubusercontent.com/github/explore/main/topics/arduino/arduino.png -O ~/arduino.png

# 6. Tạo file .desktop (Tên app là 'Arduino IDE')
echo "📌 Tạo shortcut trong menu..."
cat <<EOF > ~/.local/share/applications/arduino-ide.desktop
[Desktop Entry]
Name=Arduino IDE
Comment=Arduino IDE AppImage
Exec=/home/$USER/opt/arduino-ide/arduino-ide --no-sandbox
Icon=/home/$USER/arduino.png
Terminal=false
Type=Application
Categories=Development;IDE;
EOF

# 7. Cập nhật menu ứng dụng
echo "🔄 Làm mới menu ứng dụng..."
update-desktop-database ~/.local/share/applications/

echo "✅ Đã cài Arduino IDE (v$VERSION)! Bạn có thể tìm 'Arduino IDE' trong menu 🎉"
