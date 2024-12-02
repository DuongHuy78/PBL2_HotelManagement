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
    string getMaxIDKhachHang();         // Lấy ID khách hàng lớn nhat để tạo ID mới
    string taoIDKhachHang();            // Tạo ID khách hàng mới
    KhachHang *timKiemKhachHang(string);// Tìm kiếm theo ID
    KhachHang *timKiemKhachHangSDT(string); // Tìm kiếm theo số điện thoại
    KhachHang nhapThongTin();

    LinkedList<KhachHang> &getDanhSachKhachHang();
    
    friend ostream& operator<<(ostream&, const QLKhachHang&);
};
#endif