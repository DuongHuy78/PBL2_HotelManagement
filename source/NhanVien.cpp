#include "./header/NhanVien.h"
NhanVien::NhanVien() {

}

NhanVien::~NhanVien() {

}

string NhanVien::getIDNhanVien() const {
    return this->IDNhanVien;
}

void NhanVien::setIDNhanVien(string ID) {
    this->IDNhanVien = ID;
}

void NhanVien::work() {
    cout << "Da dang nhap vao tai khoan nhan vien" << endl;
}