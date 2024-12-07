#ifndef QUANLI_H
#define QUANLI_H
#include "NguoiDung.h"
#include "LinkedList.h"
#include "Utils.h"
#include "TaiKhoan.h"
class TaiKhoan;
class QuanLi: public NguoiDung {
    void setTaiKhoan(TaiKhoan *);
public:
    QuanLi();

    string getIDQuanLi() const;
    void setIDQuanLi(string);
    // void xemDanhSachLuaChonXemDoanhThu();
    // void xemDoanhThu();
    user_option_value work();
    friend ostream& operator<<(ostream&, QuanLi&);
    friend TaiKhoan;
};
#endif