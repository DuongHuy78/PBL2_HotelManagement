#include "./header/QLKhachSan.h"

QLKhachSan::QLKhachSan() {
    UI_init();
    current_Data = this;
}

QLKhachSan::~QLKhachSan() {

}

void QLKhachSan::inputTaiKhoan(string path) {
    // Này phải viết hàm đọc dữ liệu từ file, nhưng mà không ai viết nên t thêm chay

    TaiKhoan account("100001", "nguyennhatking", "12345678");
    TaiKhoan account2("000001", "qlnguyennhatking", "12345678");
    TaiKhoan account3("200001", "nvnguyennhatking", "12345678");

    quanLi.setIDQuanLi("000001");

    nhanVien.setIDNhanVien("200001");

    time_t ngaySinh = Utils::stringToDate("2005-01-01");
    KhachHang newUser("100001", "nguyen nhat hoang", ngaySinh, "0905123456", true);
    this->QLKH.themKhachHang(newUser);
    
    this->QLTK.themTaiKhoan(account);
    this->QLTK.themTaiKhoan(account2);
    this->QLTK.themTaiKhoan(account3);
}

void QLKhachSan::inputKhachHang(string) {

}

void QLKhachSan::inputLoaiPhong(string) {

}

void QLKhachSan::inputPhong(string) {

}

void QLKhachSan::inputDatPhong(string) {

}


void QLKhachSan::outputTaiKhoan(string) {

}

void QLKhachSan::outputKhachHang(string) {

}

void QLKhachSan::outputLoaiPhong(string) {

}

void QLKhachSan::outputPhong(string) {

}

void QLKhachSan::outputDatPhong(string) {

}

void QLKhachSan::work() {
    gnk_Window_Loop();
}

NguoiDung *QLKhachSan::dangNhap(string username, string password) {
    string ID = QLTK.kiemTraTaiKhoan(username, password);
    if(ID != "") {
        if(ID == quanLi.getIDQuanLi()) {
            role = QUANLI;
            return &quanLi;
        }
        if(ID == nhanVien.getIDNhanVien()) {
            role = NHANVIEN;
            return &nhanVien;
        }
        role = KHACHHANG;
        return QLKH.timKiemKhachHang(ID);
    }
    return NULL;
}

void QLKhachSan::dangXuat() {
    role = UNDEFINED;
}
