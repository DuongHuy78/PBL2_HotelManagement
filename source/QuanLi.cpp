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


// void QuanLi::xemDanhSachLuaChonXemDoanhThu(){
//     cout<<"1. XEM DOANH THU THEO NGAY."<<endl;
//     cout<<"2. XEM DOANH THU THEO THANG."<<endl;
//     cout<<"3. XEM DOANH THU THEO NAM."<<endl;
// }

/**
 * hàm này để xem doanh thu theo ngày, tháng, năm
 */
// void QuanLi::xemDoanhThu() {
//     string temp;
//     string d_begin, d_end;
//     int ktra = 1, doanhThu;
//     while(ktra){
//         ktra = 0;
//         xemDanhSachLuaChonXemDoanhThu();
//         temp = Utils::inputWithCondition("Nhap lua chon: ", 1, 1, NUMBER_ONLY);
//         if(temp != "1" && temp != "2" && temp != "3"){
//             cout<<"Nhap sai, vui long nhap lai!"<<endl;
//             ktra = 1;
//         }
//     }
//     if(temp == "1"){
//         d_begin = Utils::inputWithCondition("Nhap ngay muon xem (theo dinh dang dd/mm/yyyy): ", 10, 10, DATE);
//         // doanhThu = thongKe(d_begin, d_begin+1);
//         cout<<"Doanh thu cua ngay "<<d_begin<<" la: "<<doanhThu<<endl;
//     }
//     else if (temp == "2")
//     {
//         int ktra;
//         string month, year, date;
//         ktra = 1;
//         while(ktra){
//             ktra = 0;
//             while(true){
//                 Utils::outputData("Nhap thang muon xem (theo dinh dang mm/yyyy): ", CONSOLE);
//                 Utils::inputData(date, CONSOLE_OR_UI);
//                 if(date.size() != 8){           //dù có 7 ký tự nhưng đặt là 8 vì có thêm ký tự '\n'
//                     break;
//                 }
//                 cout<<"Nhap sai, vui long nhap lai!"<<endl;
//             }
//             stringstream ss(date);
//             getline(ss, month, '/');
//             getline(ss, year, '/');
//             if(Utils::stringToInt(month) > 12 || Utils::stringToInt(month) < 1){
//                 ktra = 1;
//             }
//             if(ktra){
//                 system("clear");
//                 cout<<"Nhap sai, vui long nhap lai!"<<endl;
//             }
//         }
//         d_begin = "01/" + month + "/" + year;
//         d_end = "31/" + month + "/" + year;
//         // doanhThu = thongKe(d_begin, d_end + 1);
//         cout<<"Doanh thu cua thang "<<month<<"/"<<year<<" la: "<<doanhThu<<endl;
//     }
//     else if(temp == "3"){
//         int ktra;
//         string year;
//         ktra = 1;
//         while(ktra){
//             ktra = 0;
//             year = Utils::inputWithCondition("Nhap nam muon xem (theo dinh dang yyyy): ", 4, 4, NUMBER_ONLY);
//             if(Utils::stringToInt(year) < 1900){
//                 ktra = 1;
//             }
//             if(ktra){
//                 system("clear");
//                 cout<<"Nhap sai, vui long nhap lai!"<<endl;
//             }
//         }
//         d_begin = "01/01/" + year;
//         d_end = "31/12/" + year;
//         // doanhThu = thongKe(d_begin, d_end + 1);
//         cout<<"Doanh thu cua nam "<<year<<" la: "<<doanhThu<<endl;
//     }
// }

ostream &operator<<(ostream &out, QuanLi &ql) {
    Utils::outputData("-----------THONG-TIN-QUAN-LI-----------\n", CONSOLE);
    Utils::outputData("ID quan li: ", CONSOLE);
    Utils::outputData(ql.ID + "\n", CONSOLE_OR_UI);
    Utils::outputData("--------------------------------------\n", CONSOLE);
    return out;
}

user_option_value QuanLi::work() {
    system("cls");
    Utils::outputData("-----------QUAN-LI-----------\n", CONSOLE);
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
    Utils::outputData("-----------------------------\n", CONSOLE);

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