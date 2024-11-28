#ifndef PHONG_H
#define PHONG_H
#include "Utils.h"
#include "LoaiPhong.h"
#define MAX_MAPHONG 7
class Phong {
    string maPhong; 
    string loaiPhong; 
public:
    Phong();
    Phong(string, string); // phòng theo data (mã phòng, loại phòng)
    Phong(const Phong&);
    ~Phong();

    string getMaPhong() const;
    string getLoaiPhong() const;

    void setMaPhong(string);
    void setLoaiPhong(string);

    Phong nhapPhongMoi();
    void menuSuaThongTin();
    void capNhatThongTin();
    void xuatThongTin();
    
    friend ostream& operator<<(ostream&, const Phong&);
};
#endif