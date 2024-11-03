#include "./header/DatPhong.h"
DatPhong::DatPhong() {
    this->maDatPhong = "";
    this->maPhong = "";
    this->IDKhachHang = "";
    this->ngayNhan = 0;
    this->ngayTra = 0;
    this->soLuongKhach = 0;
    this->donGia = 0;
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

DatPhong::DatPhong(const DatPhong & datPhong) {
    this->maDatPhong = datPhong.maDatPhong;
    this->maPhong = datPhong.maPhong;
    this->IDKhachHang = datPhong.IDKhachHang;
    this->ngayNhan = datPhong.ngayNhan;
    this->ngayTra = datPhong.ngayTra;
    this->soLuongKhach = datPhong.soLuongKhach;
    this->donGia = datPhong.donGia;
}

DatPhong::~DatPhong() {

}

string DatPhong::getMaDatPhong() const {
    return this->maDatPhong;
} 

string DatPhong::getMaPhong() const {
    return this->maPhong;
}

string DatPhong::getIDKhachHang() const {
    return this->IDKhachHang;
}

time_t DatPhong::getNgayNhan() const {
    return this->ngayNhan;
}

time_t DatPhong::getNgayTra() const {
    return this->ngayTra;
}

int DatPhong::getSoLuongKhach() const {
    return this->soLuongKhach;
}

int DatPhong::getDonGia() const {
    return this->donGia;
}


void DatPhong::setMaDatPhong(string MDP) {
    this -> maDatPhong = MDP;
}

void DatPhong::setMaPhong(string MP) {
    this -> maPhong = MP;
}

void DatPhong::setIDKhachHang(string MKH) {
    this -> IDKhachHang = MKH;
}

void DatPhong::setNgayNhan(time_t NNhan) {
    this -> ngayNhan = NNhan;
}

void DatPhong::setNgayTra(time_t NTra) {
    this -> ngayTra = NTra;
}

void DatPhong::setSoLuongKhach(int SL) {
    this -> soLuongKhach = SL;
}

void DatPhong::setDonGia(int Gia) {
    this -> donGia = Gia;
}

void DatPhong::nhapThongTinDatPhong() {                 ???
    int Ktra = 1;
    string temp, soLuongKhach;
    time_t = ngayNhan, ngayTra;
    cout <<"Nhap thong tin dat phong :" << endl;
    while(Ktra){                                        //Kiểm tra xem ngày nhận và ngày trả có hợp lệ không
        Ktra = 0;           //Ktra = 0 nếu nhập đúng
        cout <<"Nhap ngay nhan: ";
        temp = Utils::nhap(4, 11);              //ngày nhận có 10 ký tự 01/34/6789
        ngayNhan = Utils::stringToTime(temp);
        if(ngayNhan < time(0)){
            cout <<"Ngay nhan phai lon hon ngay hien tai" << endl;
            Ktra = 1;
        }
        cout <<"Nhap ngay tra: ";
        temp = Utils::nhap(4, 11);              //ngày nhận có 10 ký tự 01/34/6789
        ngayNhan = Utils::stringToTime(temp);
        if(ngayTra < ngayNhan){
            cout <<"Ngay tra phai lon hon ngay nhan" << endl;
            Ktra = 1;
        }
        if(Ktra) {
            system("clear");
            cout <<"Có vẻ đã có sai sot vui long nhap lai!" << endl;
        }
    }

    Ktra = 1;
    while(Ktra) {                           //Kiểm tra số lượng khách có hợp lệ không
        Ktra = 0;
        cout <<"Nhap so luong khach (neu lon hon 4 vui long dat 2 phong): ";
        soLuongKhach = Utils::nhap(1, 2);           //số lượng khách có 1 ký tự
        if(Utils::stringToInt(soLuongKhach) > 4) {
            cout <<"So luong khach qua nhieu, vui long dat 2 phong" << endl;
            Ktra = 1;
        }
        else if(Utils::stringToInt(soLuongKhach) < 1) {
            cout <<"So luong khach khong hop le, vui long nhap lai" << endl;
            Ktra = 1;
        }
    }
    
    cout <<"Nhap ma phong: ";

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
