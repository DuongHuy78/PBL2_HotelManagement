#ifndef QLKHACHHANG_H
#define QLKHACHHANG_H
#include "KhachHang.h"
class QLKhachHang {
    KhachHang *DSKH; // Danh sach khach hang
public:
    QLKhachHang();  // Tao danh sach
    ~QLKhachHang();

    void themKhachHang(KhachHang);
    void timKiemKhachHang(string); // Tim kiem theo id hay ten?
    void suaThongTin(string);
    void xoaKhachHang(KhachHang); // string?
};
#endif