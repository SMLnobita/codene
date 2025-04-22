#!/bin/bash

set -e

echo "🌐 Đang tải và cài đặt thư viện phụ thuộc libgl1-mesa-glx..."
wget -c https://archive.ubuntu.com/ubuntu/pool/universe/m/mesa/libgl1-mesa-glx_23.0.4-0ubuntu1~22.04.1_amd64.deb -O /tmp/libgl1-mesa-glx.deb
sudo dpkg -i /tmp/libgl1-mesa-glx.deb || sudo apt -f install -y

echo "⬇️ Đang tải Cisco Packet Tracer 8.2.2..."
wget -c https://archive.org/download/cpt822/CiscoPacketTracer822_amd64_signed.deb -O /tmp/packettracer.deb

echo "💿 Đang cài Cisco Packet Tracer..."
sudo dpkg -i /tmp/packettracer.deb || sudo apt -f install -y

echo "✅ Đã cài xong Cisco Packet Tracer 8.2.2!"

# Mở ứng dụng (tùy chọn)
echo "🚀 Bạn có thể mở bằng lệnh: packettracer"
