name = input("Nhập tên: ")
print('''[+]=[ Nhà Harley xin chào bạn ]=[+]
 # 1: Viết chì      [  3000  ]   #
 # 2: Viết xanh     [  7000  ]   #
 # 3: Gom           [  10000 ]   #
 # 4: Kéo           [  15000 ]   #
 # 5: Bộ thước      [  20000 ]   #
[+]=============================[+]''')

vietchi=3000; vietxanh=7000; gom=10000; keo=15000; bothuoc= 20000

danhsachtien = []
danhsachchonhang = []
danhsachsl = []

while True:
    n = int(input(f"Cho Harley xin mã sản phẩm {name} muốn mua: "))
    if n == 1: #Viết chì
        sl = int(input("Nhập số lượng: "))
        sum_chi = vietchi*sl
        danhsachtien.append(sum_chi)
        danhsachchonhang.append("Viết chì ")
        danhsachsl.append(sl)
        print(f"Sản phẩm Viết chì \t số lượng: {sl} \t thành tiền: {sum_chi}VNĐ")
    elif n == 2:
        sl = int(input("Nhập số lượng: "))
        sum_xanh = vietxanh*sl
        danhsachtien.append(sum_xanh)
        danhsachchonhang.append("Viết xanh")
        danhsachsl.append(sl)
        print(f"Sản phẩm Viết xanh \t số lượng: {sl} \t thành tiền: {sum_xanh}VNĐ")
    elif n == 3:
        sl = int(input("Nhập số lượng: "))
        sum_gom = gom*sl
        danhsachtien.append(sum_gom)
        danhsachchonhang.append("Gom     ")
        danhsachsl.append(sl)
        print(f"Sản phẩm Gom \t \t số lượng: {sl} \t thành tiền: {sum_gom}VNĐ")
    elif n == 4:
        sl = int(input("Nhập số lượng: "))
        sum_keo = keo*sl
        danhsachtien.append(sum_keo)
        danhsachchonhang.append("Kéo     ")
        danhsachsl.append(sl)
        print(f"Sản phẩm Kéo \t \t số lượng: {sl} \t thành tiền: {sum_keo}VNĐ")
    elif n == 5:
        sl = int(input("Nhập số lượng: "))
        sum_thuoc = bothuoc*sl
        danhsachtien.append(sum_thuoc)
        danhsachchonhang.append("Bộ thước")
        danhsachsl.append(sl)
        print(f"Sản phẩm Bộ thước \t số lượng: {sl} \t thành tiền: {sum_thuoc}VNĐ")
    elif n == 0:
        tong_tien = sum(danhsachtien)
        print("-"*60)
        print(f"Sản phẩm {name} đã chọn")
        for i in range(len(danhsachchonhang)):
            print(f"{i + 1}. {danhsachchonhang[i]} \t số lượng: {danhsachsl[i]} \t thành tiền: {danhsachtien[i]}VNĐ")
        print(f"Tổng tiền cần thanh toán là: {tong_tien}VNĐ")
        print("-"*60)
        break
print(f"Cảm ơn bạn đã ủng hộ nhà Harley")
print(f"Harley vẫn ở đây đợi {name} ! Ghé Harley khi nào {name} cần nhé !")
print(f"Harley chúc bạn {name} học tập thật tốt !!")
print("*"*60)