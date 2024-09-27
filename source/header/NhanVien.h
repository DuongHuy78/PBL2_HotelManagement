#ifndef NHANVIEN_H
#define NHANVIEN_H
#include "NguoiDung.h"
#include "QLKhachHang.h"
class NhanVien: public NguoiDung {
    string IDNhanVien;
public:
    NhanVien();
    ~NhanVien();

    KhachHang layThongTin();    
    void themKhachHang(QLKhachHang &, KhachHang);
    void timKiemKhachHang(QLKhachHang &, string);

    void work();
};
#endif