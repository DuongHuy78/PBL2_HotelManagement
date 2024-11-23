#ifndef KHACHHANG_H
#define KHACHHANG_H
#include "NguoiDung.h"
#include "Utils.h"
class KhachHang:public NguoiDung {
    string IDKhachHang; // PK
    string hoTen;
    time_t ngaySinh;
    string soDienThoai;
    gender_value gioiTinh; 
public:
    KhachHang();
    KhachHang(string, string, time_t, string, gender_value);
    KhachHang(const KhachHang&);
    ~KhachHang();

    string getIDKhachHang() const;
    string getHoTen() const;
    time_t getNgaySinh() const;
    string getSoDienThoai() const;
    bool getGioiTinh() const; 

    bool setIDKhachHang(string);
    bool setHoTen(string);
    bool setNgaySinh(time_t);
    bool setSoDienThoai(string);
    bool setGioiTinh(gender_value); 

    void menuSuaThongTin();
    void suaThongTin();
    bool work();
    
    friend ostream& operator<<(ostream&, const KhachHang&);
};
#endif