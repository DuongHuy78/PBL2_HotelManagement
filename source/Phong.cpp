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
    try {
        if(this->loaiPhong == nullptr) {
            throw "Phong::getLoaiPhong::LoaiPhong khong ton tai!";
        }
        return this->loaiPhong;
    }
    catch(const char* msg) {
        cerr << msg << endl;
        return nullptr;
    }
}

/**
 * @brief Lấy số lượng đặt phòng.
 */
int Phong::getSoLuongDatPhong() const {
    return this->danhSachDatPhong.getSize();
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
void Phong::setLoaiPhong(LoaiPhong *LP) {
    if(LP == nullptr) {
        cerr << "Phong::setLoaiPhong::LoaiPhong khong ton tai!" << endl;
        return;
    }
    if(this->loaiPhong != nullptr) {
        this->loaiPhong->xoaPhong(this);
    }
    this->loaiPhong = LP;
    LP->themPhong(this);
}

void Phong::clearLoaiPhong() {
    this->loaiPhong->xoaPhong(this);
    this->loaiPhong = nullptr;
}

/**
 * @brief In menu sửa thông tin.
 */
void Phong::menuSuaThongTin() {
    Utils::outputData("-----------MENU-SUA-THONG-TIN---------\n", CONSOLE);
    Utils::outputData("1. Sua Loai Phong\n", CONSOLE);
    Utils::outputData("2. Sua Ma Phong\n", CONSOLE);
    Utils::outputData("3. Thoat\n", CONSOLE);
    Utils::outputData("-----NhatHoang-DuongHuy-ThaoDuyen-----\n", CONSOLE);
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
    Utils::outputData("Loai Giuong: ", CONSOLE);
    Utils::outputData(P.getLoaiPhong()->getLoaiGiuongStr() + "\n", CONSOLE_OR_UI);
    Utils::outputData("So Luong Khach: ", CONSOLE);
    Utils::outputData(Utils::intToString(P.getLoaiPhong()->getSoLuongKhach()) + "\n", CONSOLE_OR_UI);
    Utils::outputData("Dien Tich: ", CONSOLE);
    Utils::outputData(Utils::intToString(P.getLoaiPhong()->getDienTich()) + " m2\n", CONSOLE_OR_UI);
    Utils::outputData("Don gia: ", CONSOLE);
    Utils::outputData(Utils::chuanHoaSo(Utils::intToString(P.getLoaiPhong()->getGiaPhong())) + " VND\n", CONSOLE_OR_UI);
    Utils::outputData("----NhatHoang-DuongHuy-ThaoDuyen----\n", CONSOLE);
    return os;
}

