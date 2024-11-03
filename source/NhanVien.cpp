#include "./header/NhanVien.h"
NhanVien::NhanVien() {
    IDNhanVien = "";
}

NhanVien::~NhanVien() {

}

string NhanVien::getIDNhanVien() const {
    return this->IDNhanVien;
}

void NhanVien::setIDNhanVien(string ID) {
    this->IDNhanVien = ID;
}

void NhanVien::themKhachHang(){
    KhachHang newKH;
    newKH.nhapThongTin();
    this->DSKH.themKhachHang(newKH);
}

void NhanVien::themDatPhong(){                  ????
    DatPhong newDP;
    newDP.nhapThongTin();
    this->DSDP.themDatPhong(newDP);
}

void NhanVien::work() {
    cout << "Da dang nhap vao tai khoan nhan vien" << endl;
}