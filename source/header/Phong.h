#ifndef PHONG_H
#define PHONG_H
#include <iostream>
using namespace std;
class Phong {
    string maPhong; 
    string loaiPhong;
    time_t ngayNhan = 0;
    time_t ngayTra = 0;
public:
    Phong(string, string);
    Phong(const Phong&);
    ~Phong();

    string getMaPhong() const;
    string getLoaiPhong() const;

    void setMaPhong(string);
    void setLoaiPhong(string);
};
#endif