#include "./header/DatPhong.h"
DatPhong::DatPhong() {

}

DatPhong::DatPhong(string MDP, string MP, string MKH, time_t NNhan, time_t NTra, int SL, int Gia) {
    this->maDatPhong = MDP;
    this->maPhong = MP;
    this->IDKhachHang = MKH;
    this->ngayNhan = NNhan;
    this->ngayTra = NTra;
    this->soLuongKhach = SL;
    this->donGia = Gia;
}

DatPhong::DatPhong(const DatPhong &) {

}

DatPhong::~DatPhong() {

}

string DatPhong::getMaDatPhong() const {

} 

string DatPhong::getMaPhong() const {

}

string DatPhong::getIDKhachHang() const {

}

time_t DatPhong::getNgayNhan() const {

}

time_t DatPhong::getNgayTra() const {

}

int DatPhong::getSoLuongKhach() const {

}

int DatPhong::getDonGia() const {

}


void DatPhong::setMaDatPhong(string) {

}

void DatPhong::setMaPhong(string) {

}

void DatPhong::setIDKhachHang(string) {

}

void DatPhong::setNgayNhan(time_t) {

}

void DatPhong::setNgayTra(time_t) {

}

void DatPhong::setSoLuongKhach(int) {

}

void DatPhong::setDonGia(int) {

}


void DatPhong::xemThongTin() {
    cout << maDatPhong << endl;
    cout << maPhong << endl;
    cout << IDKhachHang << endl;
    cout << Utils::dateToString(ngayNhan) << endl;
    cout << Utils::dateToString(ngayTra) << endl;
    cout << soLuongKhach << endl;
    cout << donGia << endl;
}
