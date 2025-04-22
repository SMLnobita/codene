#!/bin/bash

echo "🛠️ Cài đặt Arduino IDE 2.3.6..."

# 1. Cài libfuse2 nếu chưa có
echo "🔧 Đang cài libfuse2..."
sudo apt update
sudo apt install -y libfuse2

# 2. Tạo thư mục chứa AppImage
echo "📂 Tạo thư mục ~/opt/arduino-ide"
mkdir -p ~/opt/arduino-ide
cd ~/opt/arduino-ide

# 3. Tải Arduino IDE
echo "⬇️  Đang tải Arduino IDE 2.3.6..."
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.6_Linux_64bit.AppImage -O arduino-ide
chmod +x arduino-ide

# 4. Tải icon
echo "🎨 Tải icon Arduino..."
wget https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_Logo.svg -O ~/arduino.svg

# 5. Tạo file .desktop
echo "📌 Tạo shortcut trong menu..."
cat <<EOF > ~/.local/share/applications/arduino-ide.desktop
[Desktop Entry]
Name=Arduino IDE 2.3.6
Comment=Arduino IDE AppImage
Exec=/home/$USER/opt/arduino-ide/arduino-ide --no-sandbox
Icon=/home/$USER/arduino.svg
Terminal=false
Type=Application
Categories=Development;IDE;
EOF

# 6. Cập nhật menu ứng dụng
echo "🔄 Làm mới menu ứng dụng..."
update-desktop-database ~/.local/share/applications/

echo "✅ Cài đặt xong! Bạn có thể tìm 'Arduino IDE' trong menu rồi 🎉"
