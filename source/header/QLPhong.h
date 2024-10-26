#ifndef QLPHONG_H
#define QLPHONG_H
#include "Phong.h"
#include "LinkedList.h"
class QLPhong {
    LinkedList<Phong> DSP; // Danh sach phong
public:
    QLPhong();
    ~QLPhong();

    void themPhong(Phong);
    void xoaPhong(Phong);
    void suaThongTin(string);

    Phong timPhong(time_t, time_t);
};
#endif