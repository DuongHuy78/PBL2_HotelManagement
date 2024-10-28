#ifndef QLKHACHSAN_H
#define QLKHACHSAN_H
#include "QLKhachHang.h"
#include "NhanVien.h"
#include "QuanLi.h"
#include "QLDatPhong.h"
#include "QLLoaiPhong.h"
#include "QLPhong.h"
#include "QLTaiKhoan.h"
#include "UI.h"
class QLKhachSan {
    QLKhachHang QLKH;
    QLTaiKhoan QLTK;
    QLDatPhong QLDP;
    QLLoaiPhong QLLP;
    QLPhong QLP;
    role_value role = UNDEFINED;    
    NhanVien nhanVien;
    QuanLi quanLi;     
public:
    QLKhachSan();
    ~QLKhachSan();

    void inputTaiKhoan(string);
    void inputKhachHang(string);
    void inputLoaiPhong(string);
    void inputPhong(string);
    void inputDatPhong(string);

    void outputTaiKhoan(string);
    void outputKhachHang(string);
    void outputLoaiPhong(string);
    void outputPhong(string);
    void outputDatPhong(string);

    void work();
    NguoiDung *kiemTraDangNhap(string, string);
    void dangXuat();
};
#endif