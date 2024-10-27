#ifndef LOAIPHONG_H
#define LOAIPHONG_H
#include "Utils.h"
class LoaiPhong {
    string IDLoaiPhong;  // PK
    int giaPhong;
    string moTaPhong;
    int soLuongKhach;
public:
    LoaiPhong();
    LoaiPhong(string, int, string, int);
    LoaiPhong(const LoaiPhong&);
    ~LoaiPhong();

    int getLoaiPhong() const;
    int getLoaiGiuong() const;
    int getGiaPhong() const;
    string getMoTaPhong() const;
    int getSoLuongKhach() const;

    void setLoaiPhong(int);
    void setLoaiGiuong(int);
    void setGiaPhong(int);
    void setMoTaPhong(string);
    void setSoLuongKhach(int);
};
#endif