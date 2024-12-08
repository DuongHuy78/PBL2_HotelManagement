#ifndef QLPHONG_H
#define QLPHONG_H
#include "Phong.h"
#include "QLLoaiPhong.h"
#include "LinkedList.h"
class QLPhong {
    LinkedList<Phong *> DSP; // Danh sach phong
    QLLoaiPhong *QLLP;
public:
    ~QLPhong();

    void themPhong(Phong *);
    // void suaThongTin(const string&);
    void xoaPhong(const string&);

    Phong nhapThongTin();
    Phong *timPhong(string);
    void setQLLP(QLLoaiPhong *QLLP);
    LinkedList<Phong *> &getDSP();

    friend ostream& operator<<(ostream&, QLPhong&);
};
#endif