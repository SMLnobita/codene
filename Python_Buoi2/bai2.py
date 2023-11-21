print("Chương trình tính lãi ngân hàng")
tien = float(input("Nhap so tien: "))
years = int(input("Số năm muốn gửi: "))

laidau = 1*1/100  # Lãi suất 3 năm đầu
laihai = 1.2*1/100  # Lãi suất 5 năm tiếp theo
laiba = 1.5*1/100  # Lãi suất những năm còn lại

if years > 8:
    lai = tien * ((1 + laidau) ** 3) * ((1 + laihai) ** 5) * ((1 + laiba) ** (years - 8))
elif years > 3:
    lai = tien * ((1 + laidau) ** 3) * ((1 + laihai) ** (years - 3))
else:
    lai = tien * ((1 + laidau) ** years)

lai = round(lai, 2)

print(f"Số tiền gửi ($): {tien}")
print(f"Số năm gửi: {years}, Số tiền nhận được ($): {lai}")
