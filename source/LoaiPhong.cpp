#include "./header/LoaiPhong.h"

// Constructor không tham số
LoaiPhong::LoaiPhong(){}

//Deconstructor
LoaiPhong::~LoaiPhong() {

}

//constructor: Khởi tạo tất cả các thuộc tính của lớp từ các tham số đầu vào
LoaiPhong::LoaiPhong(string LoaiPhong, int LoaiGiuong, int SoLuongKhach, int DienTich, int GiaPhong, string MoTaPhong)
  : loaiPhong(LoaiPhong), loaiGiuong(LoaiGiuong), soLuongKhach(SoLuongKhach), dienTich(DienTich), giaPhong(GiaPhong), moTaPhong(MoTaPhong) {}

// Constructor sao chép
LoaiPhong::LoaiPhong(const LoaiPhong& other)
    : loaiPhong(other.loaiPhong), loaiGiuong(other.loaiGiuong), soLuongKhach(other.soLuongKhach), dienTich(other.dienTich), giaPhong(other.giaPhong), moTaPhong(other.moTaPhong) {}

//Hàm nhập thông tin loại phòng mới
void LoaiPhong::NhapLoaiPhongMoi(){
    cout << "Nhap Ten Loai Phong: ";
    cin >> this->loaiPhong;
    cout << endl;

    cout << "Nhap Loai Giuong: ";
    cin >> this->loaiGiuong;
    cout << endl;

    cout << "Nhap So Luong Khach: ";
    cin >> this->soLuongKhach;
    cout << endl;

    cout << "Nhap Dien Tich: ";
    cin >> this->dienTich;
    cout << endl;

    cout << "Nhap Gia Phong: ";
    cin >> this->giaPhong;
    cout << endl;

    cin.ignore();
    cout << "Nhap Mo Ta Phong: ";
    getline(cin,this->moTaPhong);
    cout << endl;
    return;
}

// hàm Get
string LoaiPhong::getLoaiPhong() const {
      return this->loaiPhong;
}

int LoaiPhong::getLoaiGiuong() const {
    return this->loaiGiuong;
}

int LoaiPhong::getSoLuongKhach() const {
    return this->soLuongKhach;

}

int LoaiPhong::getDienTich() const {
    return this->dienTich;
}

int LoaiPhong::getGiaPhong() const {
    return this->giaPhong;
}

string LoaiPhong::getMoTaPhong() const {
    return this->moTaPhong;
}

// Hàm Set
void LoaiPhong::setLoaiPhong(string LP){
    this->loaiPhong = LP;
}

void LoaiPhong::setLoaiGiuong(int LG) {
    this->loaiGiuong = LG;
}

void LoaiPhong::setSoLuongKhach(int SLK) {
    this->soLuongKhach = SLK;
}

void LoaiPhong::setDienTich(int DT) {
    this->dienTich = DT;
    
}

void LoaiPhong::setGiaPhong(int GP) {
    this->giaPhong = GP;

}

void LoaiPhong::setMoTaPhong(string MTP) {
    this->moTaPhong = MTP;
}