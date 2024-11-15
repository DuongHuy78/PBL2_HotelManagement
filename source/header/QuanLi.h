#ifndef QUANLI_H
#define QUANLI_H
#include "NguoiDung.h"
#include "QLLoaiPhong.h"
#include "QLPhong.h"
#include "QLDatPhong.h"
#include "LinkedList.h"
#include "Utils.h"
class QuanLi: public NguoiDung {
    string IDQuanLi;
    QLLoaiPhong *DSLP;
    QLPhong *DSP;
    QLDatPhong *DSDP;
public:
    QuanLi();
    ~QuanLi();

    string getIDQuanLi() const;
    void setIDQuanLi(string);
    void setDSLP(QLLoaiPhong*);
    void setDSP(QLPhong*);
    void setDSDP(QLDatPhong*);
    
    friend const string& operator+(const int&, const string&); 
    void taoLoaiPhong();
    void suaLoaiPhong(const string&);
    void xoaLoaiPhong(const string&);
    void taoPhong();
    void suaPhong(const string&);
    void xoaPhong(const string&);
    int thongKe(string,string);
    void xemDanhSachLuaChonXemDoanhThu();
    void xemDoanhThu();
    void work();
};
#endif