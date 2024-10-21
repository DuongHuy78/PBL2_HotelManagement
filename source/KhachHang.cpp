#include "./header/KhachHang.h"
KhachHang::KhachHang(string IDKhachHang, string hoTen, time_t ngaySinh, string soDienThoai, bool gioiTinh) {
    this->IDKhachHang = IDKhachHang;
    this->hoTen = hoTen;
    this->ngaySinh = ngaySinh;
    this->soDienThoai = soDienThoai;
    this->gioiTinh = gioiTinh;
}

KhachHang::KhachHang(const KhachHang& KhachHang) {
    this->IDKhachHang = KhachHang.IDKhachHang;
    this->hoTen = KhachHang.hoTen;
    this->ngaySinh = KhachHang.ngaySinh;
    this->soDienThoai = KhachHang.soDienThoai;
    this->gioiTinh = KhachHang.gioiTinh;
}

KhachHang::~KhachHang() {
    
}

string KhachHang::getIDKhachHang() const {
    return this->IDKhachHang;
}

string KhachHang::getHoTen() const {
    return this->hoTen;
}

time_t KhachHang::getNgaySinh() const {
    return this->ngaySinh;
}

string KhachHang::getSoDienThoai() const {
    return this->soDienThoai;
}

bool KhachHang::getGioiTinh() const {
    return this->gioiTinh;
} 


void KhachHang::setIDKhachHang(string IDKhachHang) {
    this->IDKhachHang = IDKhachHang;
}

void KhachHang::setHoTen(string hoTen) {
    this->hoTen = hoTen;
}

void KhachHang::setNgaySinh(time_t ngaySinh) {
    this->ngaySinh = ngaySinh;
}

void KhachHang::setSoDienThoai(string soDienThoai) {
    this->soDienThoai = soDienThoai;
}

void KhachHang::setGioiTinh(bool gioiTinh) {
    this->gioiTinh = gioiTinh;
} 

void KhachHang::work() {
    cout << "ID Khach Hang: " << this->IDKhachHang << endl;
    cout << "Ho Ten: " << this->hoTen << endl;
    cout << "Ngay Sinh: " << this->ngaySinh << endl;
    cout << "So Dien Thoai: " << this->soDienThoai << endl;
    cout << "Gioi Tinh: " << this->gioiTinh << endl;
}

void KhachHang::menuSuaThongTin(){                             //menu sửa thông tin
    cout << "1. Sua ID Khach Hang" << endl;
    cout << "2. Sua Ho Ten" << endl;
    cout << "3. Sua Ngay Sinh" << endl;
    cout << "4. Sua So Dien Thoai" << endl;
    cout << "5. Sua Gioi Tinh" << endl;
    cout << "6. Thoat" << endl;
    cout << "Hay nhap lua chon: ";
}
void KhachHang::suaThongTin() {
    string choice;

    while (true) {
        menuSuaThongTin();
        choice = getline(cin<<ws, choice);
        if(isdigit(choice)!=0)
        {
            choice = "0";              //nếu nhập không phải số thì gán choice = 0, để nhập lại
        }
        switch(choice):
            case "1":
                cout << "Nhap ID Khach Hang moi: ";
                getline(cin<<ws, choice);
                this->setIDKhachHang(choice);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case "2":
                cout << "Nhap Ho Ten moi: ";
                getline(cin<<ws, choice);
                this->setHoTen(choice);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case "3":
                cout << "Nhap Ngay Sinh moi: ";
                getline(cin<<ws, choice);
                this->setNgaySinh(choice);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case "4":
                cout << "Nhap So Dien Thoai moi: ";
                getline(cin<<ws, choice);
                this->setSoDienThoai(choice);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case "5":
                cout << "Nhap Gioi Tinh moi: ";
                getline(cin<<ws, choice);
                this->setGioiTinh(choice);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case "6":
                return;
            default:
                cout << "Lua chon khong hop le" << endl;
                break;
    }
}