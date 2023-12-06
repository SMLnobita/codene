def kiemTraThuocDoThi(x,y):
    f_x = x**4-x**3-7*x**2+x+6
    return f_x==y
    
def kiemTraNghiem(x,y):
    if kiemTraThuocDoThi(x,y):
        return x**4-x**3-7*x**2+x+6 ==0
    return False



x = int(input("Vui lòng nhập x: "))
y = int(input("Vui lòng nhập y: "))


print(f"A thuộc đồ thị hàm số: {kiemTraThuocDoThi(x,y)}")
print(f"Hoành độ của A là nghiệm của f(x): {kiemTraNghiem(x,y)}")
