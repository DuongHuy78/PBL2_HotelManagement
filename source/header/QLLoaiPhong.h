#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"
#include "LinkedList.h"

class QLLoaiPhong {
    LinkedList <LoaiPhong> DSLP; // danh sach loai phong
public:
    QLLoaiPhong();
    ~QLLoaiPhong();
    void AddRangeLoaiPhong(string); // đọc dữ liệu đầu vào và trả về danh sách loại phòng

    void themLoaiPhong(LoaiPhong);

    void xoaLoaiPhong(LoaiPhong);
    void suaThongTin(string);
};
#endif