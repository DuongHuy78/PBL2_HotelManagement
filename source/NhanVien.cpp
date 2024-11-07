#include "./header/NhanVien.h"
NhanVien::NhanVien() {
    IDNhanVien = "";
}

NhanVien::~NhanVien() {

}

NhanVien::NhanVien(string ID) {
    this->IDNhanVien = ID;
}

void NhanVien::setDSKH(QLKhachHang *DSKH) {
    this->DSKH = DSKH;
}

void NhanVien::setDSDP(QLDatPhong *DSDP) {
    this->DSDP = DSDP;
}

string NhanVien::getIDNhanVien() const {
    return this->IDNhanVien;
}

void NhanVien::setIDNhanVien(string ID) {
    this->IDNhanVien = ID;
}

void NhanVien::themKhachHang(){
    KhachHang newKH = DSKH->nhapThongTin();
    this->DSKH->themKhachHang(newKH);
}

void NhanVien::themDatPhong() {
    DatPhong newDP = DSDP->nhapThongTin();
    this->DSDP->themDatPhong(newDP);
}

void NhanVien::work() {
    cout << "Da dang nhap vao tai khoan nhan vien" << endl;
}