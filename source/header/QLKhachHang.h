#ifndef QLKHACHHANG_H
#define QLKHACHHANG_H
#include "KhachHang.h"
#include "LinkedList.h"
class QLKhachHang {
    LinkedList<KhachHang> DSKH; // Danh sach khach hang
public:
    QLKhachHang();
    ~QLKhachHang();
    LinkedList<KhachHang> &getDanhSachKhachHang();

    void themKhachHang(KhachHang);
    void suaThongTin(string);
    void xoaKhachHang(KhachHang *); 
    string getMaxIDKhachHang();         // Lấy ID khách hàng lớn nhat để tạo ID mới
    string taoIDKhachHang();            // Tạo ID khách hàng mới
    KhachHang *timKiemKhachHang(string);// Tìm kiếm theo ID
};
#endif