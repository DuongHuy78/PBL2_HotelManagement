#include "./header/Phong.h"

Phong::Phong()
{

}

Phong::~Phong() 
{
}

//Constructor copy
Phong::Phong(const Phong& other)
 :maPhong(other.maPhong), loaiPhong(other.loaiPhong) {}

// Constructor có tham số
Phong::Phong(string MaPhong, string LoaiPhong) : maPhong(MaPhong), loaiPhong(LoaiPhong) {}

// Hàm get
string Phong::getMaPhong() const {
    return this->maPhong;
}

string Phong::getLoaiPhong() const {
    return this->loaiPhong;
}


void Phong::setMaPhong(string MP) {
    this->maPhong = MP;
}

void Phong::setLoaiPhong(string LP) {
    this->loaiPhong = LP;
}
