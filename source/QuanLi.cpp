#include "./header/QuanLi.h"

void QuanLi::setTaiKhoan(TaiKhoan *tk) {
    this->taiKhoan = tk;
}

QuanLi::QuanLi() {
    this->ID = "";
    this->taiKhoan = nullptr;
}

string QuanLi::getIDQuanLi() const {
    return this->ID;
}

void QuanLi::setIDQuanLi(string ID) {
    this->ID = ID;
}

ostream &operator<<(ostream &out, QuanLi &ql) {
    Utils::outputData("-----------THONG-TIN-QUAN-LI-----------\n", CONSOLE);
    Utils::outputData("ID quan li: ", CONSOLE);
    Utils::outputData(ql.ID + "\n", CONSOLE_OR_UI);
    Utils::outputData("-----NhatHoang-DuongHuy-ThaoDuyen-----\n", CONSOLE);
    return out;
}

user_option_value QuanLi::work() {
    system("cls");
    Utils::outputData("-------------QUAN-LI------------\n", CONSOLE);
    Utils::outputData("1. Tao loai phong\n", CONSOLE);
    Utils::outputData("2. Xem danh sach loai phong\n", CONSOLE);
    Utils::outputData("3. Sua loai phong\n", CONSOLE);
    Utils::outputData("4. Xoa loai phong\n", CONSOLE);
    Utils::outputData("5. Tao phong\n", CONSOLE);
    Utils::outputData("6. Xem danh sach phong\n", CONSOLE);
    Utils::outputData("7. Sua phong\n", CONSOLE);
    Utils::outputData("8. Xoa phong\n", CONSOLE);
    Utils::outputData("9. Xem doanh thu\n", CONSOLE);
    Utils::outputData("10. Dang xuat\n", CONSOLE);
    Utils::outputData("--NhatHoang-DuongHuy-ThaoDuyen--\n", CONSOLE);

    string choice_str;
    Utils::outputData("Hay nhap lua chon: ", CONSOLE);
    Utils::inputData(choice_str, CONSOLE_OR_UI);
    if(Utils::isNumberOnly(choice_str) == false) {
        Utils::outputData("Lua chon khong hop le!\n", CONSOLE);
        return CONTINUE;
    }
    int choice = Utils::stringToInt(choice_str);
    string maLoaiPhong, maPhong;
    switch(choice) {
        case 1:
            return ADD_LOAI_PHONG;
        case 2:
            return PRINT_DSLP;
        case 3:
            return UPDATE_LOAIPHONG;
        case 4:
            return DELETE_LOAIPHONG;
        case 5:
            return ADD_PHONG;
        case 6:
            return PRINT_DSP;
        case 7:
            return UPDATE_PHONG;
        case 8:
            return DELETE_PHONG;
        case 9:
            return PRINT_DOANH_THU;
        case 10:
            return SIGN_OUT;
        default:
            Utils::outputData("Lua chon khong hop le!\n", CONSOLE);
            Utils::pauseConsole();
            return CONTINUE;
    }    
}