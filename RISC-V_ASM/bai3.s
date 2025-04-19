.global _start
_start:
    # Viết chương trình assembly kiểm tra số N có phải là số chính phương hay không.
    # Nếu N là số chính phương thì biến r = 1, ngược lại r = 0
    la x5, N          # x5 lưu địa chỉ biến N
    la x6, r          # x6 lưu địa chỉ biến r
    lw x8, 0(x5)      # x8 = N, nạp giá trị N từ bộ nhớ
    li x9, 0          # x9 = i, biến đếm từ 1 tới sqrt(N)
    li x18, 0         # x18 = i*i, giá trị bình phương

Loop:
    addi x9, x9, 1                   # i = i + 1
    mul x18, x9, x9                  # x18 = i * i
    bge x18, x8, SoChinhPhuong       # nếu i^2 >= N → kiểm tra chính phương
    beq x0, x0, Loop                 # nhảy lại Loop (vòng lặp)

SoChinhPhuong:
    beq x18, x8, DUNG                # nếu i^2 == N → đúng là số chính phương
    bne x18, x8, SAI                 # nếu i^2 > N → sai, không phải số chính phương

DUNG:
    li x19, 1                        # gán 1 vào r
    sw x19, 0(x6)                    # lưu kết quả 1 vào địa chỉ biến r
    beq x0, x0, _start               # nhảy về _start để chạy lại từ đầu (lặp vô hạn)

SAI:
    li x19, 0                        # gán 0 vào r
    sw x19, 0(x6)                    # lưu kết quả 0 vào địa chỉ biến r
    beq x0, x0, _start               # nhảy về _start để chạy lại từ đầu (lặp vô hạn)

.data
N: .word 15
r: .word 0