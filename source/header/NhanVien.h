#ifndef NHANVIEN_H
#define NHANVIEN_H
#include "NguoiDung.h"
#include "Utils.h"
#include "QLKhachHang.h"
#include "QLDatPhong.h"
class NhanVien: public NguoiDung {
    string IDNhanVien;
    QLKhachHang *DSKH;
    QLDatPhong *DSDP;
public:
    NhanVien();
    NhanVien(string);
    ~NhanVien();

    void setDSKH(QLKhachHang*);
    void setDSDP(QLDatPhong*);
    string getIDNhanVien() const;
    void setIDNhanVien(string);
    void themKhachHang();
    void themDatPhong();
    bool work();
    friend ostream& operator<<(ostream& out, const NhanVien&);
};
#endif