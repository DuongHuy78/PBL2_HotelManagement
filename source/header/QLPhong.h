#ifndef QLPHONG_H
#define QLPHONG_H
#include "Phong.h"
#include "QLLoaiPhong.h"
#include "LinkedList.h"
class QLPhong {
    LinkedList<Phong> DSP; // Danh sach phong
    QLLoaiPhong *QLLP;
public:
    QLPhong();
    ~QLPhong();

    void AddRangePhong(string); // đọc dữ liệu đầu vào và trả về danh sách phòng

    void themPhong(const Phong&);
    // void taoPhongMoi(Phong);
    void xemPhong();
    void suaThongTin(const string&);
    void xoaPhong(const string&);

    Phong nhapThongTin();
    Phong *timPhong(string);
    // void capNhatFile(Phong*, string);
    void setQLLP(QLLoaiPhong *QLLP);
    // void QLPhong_Choice();
    LinkedList<Phong> &getDanhSachPhong();

    friend ostream& operator<<(ostream&, QLPhong&);
};
#endif