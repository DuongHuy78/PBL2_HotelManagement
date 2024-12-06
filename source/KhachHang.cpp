#include "./header/KhachHang.h"

KhachHang::KhachHang() {
    this->ID = "";
    this->hoTen = "";
    this->ngaySinh = 0;
    this->soDienThoai = "";
    this->gioiTinh = UNDEFINED_GENDER;
    this->taiKhoan = nullptr;
}
KhachHang::KhachHang(string IDKhachHang, string hoTen, time_t ngaySinh, string soDienThoai, gender_value gioiTinh) {
    this->ID = "";
    this->hoTen = "";
    this->ngaySinh = 0;
    this->soDienThoai = "";
    this->gioiTinh = UNDEFINED_GENDER;
    this->taiKhoan = nullptr;
    
    setIDKhachHang(IDKhachHang);
    setHoTen(hoTen);
    setNgaySinh(ngaySinh);
    setSoDienThoai(soDienThoai);
    setGioiTinh(gioiTinh);
}

KhachHang::KhachHang(const KhachHang& KhachHang) {
    this->ID = KhachHang.ID;
    this->hoTen = KhachHang.hoTen;
    this->ngaySinh = KhachHang.ngaySinh;
    this->soDienThoai = KhachHang.soDienThoai;
    this->gioiTinh = KhachHang.gioiTinh;
    this->taiKhoan = KhachHang.taiKhoan;
}

KhachHang::~KhachHang() {}

string KhachHang::getIDKhachHang() const {
    return this->ID;
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

gender_value KhachHang::getGioiTinh() const {
    return this->gioiTinh;
} 

// LinkedList<DatPhong *> &KhachHang::getDanhSachDatPhong() const {
//     return this->danhSachDatPhong;
// }

void KhachHang::themDatPhong(DatPhong *dp) {
    danhSachDatPhong.add(dp);
}

void KhachHang::setTaiKhoan(TaiKhoan *tk) {
    this->taiKhoan = tk;
}   

bool KhachHang::setIDKhachHang(string IDKhachHang) {
    if(Utils::isNumberOnly(IDKhachHang)) {
        this->ID = IDKhachHang;
        return true;
    }
    else {
        return false;
    }
}

bool KhachHang::setHoTen(string hoTen) {
    if(Utils::isAlphabetAndSpaceOnly(hoTen)) {
        this->hoTen = hoTen;
        return true;
    }
    else {
        return false;
    }
}

bool KhachHang::setNgaySinh(time_t ngaySinh) {
    if(Utils::isDate(Utils::dateToString(ngaySinh))) {
        this->ngaySinh = ngaySinh;
        return true;
    }
    else {
        return false;
    }
}

bool KhachHang::setSoDienThoai(string soDienThoai) {
    if(Utils::isVietNamPhoneNumber(soDienThoai)) {
        this->soDienThoai = soDienThoai;
        return true;
    }
    else {
        return false;
    }
}

bool KhachHang::setGioiTinh(gender_value gioiTinh) {
    this->gioiTinh = gioiTinh;
    return true;
} 

void KhachHang::menuSuaThongTin() {        //in menu sửa thông tin
    Utils::outputData("-----------MENU-SUA-THONG-TIN---------\n", CONSOLE);
    Utils::outputData("1. Sua Ho Ten\n", CONSOLE);
    Utils::outputData("2. Sua Ngay Sinh\n", CONSOLE);
    Utils::outputData("3. Sua So Dien Thoai\n", CONSOLE);
    Utils::outputData("4. Sua Gioi Tinh\n", CONSOLE);
    Utils::outputData("5. Thoat\n", CONSOLE);
    Utils::outputData("--------------------------------------\n", CONSOLE);
}

void KhachHang::suaThongTin() {
    int choice;
    string temp;
    while (true) {
        system("cls");
        menuSuaThongTin();
        choice = Utils::stringToInt(Utils::inputWithCondition("Hay nhap lua chon: ", 1, 1, NUMBER_ONLY));
        switch(choice) {
            case 1:
                temp = Utils::inputWithCondition("Nhap ho ten moi: ", 1, MAX_NAME, ALPHABET_AND_SPACE_ONLY);
                Utils::chuanHoaTen(temp);
                this->setHoTen(temp);
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                Utils::pauseConsole();
                break;
            case 2:
                temp = Utils::inputWithCondition("Nhap ngay sinh moi: ", 1, 10, DATE);
                this->setNgaySinh(Utils::stringToDate(temp));
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                Utils::pauseConsole();
                break;
            case 3:
                temp = Utils::inputWithCondition("Nhap so dien thoai moi: ", 1, 10, VIETNAM_PHONE_NUMBER);
                this->setSoDienThoai(temp);
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                Utils::pauseConsole();
                break;
            case 4:
                temp = Utils::inputWithCondition("Nhap gioi tinh (Nam/Nu): ", 1, 3, GENDER);
                this->setGioiTinh(Utils::stringToGender(temp));
                Utils::outputData("Chinh sua thong tin thanh cong!\n", CONSOLE);
                Utils::pauseConsole();
                break;
            case 5:
                Utils::outputData("Thoat khoi chuc nang sua thong tin!\n", CONSOLE);
                return;
            default:
                Utils::outputData("Lua chon khong hop le. Vui long thu lai\n", CONSOLE);
                Utils::pauseConsole();
                break;
        }  
    }
}

ostream& operator<<(ostream& out, const KhachHang& kh) {
    Utils::outputData("-----------THONG-TIN-KHACH-HANG---------\n", CONSOLE);
    Utils::outputData("ID Khach Hang: ", CONSOLE);
    Utils::outputData(kh.ID + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ho Ten: ", CONSOLE);
    Utils::outputData(kh.hoTen + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ngay Sinh: ", CONSOLE);
    Utils::outputData(Utils::dateToString(kh.ngaySinh) + "\n", CONSOLE_OR_UI);
    Utils::outputData("So Dien Thoai: ", CONSOLE);
    Utils::outputData(kh.soDienThoai + "\n", CONSOLE_OR_UI);
    Utils::outputData("Gioi Tinh: ", CONSOLE);
    Utils::outputData(Utils::genderToString(kh.gioiTinh) + "\n", CONSOLE_OR_UI);
    Utils::outputData("----------------------------------------\n", CONSOLE);
    return out;
}

user_option_value KhachHang::work() {
    system("cls");
    Utils::outputData("----------KHACH-HANG---------\n", CONSOLE);
    Utils::outputData("1. Sua thong tin\n", CONSOLE);
    Utils::outputData("2. Xem thong tin\n", CONSOLE);
    Utils::outputData("3. Dat Phong\n", CONSOLE);
    Utils::outputData("4. Lich su dat phong\n", CONSOLE);
    Utils::outputData("5. Dang xuat\n", CONSOLE);
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
            return CHANGE_PROFILE;
        case 2:
            cout << *this;
            Utils::pauseConsole();
            return CONTINUE;
        case 3:
            return USER_BOOK_ROOM;
        case 4:
            return USER_BOOK_ROOM_HISTORY;
        case 5:
            return SIGN_OUT;
        default:
            Utils::outputData("Lua chon khong hop le!\n", CONSOLE);
            Utils::pauseConsole();
            return CONTINUE;
    }
}
