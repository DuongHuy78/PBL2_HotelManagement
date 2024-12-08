#ifndef PHONG_H
#define PHONG_H
#include "Utils.h"
#include "LoaiPhong.h"
#include "DatPhong.h"
#define MAX_MAPHONG 7
class LoaiPhong;
class DatPhong;
class Phong {
    string maPhong; 
    LoaiPhong *loaiPhong;
    LinkedList<DatPhong *> danhSachDatPhong;
    void themDatPhong(DatPhong *);
public:
    Phong();
    Phong(string);
    Phong(const Phong&);

    string getMaPhong() const;
    LoaiPhong *getLoaiPhong() const;

    void setMaPhong(string);
    void setLoaiPhong(LoaiPhong *);

    void menuSuaThongTin();
    
    friend ostream& operator<<(ostream&, const Phong&);
    friend LoaiPhong;
    friend DatPhong;
};
#endif