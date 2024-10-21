#ifndef QLKHACHHANG_H
#define QLKHACHHANG_H
#include "KhachHang.h"
class QLKhachHang {
    KhachHang *DSKH; // Danh sach khach hang
public:
    QLKhachHang();  // Tao danh sach
    ~QLKhachHang();

    void themKhachHang(KhachHang);
    void timKiemKhachHang(string); // Tim kiem theo id và ten
    void suaThongTin(string);
    void xoaKhachHang(KhachHang); // xóa khách hàng theo id và ten
};
#endif