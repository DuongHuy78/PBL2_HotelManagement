#include "header/QLKhachSan.h"
int main() {
    // g++ .\stbIml.cpp .\gnk_2D.cpp .\UI.cpp .\LoaiPhong.cpp .\QLLoaiPhong.cpp .\Phong.cpp .\QLPhong.cpp .\DatPhong.cpp .\QLDatPhong.cpp .\TaiKhoan.cpp .\QLTaiKhoan.cpp .\KhachHang.cpp .\QLKhachHang.cpp .\NhanVien.cpp .\QuanLi.cpp .\QLKhachSan.cpp .\main.cpp -lopengl32 -lglew32 -lglfw3 -lfreetype
    QLKhachSan db;
    db.inputTaiKhoan("data/tai_khoan.txt");
    db.inputKhachHang("data/khach_hang.txt");
    db.inputLoaiPhong("data/loaiphong.txt");
    db.inputPhong("data/phong.txt");
    db.inputDatPhong("data/dat_phong.txt");
    system("pause");
    system("cls");
    db.work();
    return 0;
}