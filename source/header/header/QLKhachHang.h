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
    string getMaxIDKhachHang(); // Lay ID khach hang lon nhat để tạo ID mới
    string taoIDKhachHang(); // Tao ID khach hang moi
    KhachHang *timKiemKhachHang(string); // Tim kiem theo ID
};
#endif