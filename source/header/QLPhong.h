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

    void themPhong(const Phong&);
    void xemPhong();
    void suaThongTin(const string&);
    void xoaPhong(const string&);

    Phong nhapThongTin();
    Phong *timPhong(string);
    void setQLLP(QLLoaiPhong *QLLP);
    LinkedList<Phong> &getDSP();
    // Node<Phong> *getHead();

    friend ostream& operator<<(ostream&, QLPhong&);
};
#endif