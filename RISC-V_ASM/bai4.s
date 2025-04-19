.global _start
_start:
    # Chương trình tính Ước Chung Lớn Nhất (UCLN) của hai số N và M
    # Dùng thuật toán Euclid dạng phép trừ
    # Lặp đến khi N == M, mỗi bước trừ số lớn hơn cho số nhỏ hơn\

    la x5, N                # x5 lưu địa chỉ biến N
    la x6, M                # x6 lưu địa chỉ biến M
    la x7, r                # x7 lưu địa chỉ biến r
    lw x8, 0(x5)            # x8 = N, nạp giá trị N từ bộ nhớ
    lw x9, 0(x6)            # x9 = M, nạp giá trị M từ bộ nhớ

Loop:
    beq x8, x9, DONE        # nếu x8 == x9 → đã tìm được UCLN
    bgt x8, x9, ASUBB       # nếu x8 > x9 → thực hiện x8 = x8 - x9
    blt x8, x9, BSUBA       # nếu x8 < x9 → thực hiện x9 = x9 - x8

ASUBB:
    sub x8, x8, x9          # x8 = x8 - x9
    beq x0, x0, Loop        # nhảy lại Loop (vòng lặp)

BSUBA:
    sub x9, x9, x8          # x9 = x9 - x8
    beq x0, x0, Loop        # nhảy lại Loop (vòng lặp)

DONE:
    sw x8, 0(x7)            # lưu kết quả UCLN vào địa chỉ biến r
    beq x0, x0, _start      # nhảy về _start để chạy lại từ đầu (lặp vô hạn)

.data
    N: .word 60       
    M: .word 24       
    r: .word 0        