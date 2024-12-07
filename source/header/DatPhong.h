#ifndef DATPHONG_H
#define DATPHONG_H
#include "Utils.h"
#include "Phong.h"
#include "KhachHang.h"
class Phong;
class KhachHang;
class DatPhong {
    string maDatPhong; // PK

    Phong *phong;
    KhachHang *khachHang;

    time_t ngayNhan;
    time_t ngayTra;
    int soLuongKhach;
    int donGia;
    
public:
    DatPhong();
    DatPhong(string, time_t, time_t, int, int);
    DatPhong(const DatPhong &);

    string getMaDatPhong() const; 
    Phong *getPhong() const;
    KhachHang *getKhachHang() const;
    time_t getNgayNhan() const;
    time_t getNgayTra() const;
    int getSoLuongKhach() const;
    int getDonGia() const;
    int tongTien();

    void setMaDatPhong(string);
    void setPhong(Phong *);
    void setKhachHang(KhachHang *);
    void setNgayNhanAndNgayTra(time_t, time_t);
    void setSoLuongKhach(int);
    void setDonGia(int);
    
    friend ostream& operator<<(ostream&, const DatPhong&);
    friend Phong;
    friend KhachHang;
};
#endif