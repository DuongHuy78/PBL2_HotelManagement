#ifndef DATPHONG_H
#define DATPHONG_H
#include "Utils.h"
class DatPhong {
    string maDatPhong; // PK
    string maPhong;
    string IDKhachHang;
    time_t ngayNhan;
    time_t ngayTra;
    int soLuongKhach;
    int donGia;
public:
    DatPhong();
    DatPhong(string, string, string, time_t, time_t, int, int);
    DatPhong(const DatPhong &);
    ~DatPhong();

    string getMaDatPhong() const; 
    string getMaPhong() const;
    string getIDKhachHang() const;
    time_t getNgayNhan() const;
    time_t getNgayTra() const;
    int getSoLuongKhach() const;
    int getDonGia() const;

    void setMaDatPhong(string);
    void setMaPhong(string);
    void setIDKhachHang(string);
    void setNgayNhan(time_t);
    void setNgayTra(time_t);
    void setSoLuongKhach(int);
    void setDonGia(int);
    void work();
};
#endif