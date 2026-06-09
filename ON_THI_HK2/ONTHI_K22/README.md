# ONTHI_K22 - De kiem tra thuc hanh OOP (60 phut)

Code C++ giai **7 de** trong file **De-thi_OOP.pdf**. Moi de chia theo so cuoi MSSV.
Tat ca da bien dich & chay thu OK voi `g++ -std=c++17`.

> **Chon de theo so cuoi MSSV cua ban:**
> | So cuoi MSSV | De | Thu muc |
> |---|---|---|
> | 1 hoac 2 | De 1 | `De1/` |
> | 3 hoac 4 | De 2 | `De2/` |
> | 5 hoac 6 | De 3 | `De3/` |
> | 7 | De 4 | `De4/` |
> | 8 | De 5 | `De5/` |
> | 9 | De 6 | `De6/` |
> | 0 | De 7 | `De7/` |

## Cach bien dich & chay
```bash
g++ -std=c++17 De1/cau1_sophuc_thuc.cpp -o cau1
./cau1
```

## Noi dung tung de

### De 1 (MSSV cuoi 1, 2)
- `De1/cau1_sophuc_thuc.cpp` - So phuc + so thuc: `z+u=(a+u)+bi`; nhan: `z*u=au+ubi` (nap chong toan tu voi double)
- `De1/cau2_diem_tong.cpp` - Diem 2D, tong 2 diem `A+B=(xA+xB, yA+yB)`

### De 2 (MSSV cuoi 3, 4)
- `De2/cau1_point.cpp` - Lop Point: Display + destructor (huy bo)
- `De2/cau2_multipoint.cpp` - MultiPoint (mang dong): Calculate (khoang cach toi goc), toan tu `>`, Display, Insert, destructor

### De 3 (MSSV cuoi 5, 6)
- `De3/cau1_hinhhoc_tamgiac.cpp` - HinhHoc co ham ao tinh dien tich; TamGiac ke thua, nhap 3 canh, Heron
- `De3/cau2_matrix_friend.cpp` - Ma tran, ham cong la **ham tu do + friend**

### De 4 (MSSV cuoi 7)
- `De4/cau1_diem3d_eq.cpp` - Diem (x,y,z), toan tu `==` kiem tra 2 diem trung nhau
- `De4/cau2_phanso.cpp` - Phan so: cong, tru, nhan, chia, nhap, xuat

### De 5 (MSSV cuoi 8)
- `De5/cau1_sophuc.cpp` - So phuc: `+ - *`, chuyen doi thuc<->phuc
- `De5/cau2_matrix_eq.cpp` - Ma tran, toan tu `==` so sanh 2 ma tran

### De 6 (MSSV cuoi 9)
- `De6/cau1_vector.cpp` - Vector co 3 ham thiet lap (0/1/2 tham so), tong 2 vector, toan tu `==`
- `De6/cau2_tamgiac_eq.cpp` - Tam giac, toan tu `==` so sanh theo 3 canh bang nhau (khong ke thu tu)

### De 7 (MSSV cuoi 0)
- `De7/thucung.cpp` - Animal (ao TinhTien) -> Cho, Meo; lop NgoiNha quan ly danh sach, tinh tong tien an

> Cac bai co `cin` (tam giac De3, ma tran, phan so) se cho nhap tu ban phim khi chay.
> Cac bai con lai dung san du lieu mau de in ket qua ngay - co the doi sang nhap tay neu can.
