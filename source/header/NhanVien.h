#ifndef NHANVIEN_H
#define NHANVIEN_H
#include "NguoiDung.h"
#include "Utils.h"
#include "QLKhachHang.h"
class NhanVien: public NguoiDung {
    string IDNhanVien;
public:
    NhanVien();
    NhanVien(string);
    ~NhanVien();

    string getIDNhanVien() const;
    void setIDNhanVien(string);
    void themKhachHang();
    void themDatPhong();
    void work();
};
#endif