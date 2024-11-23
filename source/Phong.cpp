#include "./header/Phong.h"

Phong::Phong() {
    this->maPhong = "";
    this->loaiPhong = "";
}

Phong::Phong(string MaPhong, string LoaiPhong){
    this->maPhong = MaPhong;
    this->loaiPhong = LoaiPhong;
}

Phong::Phong(const Phong& other){
    this->maPhong = other.maPhong;
    this->loaiPhong = other.loaiPhong;
}

Phong::~Phong() {
}

// Hàm get
string Phong::getMaPhong() const {
    return this->maPhong;
}

string Phong::getLoaiPhong() const {
    return this->loaiPhong;
}


void Phong::setMaPhong(string MP){
    this->maPhong = MP;
}

void Phong::setLoaiPhong(string LP) {
    this->loaiPhong = LP;
}

string Phong::capNhatThongTin(){
    cout << "Nhap Loai Phong: ";
    string tempStr = (Utils::nhap(5,MAX_MAPHONG+1));
    return tempStr;
}

void Phong::xuatThongTin() {
    cout << left << setw(15) << maPhong << loaiPhong << endl;
    cout << string(25, '-') << endl;
}

ostream& operator<<(ostream& os, const Phong& P) {
    Utils::outputData("-----------THONG-TIN-PHONG---------\n", CONSOLE);
    Utils::outputData("Ma Phong: ", CONSOLE);
    Utils::outputData(P.maPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("Loai Phong: ", CONSOLE);
    Utils::outputData(P.loaiPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("--------------------------------------\n", CONSOLE);
    return os;
}

