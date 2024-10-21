#ifndef KHACHHANG_H
#define KHACHHANG_H
#include "NguoiDung.h"
#include "Phong.h"
#include "QLKhachSan.h"

class KhachHang:public NguoiDung {
    string IDKhachHang;
    string hoTen;
    time_t ngaySinh;
    string soDienThoai;
    bool gioiTinh; 
public:
    KhachHang(string, string, time_t, string, bool);
    KhachHang(const KhachHang&);
    ~KhachHang();

    string getIDKhachHang() const;
    string getHoTen() const;
    time_t getNgaySinh() const;
    string getSoDienThoai() const;
    bool getGioiTinh() const; 

    void setIDKhachHang(string);
    void setHoTen(string);
    void setNgaySinh(time_t);
    void setSoDienThoai(string);
    void setGioiTinh(bool); 

    void menuSuaThongTin();                             //menu sửa thông tin
    void suaThongTin();
    void work();                            //in ra thông tin
    void huyDatPhong(string);             //hủy đặt phòng
};
#endif