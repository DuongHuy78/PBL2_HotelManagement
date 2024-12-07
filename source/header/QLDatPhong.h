#ifndef QLDATPHONG_H
#define QLDATPHONG_H
#include "DatPhong.h"
#include "QLKhachHang.h"
#include "QLLoaiPhong.h"
#include "QLphong.h"
#include "LinkedList.h"
class QLDatPhong {
    LinkedList<DatPhong *> DSDP; // Danh sach dat phong
    // QLLoaiPhong* DSLP; // Danh sach loai phong
    // QLPhong* DSP; // Danh sach phong
    // QLKhachHang* DSKH; // Danh sach khach hang
    // string currentID;
    // role_value role;
public:
    ~QLDatPhong();
    // void setDSLP(QLLoaiPhong*);
    // void setDSP(QLPhong*);
    // void setDSKH(QLKhachHang*);
    // void setcurrentID(string);
    // void setRole(role_value);

    void themDatPhong(DatPhong *);
    void xoaDatPhong(DatPhong *);
    DatPhong *timKiemDatPhong(string);
    string getMaxMaDatPhong();
    string taoMaDatPhong();
    
    LinkedList<DatPhong *> &getDSDP();
    
    friend ostream& operator<<(ostream&, const QLDatPhong&);
};
#endif