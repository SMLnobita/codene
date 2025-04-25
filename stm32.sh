#!/bin/bash

set -e

echo "🔧 Đang cài STM32CubeIDE 1.18.1..."

TMP_DIR="/tmp/stm32cubeide_install"
ZIP_URL="https://archive.org/download/en.st-stm32cubeide_1.18.1_24813_20250409_2138_amd64.deb_bundle.sh/en.st-stm32cubeide_1.18.1_24813_20250409_2138_amd64.deb_bundle.sh.zip"

# Cài gói cần thiết
sudo apt update
sudo apt install -y unzip libfuse2

# Tải và giải nén
mkdir -p "$TMP_DIR"
cd "$TMP_DIR"
wget -c "$ZIP_URL" -O stm32cubeide.zip
unzip stm32cubeide.zip
chmod +x *.sh

# Chạy script kèm auto yes
echo "⚙️ Chạy trình cài đặt với auto-yes..."
yes yes | sudo ./*.sh

echo "✅ Cài đặt STM32CubeIDE hoàn tất!"
echo "🚀 Bạn có thể tìm 'STM32CubeIDE' trong menu hoặc gõ: stm32cubeide"
