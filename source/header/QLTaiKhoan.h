#ifndef QLTAIKHOAN_H
#define QLTAIKHOAN_H

#include "TaiKhoan.h"
#include "LinkedList.h"
class QLTaiKhoan {
    LinkedList<TaiKhoan *> DSTK; // Danh sach tai khoan
public:
    ~QLTaiKhoan();

    void themTaiKhoan(TaiKhoan *tk);
    void xoaTaiKhoan(TaiKhoan *);
    void suaThongTinTaiKhoan(string);
    string kiemTraTaiKhoan(string, string);
    TaiKhoan *getTaiKhoanByID(string);
    LinkedList<TaiKhoan *> &getDSTK();

    friend ostream& operator<<(ostream&, const QLTaiKhoan&);
};
#endif