.global _start
_start:
    # Viết chương trình assembly tính r = N^M, với N và M là hai số cho trước.
    la x5, N              # x5 lưu địa chỉ biến N
    la x6, M              # x6 lưu địa chỉ biến M
    la x7, r              # x7 lưu địa chỉ biến r
    lw x8, 0(x5)          # x8 = N, nạp giá trị N từ bộ nhớ
    lw x9, 0(x6)          # x9 = M, nạp giá trị M từ bộ nhớ
    li x18, 0             # x18 = i, dùng làm biến đếm
    li x19, 1             # x19 = 1, giá trị khởi tạo kết quả r = 1

Loop:
    addi x18, x18, 1      # i = i + 1
    mul x19, x19, x8      # r = r * N
    beq x18, x9, KetQua   # nếu i == M thì nhảy đến KetQua
    beq x0, x0, Loop      # nhảy lại Loop (vòng lặp)

KetQua:
    sw x19, 0(x7)         # lưu kết quả r = N^M vào địa chỉ biến r
    beq x0, x0, _start    # nhảy về _start để chạy lại từ đầu (lặp vô hạn)

.data
    N: .word 2
    M: .word 4
    r: .word 0