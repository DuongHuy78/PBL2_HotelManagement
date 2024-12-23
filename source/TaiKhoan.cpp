#include "./header/TaiKhoan.h"

TaiKhoan::TaiKhoan() {
    this->ID = "";
    this->username = "";
    this->password = "";
}

TaiKhoan::TaiKhoan(string ID, string username, string password) {
    this->ID = ID;
    this->username = username;
    this->password = password;
}

TaiKhoan::TaiKhoan(const TaiKhoan&other) {
    this->ID = other.ID;
    this->username = other.username;
    this->password = other.password;
}

string TaiKhoan::getUsername() const {
    return this->username;
}

string TaiKhoan::getPassword() const {
    return this->password;
}

string TaiKhoan::getID() const {
    return this->ID;
}


void TaiKhoan::setUsername(string username) {
    this->username = username;
}

void TaiKhoan::setPassword(string password) {
    this->password = password;
}

void TaiKhoan::setID(string ID) {
    this->ID = ID;
}

void TaiKhoan::setNguoiDung(NguoiDung* nguoiDung) {
    this->nguoiDung = nguoiDung;
    nguoiDung->setTaiKhoan(this);
}

NguoiDung* TaiKhoan::getNguoiDung() const {
    try {
        if(this->nguoiDung == nullptr) {
            throw "TaiKhoan::getNguoiDung::NguoiDung khong ton tai!";
        }
        return this->nguoiDung;
    }
    catch(const char* msg) {
        cerr << msg << endl;
        return nullptr;
    }
}

role_value TaiKhoan::getRole() const {
    if(this->ID[0] == '1') return KHACHHANG;
    if(this->ID[0] == '2') return NHANVIEN;
    if(this->ID[0] == '3') return QUANLI;
    return UNDEFINED_ROLE;
}

ostream& operator<<(ostream& os, const TaiKhoan& tk) {
    Utils::outputData("-----------THONG-TIN-TAI-KHOAN---------\n", CONSOLE);
    Utils::outputData("ID: ", CONSOLE);
    Utils::outputData(tk.ID, CONSOLE_OR_UI);
    Utils::outputData("\n", CONSOLE_OR_UI);
    Utils::outputData("Username: ", CONSOLE);
    Utils::outputData(tk.username, CONSOLE_OR_UI);
    Utils::outputData("\n", CONSOLE_OR_UI);
    Utils::outputData("Password: ", CONSOLE);
    Utils::outputData(tk.password, CONSOLE_OR_UI);
    Utils::outputData("\n", CONSOLE_OR_UI);
    Utils::outputData("-----NhatHoang-DuongHuy-ThaoDuyen-----\n", CONSOLE);
    return os;
}
