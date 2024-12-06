#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H
#include "Utils.h"
#include "TaiKhoan.h"
class TaiKhoan;
class NguoiDung {
protected:
    string ID;
    TaiKhoan *taiKhoan;
    virtual void setTaiKhoan(TaiKhoan *) = 0;
public:
    virtual user_option_value work() = 0;
    friend TaiKhoan;
};
#endif