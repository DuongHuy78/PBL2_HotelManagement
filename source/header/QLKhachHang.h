#ifndef QLKHACHHANG_H
#define QLKHACHHANG_H
#include "KhachHang.h"
#include "LinkedList.h"
class QLKhachHang {
    LinkedList<KhachHang> DSKH; // Danh sach khach hang
public:
    QLKhachHang();
    ~QLKhachHang();

    void themKhachHang(KhachHang);
    void suaThongTin(string);
    void xoaKhachHang(KhachHang *); 

    KhachHang *timKiemKhachHang(string); // Tim kiem theo ID
};
#endif