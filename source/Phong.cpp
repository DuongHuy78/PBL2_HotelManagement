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
    if (!Utils::isRoomType(LP)) {
        Utils::outputData("Loai phong khong hop le!\n", CONSOLE);
        return;
    }
    this->loaiPhong = LP;
}

// string Phong::capNhatThongTin(){
//     cout << "Nhap Loai Phong: ";
//     string tempStr = (Utils::nhap(5,MAX_MAPHONG+1));
//     return tempStr;
// }

void Phong::menuSuaThongTin() {
    Utils::outputData("-----------MENU-SUA-THONG-TIN---------\n", CONSOLE);
    Utils::outputData("1. Sua Loai Phong\n", CONSOLE);
    Utils::outputData("2. Sua Ma Phong\n", CONSOLE);
    Utils::outputData("3. Thoat\n", CONSOLE);
    Utils::outputData("--------------------------------------\n", CONSOLE);
}

void Phong::capNhatThongTin(){
    int choice;
    string temp;
    while (true) {
        system("cls");
        menuSuaThongTin();
        choice = Utils::stringToInt(Utils::inputWithCondition("Hay nhap lua chon: ", 1, 1, NUMBER_ONLY));
        switch(choice) {
            case 1:
                temp = Utils::inputWithCondition("Sua Loai Phong: ", 1, MAX_IDLOAIPHONG, ALPHABET_AND_NUMBER_ONLY);
                this->setLoaiPhong(temp);
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                system("pause");
                break;
            case 2:
                temp = Utils::inputWithCondition("Sua Ma Phong: ", 1, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
                this->setMaPhong(temp);
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                system("pause");
                break;
            case 3:
                Utils::outputData("Thoat khoi chuc nang sua thong tin!\n", CONSOLE);
                return;
            default:
                Utils::outputData("Lua chon khong hop le. Vui long thu lai\n", CONSOLE);
                system("pause");
                break;
        }  
    }
}

void Phong::xuatThongTin() {
    cout << left << setw(15) << maPhong << loaiPhong << endl;
    cout << string(25, '-') << endl;
}

ostream& operator<<(ostream& os, const Phong& P) {
    Utils::outputData("-----------THONG-TIN-PHONG-----------\n", CONSOLE);
    Utils::outputData("Ma Phong: ", CONSOLE);
    Utils::outputData(P.maPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("Loai Phong: ", CONSOLE);
    Utils::outputData(P.loaiPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("-------------------------------------\n", CONSOLE);
    return os;
}

