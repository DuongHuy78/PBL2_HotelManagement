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

    void themPhong(Phong);
    void xemPhong();
    void suaThongTinPhong(const string&);
    void xoaPhong(const string&);

    Phong *timPhong(string);
    void capNhatFile(Phong*, string);
    void setQLLP(QLLoaiPhong *QLLP);
    void QLPhong_Choice();

    Phong timPhong(time_t, time_t);
    LinkedList<Phong> &getDanhSachPhong();
    Node<Phong> *getHead();

};
#endif