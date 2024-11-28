#include "./header/NhanVien.h"
NhanVien::NhanVien() {
    IDNhanVien = "";
}

NhanVien::~NhanVien() {

}

NhanVien::NhanVien(string ID) {
    this->IDNhanVien = ID;
}

string NhanVien::getIDNhanVien() const {
    return this->IDNhanVien;
}

void NhanVien::setIDNhanVien(string ID) {
    this->IDNhanVien = ID;
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
    Utils::outputData("4. Danh sach dat phong\n", CONSOLE);
    Utils::outputData("5. Danh sach loai phong\n", CONSOLE);
    Utils::outputData("6. Danh sach phong\n", CONSOLE);
    Utils::outputData("7. Xem thong tin khach hang (ID)\n", CONSOLE);
    Utils::outputData("8. Xem thong tin dat phong (ID)\n", CONSOLE);
    Utils::outputData("9. Xem thong tin khach hang (SDT)\n", CONSOLE);
    // Nếu phòng đang được đặt thì in kèm thông tin đặt phòng
    Utils::outputData("10. Xem thong tin phong (ID)\n", CONSOLE); 
    Utils::outputData("11. Xem thong tin phong (loaiPhong)\n", CONSOLE);
    Utils::outputData("12. Dang xuat\n", CONSOLE);
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
            return ADD_KHACHHANG;
        case 2:
            return USER_BOOK_ROOM;
        case 3:
            return PRINT_DSKH;
        case 4:
            return PRINT_DSDP;
        case 5:
            return PRINT_DSLP;
        case 6:
            return PRINT_DSP;
        case 7: 
            return PRINT_DSKH_ID;
        case 8:
            return PRINT_DSDP_ID;
        case 9:
            return PRINT_DSKH_SDT;
        case 10:
            return PRINT_DSP_ID;
        case 11:
            return PRINT_DSP_LOAIPHONG;
        case 12:
            return SIGN_OUT;
        default:
            Utils::outputData("Lua chon khong hop le!\n", CONSOLE);
            system("pause");
            return CONTINUE;
    }
}
