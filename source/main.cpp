#include "header/QLKhachSan.h"
int main() {
    cin.sync_with_stdio(false);
    // g++ .\stbIml.cpp .\gnk_2D.cpp .\UI.cpp .\LoaiPhong.cpp .\QLLoaiPhong.cpp .\Phong.cpp .\QLPhong.cpp .\DatPhong.cpp .\QLDatPhong.cpp .\TaiKhoan.cpp .\QLTaiKhoan.cpp .\KhachHang.cpp .\QLKhachHang.cpp .\NhanVien.cpp .\QuanLi.cpp .\QLKhachSan.cpp .\main.cpp -lopengl32 -lglew32 -lglfw3 -lfreetype
    QLKhachSan db;
    db.inputTaiKhoan("data/tai_khoan.txt");
    db.inputKhachHang("data/khach_hang.txt");
    db.inputLoaiPhong("data/loaiphong.txt");
    db.inputPhong("data/phong.txt");
    db.inputDatPhong("data/dat_phong.txt");
    Utils::pauseConsole();
    db.work();
    cout << "Saving data..." << endl;
    db.outputTaiKhoan("data/tai_khoan.txt");
    db.outputKhachHang("data/khach_hang.txt");
    db.outputLoaiPhong("data/loaiphong.txt");
    db.outputPhong("data/phong.txt");
    db.outputDatPhong("data/dat_phong.txt");
    return 0;
}