#ifndef QLKHACHSAN_H
#define QLKHACHSAN_H
#include <fstream>
#include <sstream>
#include <cctype>
#include "DatPhong.h"
#include "KhachHang.h"
#include "LoaiPhong.h"
#include "Phong.h"
#include "TaiKhoan.h"
#include "QLKhachHang.h"
#include "QLDatPhong.h"
#include "QLLoaiPhong.h"
#include "QLPhong.h"
#include "NhanVien.h"
#include "QuanLi.h"

class QLKhachSan {
    QLKhachHang QLKH;
    QLDatPhong QLDP;
    QLLoaiPhong QLLP;
    QLPhong QLP;
    
    int role;   // Neu role = -1, chua dang nhap
public:
    QLKhachSan();
    ~QLKhachSan();

    bool canReadFile(string);

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

    int getRoleById(string);
    void work();
    NguoiDung *dangNhap();
    void dangXuat(string);
    void kiemTraTraPhong();
    void thongBao(string, string);
    void chuanHoaTen(string &);
};
#endif