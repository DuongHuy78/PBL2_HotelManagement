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
    string currentID;
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
    NguoiDung *dangNhap(string, string);
    void dangXuat();

    /**
     * Duyệt qua 'danh sách đặt phòng' kiểm tra các phòng đang được đặt
     * Từ đó đặt trạng thái phòng của các phòng đó là bận 
     * Sau đó in ra danh sách những phòng không có trạng thái bận
     */
    // void roomAvailability(time_t, time_t);
};
#endif