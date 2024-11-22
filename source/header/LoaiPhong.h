#ifndef LOAIPHONG_H
#define LOAIPHONG_H
#include "Utils.h"
#define MAX_IDLOAIPHONG 7
class LoaiPhong {
    string loaiPhong;   // S, D, D2, T, F, F2
    int loaiGiuong;  // 1, 2
    int soLuongKhach;   // hiểu là số lượng khách tối đa trong 1 phòng
    int dienTich;
    int giaPhong;
    string moTaPhong;
public:
    LoaiPhong();
    LoaiPhong(string, int, int, int, int, string);
    LoaiPhong(const LoaiPhong&);
    ~LoaiPhong();
    friend ostream& operator<<(ostream& out, const LoaiPhong&);

    string getLoaiPhong() const; // mã loại phòng
    int getLoaiGiuong() const; // 1, 2, 12
    int getSoLuongKhach() const; 
    int getGiaPhong() const;
    int getDienTich() const;
    string getMoTaPhong() const;

    bool setLoaiPhong(string);
    bool setLoaiGiuong(int);
    bool setSoLuongKhach(int);
    bool setDienTich(int);
    bool setGiaPhong(int);
    bool setMoTaPhong(string);

    void NhapLoaiPhongMoi();
    void menuCapNhat();
    void capNhatThongTin();
    void xuatThongTin();
};
#endif