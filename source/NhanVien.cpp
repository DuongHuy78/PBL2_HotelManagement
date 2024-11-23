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

ostream& operator<<(ostream& out, const NhanVien& nv) {
    Utils::outputData("-----------THONG-TIN-NHAN-VIEN---------\n", CONSOLE);
    Utils::outputData("ID Nhan Vien: ", CONSOLE);
    Utils::outputData(nv.IDNhanVien + "\n", CONSOLE_OR_UI);
    Utils::outputData("--------------------------------------\n", CONSOLE);
    return out;
}

user_option_value NhanVien::work() {
    system("cls");
    Utils::outputData("-----------NHAN-VIEN---------\n", CONSOLE);
    Utils::outputData("1. Them khach hang\n", CONSOLE);
    Utils::outputData("2. Them dat phong\n", CONSOLE);
    Utils::outputData("3. Danh sach khach hang\n", CONSOLE);
    Utils::outputData("4. Dang xuat\n", CONSOLE);
    Utils::outputData("-----------------------------\n", CONSOLE);

    string choice_str;
    Utils::outputData("Hay nhap lua chon: ", CONSOLE);
    Utils::inputData(choice_str, CONSOLE_OR_UI);
    if(Utils::isNumberOnly(choice_str) == false) {
        Utils::outputData("Lua chon khong hop le!\n", CONSOLE);
        return CONTINUE;
    }
    int choice = Utils::stringToInt(choice_str);
    switch(choice) {
        case 1:
            themKhachHang();
            system("pause");
            return CONTINUE;
        case 2:
            themDatPhong();
            system("pause");
            return CONTINUE;
        case 3:
            cout << *DSKH;
            system("pause");
            return CONTINUE;
        case 4:
            return SIGN_OUT;
        default:
            Utils::outputData("Lua chon khong hop le!\n", CONSOLE);
            return CONTINUE;
    }
}
