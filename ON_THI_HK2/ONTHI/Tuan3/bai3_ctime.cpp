// Tuan 3 - Bai 3: Lop CTime (gio, phut, giay)
// Phuong thuc: cong (giay), tru (giay), nhap, xuat
#include <iomanip>
#include <iostream>

using namespace std;

class CTime {
private:
  int gio, phut, giay;

  // Chuan hoa ve dang gio:phut:giay hop le (24 gio)
  void chuanHoa(long tongGiay) {
    tongGiay %= 86400;           // 1 ngay = 86400 giay
    if (tongGiay < 0) tongGiay += 86400;
    gio = tongGiay / 3600;
    phut = (tongGiay % 3600) / 60;
    giay = tongGiay % 60;
  }

public:
  CTime(int h = 0, int m = 0, int s = 0) { chuanHoa((long)h * 3600 + m * 60 + s); }

  long toGiay() const { return (long)gio * 3600 + phut * 60 + giay; }

  void nhap() {
    int h, m, s;
    cout << "Nhap gio phut giay: ";
    cin >> h >> m >> s;
    chuanHoa((long)h * 3600 + m * 60 + s);
  }

  void xuat() const {
    cout << setfill('0') << setw(2) << gio << ":" << setw(2) << phut << ":"
         << setw(2) << giay << setfill(' ') << endl;
  }

  CTime congGiay(int s) {
    CTime kq;
    kq.chuanHoa(toGiay() + s);
    return kq;
  }
  CTime truGiay(int s) {
    CTime kq;
    kq.chuanHoa(toGiay() - s);
    return kq;
  }
};

int main() {
  CTime t;
  cout << "--- Nhap thoi diem ---\n";
  t.nhap();

  cout << "Thoi diem da nhap : ";
  t.xuat();

  int s;
  cout << "Nhap so giay can cong: ";
  cin >> s;
  cout << "Sau khi cong " << s << " giay: ";
  t.congGiay(s).xuat();

  cout << "Nhap so giay can tru: ";
  cin >> s;
  cout << "Sau khi tru " << s << " giay: ";
  t.truGiay(s).xuat();

  return 0;
}
