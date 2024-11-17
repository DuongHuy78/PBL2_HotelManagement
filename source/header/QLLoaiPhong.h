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

    void themLoaiPhong(LoaiPhong); 
    void xemLoaiPhong();
    void suaThongTinLoaiPhong(const string&);
    void xoaLoaiPhong(const string& );

    void capNhatFile(LoaiPhong*, string); 
    LoaiPhong *timLoaiPhong(string);
    void QLLoaiPhong_Choice();
    int soLuongKhach(string);
    int getGiaPhong(string);
     
};
#endif