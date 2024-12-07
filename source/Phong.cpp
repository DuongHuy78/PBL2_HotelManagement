#include "./header/Phong.h"

/**
 * @brief Thêm đặt phòng.
 */
void Phong::themDatPhong(DatPhong *DP) {
    this->danhSachDatPhong.add(DP);
}

/**
 * @brief Hàm khởi tạo mặc định.
 */
Phong::Phong() {
    this->maPhong = "";
    this->loaiPhong = nullptr;
}

/**
 * @brief Hàm khởi tạo với mã phòng.
 */
Phong::Phong(string MaPhong){
    this->maPhong = MaPhong;
    this->loaiPhong = nullptr;
}

/**
 * @brief Hàm sao chép cho lớp Phong.
 */
Phong::Phong(const Phong& other) {
    this->maPhong = other.maPhong;
    this->loaiPhong = other.loaiPhong;
}

/**
 * @brief Lấy mã phòng.
 */
string Phong::getMaPhong() const {
    return this->maPhong;
}

/**
 * @brief Lấy loại phòng.
 */
LoaiPhong *Phong::getLoaiPhong() const {
    return this->loaiPhong;
}

/**
 * @brief Thiết lập mã phòng.
 */
void Phong::setMaPhong(string MP){
    this->maPhong = MP;
}

/**
 * @brief Thiết lập loại phòng.
 */
void Phong::setLoaiPhong(LoaiPhong *LP){
    this->loaiPhong = LP;
    LP->themPhong(this);
}

/**
 * @brief In menu sửa thông tin.
 */
void Phong::menuSuaThongTin() {
    Utils::outputData("-----------MENU-SUA-THONG-TIN---------\n", CONSOLE);
    Utils::outputData("1. Sua Loai Phong\n", CONSOLE);
    Utils::outputData("2. Sua Ma Phong\n", CONSOLE);
    Utils::outputData("3. Thoat\n", CONSOLE);
    Utils::outputData("--------------------------------------\n", CONSOLE);
}

/**
 * @brief Cập nhật thông tin phòng.
 */
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
                //this->setLoaiPhong(temp);
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                Utils::pauseConsole();
                break;
            case 2:
                temp = Utils::inputWithCondition("Sua Ma Phong: ", 1, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
                this->setMaPhong(temp);
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                Utils::pauseConsole();
                break;
            case 3:
                Utils::outputData("Thoat khoi chuc nang sua thong tin!\n", CONSOLE);
                return;
            default:
                Utils::outputData("Lua chon khong hop le. Vui long thu lai\n", CONSOLE);
                Utils::pauseConsole();
                break;
        }  
    }
}

/**
 * @brief In thông tin phòng.
 */
ostream& operator<<(ostream& os, const Phong& P) {
    Utils::outputData("-----------THONG-TIN-PHONG-----------\n", CONSOLE);
    Utils::outputData("Ma Phong: ", CONSOLE);
    Utils::outputData(P.maPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("Loai Phong: ", CONSOLE);
    Utils::outputData(P.getLoaiPhong()->getLoaiPhong() + "\n", CONSOLE_OR_UI);
    Utils::outputData("-------------------------------------\n", CONSOLE);
    return os;
}

