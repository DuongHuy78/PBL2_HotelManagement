#ifndef NHANVIEN_H
#define NHANVIEN_H
#include "NguoiDung.h"
#include "Utils.h"
// #include "QLKhachHang.h"
// #include "QLDatPhong.h"
#include "TaiKhoan.h"
class TaiKhoan;
class NhanVien: public NguoiDung {
    void setTaiKhoan(TaiKhoan *);
public:
    NhanVien();
    NhanVien(string);

    string getIDNhanVien() const;
    void setIDNhanVien(string);

    user_option_value work();
    friend ostream& operator<<(ostream& out, const NhanVien&);
    friend TaiKhoan;
};
#endif