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

TaiKhoan::~TaiKhoan() {

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

role_value TaiKhoan::getRole() const {
    if(this->ID[0] == '1') return KHACHHANG;
    if(this->ID[0] == '2') return NHANVIEN;
    if(this->ID[0] == '3') return QUANLI;
    return UNDEFINED_ROLE;
}
