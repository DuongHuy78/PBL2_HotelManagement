#include "./header/QLKhachSan.h"


QLKhachSan::QLKhachSan() {
    
}

QLKhachSan::~QLKhachSan() {

}

void QLKhachSan::inputTaiKhoan(string path) {
    // Này phải viết hàm đọc dữ liệu từ file, nhưng mà không ai viết nên t thêm chay

    TaiKhoan account("U-00001", "nguyennhatking", "12345678");
    TaiKhoan account2("M-00001", "qlnguyennhatking", "12345678");
    TaiKhoan account3("S-00001", "nvnguyennhatking", "12345678");

    quanLi.setIDQuanLi("M-00001");

    nhanVien.setIDNhanVien("S-00001");

    time_t ngaySinh = Utils::stringToDate("2005-01-01");
    KhachHang newUser("U-00001", "nguyen nhat hoang", ngaySinh, "0905123456", true);
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
    NguoiDung *p;
    while(role == UNDEFINED) {
        p = dangNhap();
        if(p != NULL) p->work();
    }
}

NguoiDung *QLKhachSan::dangNhap() {
    string username, password;
    cout << "Nhap username: ";
    cin >> username;
    cout << "Nhap password: ";
    cin >> password;
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
