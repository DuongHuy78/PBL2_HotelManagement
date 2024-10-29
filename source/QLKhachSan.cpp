#include "./header/QLKhachSan.h"

QLKhachSan::QLKhachSan() {
    UI_init();
    current_Data = this;
}

QLKhachSan::~QLKhachSan() {

}

void QLKhachSan::inputTaiKhoan(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    int index = 0;
    string line, username, password, ID;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        username = Utils::getSubstringUntilX(line, index, ',');
        password = Utils::getSubstringUntilX(line, index, ',');
        ID       = Utils::getSubstringUntilX(line, index, '\n');
        TaiKhoan newTaiKhoan(ID, username, password);
        QLTK.themTaiKhoan(newTaiKhoan);
        role_value role = newTaiKhoan.getRole();
        if(role == NHANVIEN) {
            nhanVien.setIDNhanVien(ID);
        } 
        else if(role == QUANLI) {
            quanLi.setIDQuanLi(ID);
        }
        index = 0;
    }  
}

void QLKhachSan::inputKhachHang(string path) {
ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    int index = 0;
    string line, ID, name, birthday, phone, gender;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        ID       = Utils::getSubstringUntilX(line, index, ',');
        name     = Utils::getSubstringUntilX(line, index, ',');
        birthday = Utils::getSubstringUntilX(line, index, ',');
        phone    = Utils::getSubstringUntilX(line, index, ',');
        gender   = Utils::getSubstringUntilX(line, index, '\n');
        gender_value genVal;
        if(gender == "Nam") genVal = NAM;
        else if(gender == "Nu") genVal = NU;
        else genVal = UNDEFINED_GENDER;
        KhachHang newKhachHang(ID, name, Utils::stringToDate(Utils::trim(birthday)), phone, genVal);
        QLKH.themKhachHang(newKhachHang);
        index = 0;
    }  
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
    role = UNDEFINED_ROLE;
}
