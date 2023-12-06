danhSach = []
n = int(input("Nhập số lượng số muốn nhập: "))

def addDanhSach(n):
    for i in range(0,n,1):
        sulyso = i+1
        sone = int(input(f"Nhập phần tử thứ [{sulyso}]: "))
        danhSach.append(sone)

def tinhTong():
    sum =0
    for i in danhSach:
        sum +=i
    return sum

addDanhSach(n)
kq = tinhTong()
print(f"Kết quả là: {kq}")
