#ifndef KHACHHANG_H
#define KHACHHANG_H
#include "NguoiDung.h"
#include "DatPhong.h"
#include "LinkedList.h"
#include "TaiKhoan.h"
#include "Utils.h"
class DatPhong;
class TaiKhoan;
class KhachHang: public NguoiDung {
    string hoTen;
    time_t ngaySinh;
    string soDienThoai;
    gender_value gioiTinh; 
    LinkedList<DatPhong *> danhSachDatPhong;
    void themDatPhong(DatPhong *);  
    void setTaiKhoan(TaiKhoan *);
public:
    KhachHang();
    KhachHang(string, string, time_t, string, gender_value);
    KhachHang(const KhachHang&);
    ~KhachHang();

    string getIDKhachHang() const;
    string getHoTen() const;
    time_t getNgaySinh() const;
    string getSoDienThoai() const;
    gender_value getGioiTinh() const; 
    LinkedList<DatPhong *> &getDanhSachDatPhong() const;

    bool setIDKhachHang(string);
    bool setHoTen(string);
    bool setNgaySinh(time_t);
    bool setSoDienThoai(string);
    bool setGioiTinh(gender_value); 

    void menuSuaThongTin();
    void suaThongTin();
    user_option_value work();
    
    friend ostream& operator<<(ostream&, const KhachHang&);
    friend DatPhong;
    friend TaiKhoan;
};
#endif