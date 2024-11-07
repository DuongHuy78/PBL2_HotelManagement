#include "./header/KhachHang.h"

KhachHang::KhachHang() {
    IDKhachHang = "";   
    hoTen = "";
    ngaySinh = 0;
    soDienThoai = "";
    gioiTinh = UNDEFINED_GENDER;
}
KhachHang::KhachHang(string IDKhachHang, string hoTen, time_t ngaySinh, string soDienThoai, gender_value gioiTinh) {
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

void KhachHang::setGioiTinh(gender_value gioiTinh) {
    this->gioiTinh = gioiTinh;
} 

void KhachHang::menuSuaThongTin(){        //in menu sửa thông tin
    cout << "1. Sua Ho Ten" << endl;
    cout << "2. Sua Ngay Sinh" << endl;
    cout << "3. Sua So Dien Thoai" << endl;
    cout << "4. Sua Gioi Tinh" << endl;
    cout << "5. Thoat" << endl;
    cout << "Hay nhap lua chon: ";
}
void KhachHang::suaThongTin() {
    gender_value gender = UNDEFINED_GENDER;
    int choice;          //lựa chọn
    string temp;            //biến tạm
    while (true) {
        menuSuaThongTin();
        choice = stoi(Utils::nhap(1, 2));         //chọn 2 vì 1 số và 1 ký tự '\0'
        switch(choice) {
            case 1:
                cout << "Nhap ho ten moi: ";
                temp = Utils::nhap(2, MAX_NAME+1);
                Utils::chuanHoaTen(temp);
                this->setHoTen(temp);
                system("cls");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 2:
                temp = Utils::nhapNgaySinh();
                this->setNgaySinh(Utils::stringToDate(temp));
                system("cls");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 3:
                cout << "Nhap So dien thoai moi: ";
                temp = Utils::NhapSoDienThoai();
                this->setSoDienThoai(temp);
                system("cls");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 4:
                while(1) {
                    cout << "Nhap gioi tinh (Nam/Nu): ";
                    temp = Utils::nhap(2, 4);
                    gender = Utils::stringToGender(temp);
                    if(gender != UNDEFINED_GENDER) break;
                    system("cls");
                    cout << "Nhap sai, vui long nhap lai!" << endl;
                }
                gender = Utils::stringToGender(temp);
                this->setGioiTinh(gender);
                system("cls");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 5:
                return;
            default:
                system("cls");
                cout << "Lua chon khong hop le." << endl;
                cout<< "Vui long chon lai!" << endl;
                break;
        }  
    }
}



void KhachHang::work() {
    cout << "ID Khach Hang: " << this->IDKhachHang << endl;
    cout << "Ho Ten: " << this->hoTen << endl;
    cout << "Ngay Sinh: " << Utils::dateToString(this->ngaySinh) << endl;
    cout << "So Dien Thoai: " << this->soDienThoai << endl;
    cout << "Gioi Tinh: " << Utils::genderToString(this->gioiTinh) << endl;
}

ostream& operator<<(ostream& out, const KhachHang& kh) {
    out << "ID Khach Hang: " << kh.IDKhachHang << endl;
    out << "Ho Ten: " << kh.hoTen << endl;
    out << "Ngay Sinh: " << Utils::dateToString(kh.ngaySinh) << endl;
    out << "So Dien Thoai: " << kh.soDienThoai << endl;
    out << "Gioi Tinh: " << Utils::genderToString(kh.gioiTinh) << endl;
    return out;
}

void KhachHang::huyDatPhong(string IDDatPhong) {
    
}