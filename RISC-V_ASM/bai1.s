.global _start
_start:
	la x5, N              # x5 lưu địa chỉ biến N
	la x6, r              # x6 lưu địa chỉ biến r
	lw x7, 0(x5)          # x7 = N, nạp giá trị N từ bộ nhớ
	li x8, 0              # x8 = i, dùng làm biến đếm
	li x9, 1              # x9 = 1, dùng để lưu giai thừa (gt)

Loop:
	addi x8, x8, 1        # i = i + 1
	mul x9, x9, x8        # gt = gt * i
	beq x8, x7, KetQua    # nếu i == N thì nhảy tới KetQua
	beq x0, x0, Loop      # nhảy lại Loop (vòng lặp)

KetQua:
	sw x9, 0(x6)          # lưu kết quả giai thừa vào địa chỉ biến r
	beq x0, x0, _start    # nhảy về _start để chạy lại từ đầu (lặp vô hạn)

.data
	N: .word 5
	r: .word 0

	