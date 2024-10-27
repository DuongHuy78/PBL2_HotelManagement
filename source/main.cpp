#include <iostream>
#include "./header/QLKhachSan.h"
using namespace std;

int main() {
    // g++ .\DatPhong.cpp .\KhachHang.cpp .\LoaiPhong.cpp .\NhanVien.cpp .\Phong.cpp .\QLKhachSan.cpp .\QuanLi.cpp .\main.cpp .\TaiKhoan.cpp .\QLDatPhong.cpp .\QLKhachHang.cpp .\QLLoaiPhong.cpp .\QLPhong.cpp
    QLKhachSan db;
    
    QLLoaiPhong P;
    P.AddRangeLoaiPhong("loaiphong.txt");
    db.inputTaiKhoan("data/TaiKhoan.txt");
    db.inputKhachHang("data/KhachHang.txt");
    db.inputLoaiPhong("data/LoaiPhong.txt");
    db.inputPhong("data/Phong.txt");
    db.inputDatPhong("data/DatPhong.txt");
    db.work();
    return 0;
}