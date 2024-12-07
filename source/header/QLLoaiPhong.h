#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"
#include "LinkedList.h"
class QLLoaiPhong {
    LinkedList<LoaiPhong *> DSLP; 
public:
    QLLoaiPhong();
    ~QLLoaiPhong();

    void themLoaiPhong(LoaiPhong *); 
    //void xemLoaiPhong();
    void suaThongTin(const string&);
    void xoaLoaiPhong(const string& );

    LoaiPhong *timLoaiPhong(string);
    int soLuongKhach(string);
    int getGiaPhong(string);
    LinkedList<LoaiPhong *>& getDSLP();

    friend ostream& operator<<(ostream&, const QLLoaiPhong&);
};
#endif