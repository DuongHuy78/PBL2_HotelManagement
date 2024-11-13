#ifndef QLDATPHONG_H
#define QLDATPHONG_H
#include "DatPhong.h"
#include "KhachHang.h"
#include "Phong.h"
#include "LinkedList.h"
class QLDatPhong {
    LinkedList<DatPhong> DSDP; // Danh sach dat phong
public:
    QLDatPhong();
    ~QLDatPhong();

    void themDatPhong(DatPhong);
    void xoaDatPhong(DatPhong *);
    DatPhong *timKiemDatPhong(string);
    string getMaxMaDatPhong();
    string taoMaDatPhong();

    Node<DatPhong> *getHead();
    LinkedList<DatPhong> &getDanhSachDatPhong();
    DatPhong nhapThongTin();
};
#endif