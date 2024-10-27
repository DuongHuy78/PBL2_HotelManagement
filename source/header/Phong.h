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
    Phong();
    ~Phong();
    Phong(string, string); // phong theo data (mã phòng, loại phòng)
    Phong(const Phong&);

    string getMaPhong() const;
    string getLoaiPhong() const;

    void setMaPhong(string);
    void setLoaiPhong(string);
};

#endif