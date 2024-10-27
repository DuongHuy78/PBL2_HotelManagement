#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"
#include "LinkedList.h"
class QLLoaiPhong {
    LinkedList<LoaiPhong> DSLP; // Danh sach loai phong
public:
    QLLoaiPhong();
    ~QLLoaiPhong();

    void themLoaiPhong(LoaiPhong);
    void xoaLoaiPhong(LoaiPhong);
    void suaThongTin(string);
};
#endif