#include "header/QLKhachSan.h"
int main() {
    // g++ .\LoaiPhong.cpp .\QLLoaiPhong.cpp .\Phong.cpp .\QLPhong.cpp .\DatPhong.cpp .\QLDatPhong.cpp .\TaiKhoan.cpp .\QLTaiKhoan.cpp .\KhachHang.cpp .\QLKhachHang.cpp .\NhanVien.cpp .\QuanLi.cpp .\QLKhachSan.cpp .\main.cpp
    QLKhachSan db;
    db.inputTaiKhoan("data/TaiKhoan.txt");
    db.inputKhachHang("data/KhachHang.txt");
    db.inputLoaiPhong("data/LoaiPhong.txt");
    db.inputPhong("data/Phong.txt");
    db.inputDatPhong("data/DatPhong.txt");
    db.work();
    return 0;
}