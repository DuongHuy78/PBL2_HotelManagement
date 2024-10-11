#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"

class QLLoaiPhong {
    LoaiPhong *DSLP; // danh sach loai phong
public:
    QLLoaiPhong();
    ~QLLoaiPhong();

    void themLoaiPhong(LoaiPhong);
    void xoaLoaiPhong(LoaiPhong);
    void suaThongTin(string);
};
#endif