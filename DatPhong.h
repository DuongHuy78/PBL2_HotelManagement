#include <iostream>
#include <time.h>
using namespace std;
class DatPhong {
    string maDatPhong; // PK
    string maPhong;
    string IDKhachHang;
    time_t ngayNhan;
    time_t ngayTra;
    int soLuongKhach;
    int donGia;
public:
    DatPhong(string, string, string, time_t, time_t, int, int);
    DatPhong(const DatPhong &);
    ~DatPhong();

    void getMaDatPhong() const; 
    void getMaPhong() const;
    void getIDKhachHang() const;
    void getNgayNhan() const;
    void getNgayTra() const;
    void getSoLuongKhach() const;
    void getDonGia() const;

    string setMaDatPhong(string);
    string setMaPhong(string);
    string setIDKhachHang(string);
    time_t setNgayNhan(time_t);
    time_t setNgayTra(time_t);
    int setSoLuongKhach(int);
    int setDonGia(int);

    void xemThongTin();
};