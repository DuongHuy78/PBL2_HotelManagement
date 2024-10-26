#ifndef PHONG_H
#define PHONG_H
#include "Utils.h"
class Phong {
    string maPhong; 
    string loaiPhong; 
public:
    Phong();
    Phong(string, string);
    Phong(const Phong&);
    ~Phong();

    string getMaPhong() const;
    string getLoaiPhong() const;

    void setMaPhong(string);
    void setLoaiPhong(string);
};
#endif