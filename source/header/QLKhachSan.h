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
struct loaiPhongAvailable {
    LoaiPhong *loaiphong = nullptr;
    int amount = 0;
};

class QLKhachSan {
    QLKhachHang QLKH;
    QLTaiKhoan QLTK;
    QLDatPhong QLDP;
    QLLoaiPhong QLLP;
    QLPhong QLP;
    role_value role = UNDEFINED_ROLE;    
    NhanVien nhanVien;
    QuanLi quanLi;
    NguoiDung *current_user = nullptr;
public:
    QLKhachSan();

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

    void requestHandling(user_option_value);

    void roomAvailability(time_t, time_t, int, LinkedList<Phong *> &);
    void searchTypeRoom(string &, string &, string &, LinkedList<Phong *> &, LinkedList<loaiPhongAvailable> &);
    void bookingRoom(const string &, const string &, const string &, LinkedList<Phong *> &, LinkedList<loaiPhongAvailable> &);
    void list_Type_Room_Available();
    void list_Room_Available();
    void list_all_type_room();
    role_value getCurrentRole();
    bool GuestExist(string);
    void xemDanhSachLuaChonXemDoanhThu();
    int thongKe(string, string);
};

#endif