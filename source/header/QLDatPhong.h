#ifndef QLDATPHONG_H
#define QLDATPHONG_H
#include "DatPhong.h"
#include "QLKhachHang.h"
#include "QLLoaiPhong.h"
#include "QLphong.h"
#include "LinkedList.h"
class QLDatPhong {
    LinkedList<DatPhong *> DSDP; // Danh sach dat phong
public:
    ~QLDatPhong();
    
    void themDatPhong(DatPhong *);
    void xoaDatPhong(DatPhong *);
    DatPhong *timKiemDatPhong(string);
    string getMaxMaDatPhong();
    string taoMaDatPhong();
    
    LinkedList<DatPhong *> &getDSDP();
    
    friend ostream& operator<<(ostream&, const QLDatPhong&);
};
#endif