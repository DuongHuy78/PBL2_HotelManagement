#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"
#include "LinkedList.h"
class QLLoaiPhong {
    LinkedList<LoaiPhong> DSLP; 
public:
    QLLoaiPhong();
    ~QLLoaiPhong();

    void AddRangeLoaiPhong(string);

    void themLoaiPhong(const LoaiPhong&); 
    void xemLoaiPhong();
    void suaThongTin(const string&);
    void xoaLoaiPhong(const string& );

    void capNhatFile(LoaiPhong*, string); 
    LoaiPhong *timLoaiPhong(string);
    int soLuongKhach(string);
    int getGiaPhong(string);
    LinkedList<LoaiPhong>& getDSLP();

    friend ostream& operator<<(ostream&, const QLLoaiPhong&);
};
#endif