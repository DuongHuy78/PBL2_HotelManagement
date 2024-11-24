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
    role_value role = UNDEFINED_ROLE;    
    NhanVien nhanVien;
    QuanLi quanLi;
    // string currentID; 
    NguoiDung *current_user = nullptr;
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
    bool dangNhap();
    void dangXuat();
    sign_up_return_value taoTaiKhoan(string, string, string, string, string, string);

    void roomAvailability(time_t, time_t, int, LinkedList<Phong *> &);
    void bookingRoom();
};
#endif