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
string KhachHang::nhapNgaySinh() {
    string input;
    int day, month, year;
    int check;
    int maxDaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // Số ngày trong tháng

    while (1) {  // Lặp lại nếu nhập sai
        cout << "Nhap ngay thang nam sinh (theo dinh dang dd/mm/yyyy): ";
        input = Utils::nhap(4, 11);  // Nhập ngày tháng năm sinh

        // Tách chuỗi thành ngày, tháng, năm
        stringstream ss(input);
        string temp_day, temp_month, temp_year;

        getline(ss, temp_day, '/');
        getline(ss, temp_month, '/');
        getline(ss, temp_year, '/');

        // Chuyển chuỗi sang số nguyên
        day = atoi(temp_day.c_str());
        month = atoi(temp_month.c_str());
        year = atoi(temp_year.c_str());

        check = 1;

        // Kiểm tra tháng và năm hợp lệ lớn 18 tuổi
        // Khai báo biến tên là localTimeInfo
        tm* localTimeInfo;
        // Lấy thời gian hiện tại
        time_t currentTime = time(nullptr);
        localTimeInfo = localtime(&currentTime);
        if (month <= 0 || month > 12 || year <= 1900 || year > localTimeInfo->tm_year + 1900 - 18) {
            check = 0;
        }
        // Kiểm tra năm nhuận
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            if (month == 2 && (day > 29 || day <= 0)) {
                check = 0;
            }
        } else {
            // Kiểm tra ngày hợp lệ
            if (day <= 0 || day > maxDaysInMonth[month - 1]) {
                check = 0;
            }
        }

        if (check != 1) {
            std::cout << "Ban nhap sai, vui long nhap lai!\n";
            continue;
        }

        return input;
    }
}

string KhachHang::NhapSoDienThoai() {
    string temp = "";
    char ch;
    while (1) {
        ch = getch();
        if (isdigit(ch) && temp.length() <= 10) {
            cout << ch;
            temp += ch;
        } 
        else if (ch == '\b' && !temp.empty()) { // \b là ký tự backspace
            cout << "\b \b";
            temp.pop_back();
        }
        if(temp.length() == 10 && (ch  == '\r' || ch == '\n') )
            break;
    }
    cout << endl;
    return temp;
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
    int gender = 0;
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
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 2:
                temp = nhapNgaySinh();
                this->setNgaySinh(Utils::stringToTime(temp));
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 3:
                cout << "Nhap So dien thoai moi: ";
                temp = NhapSoDienThoai();
                this->setSoDienThoai(temp);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 4:
                while(1){
                    cout << "Nhap gioi tinh (Nam nhap 0, Nu nhap 1): ";
                    temp = Utils::nhap(1, 2);           //giới tính có 1 ký tự
                    if(temp == "0" || temp == "1") break;
                    cout << "Nhap sai, vui long nhap lai!" << endl;
                }
                gender = Utils::stringToInt(temp);
                if(gender == 0) this->setGioiTinh(NAM);
                else if(gender == 1) this->setGioiTinh(NU);
                system("clear");
                cout<< "Chinh sua thong tin thanh cong!" << endl;
                break;
            case 5:
                return;
            default:
                system("clear");
                cout << "Lua chon khong hop le." << endl;
                cout<< "Vui long chon lai!" << endl;
                break;
        }  
    }
}

void KhachHang::nhapThongTin() {
    int gender = 0;
    string temp;            //biến tạm
    LinkedList<KhachHang> DSKH = QLKhachHang::getDSKH();

    temp = DSKH.taoIDKhachHang();           //ID khách hàng tự tạo chứ ko nhập
    this->setIDKhachHang(temp);

    cout << "Nhap thong tin khach hang" << endl;
    
    cout << "Nhap ho ten : ";
    temp = Utils::nhap(2, MAX_NAME+1);
    Utils::chuanHoaTen(temp);
    this->setHoTen(temp);
    
    temp = nhapNgaySinh();
    this->setNgaySinh(Utils::stringToTime(temp));

    cout << "Nhap So dien thoai : ";
    temp = NhapSoDienThoai();
    this->setSoDienThoai(temp);

    while(1){
        cout << "Nhap gioi tinh (Nam nhap 0, Nu nhap 1): ";
        temp = Utils::nhap(1, 2);           //giới tính có 1 ký tự
        if(temp == "0" || temp == "1") break;
        system("clear");
        cout << "Nhap sai, vui long nhap lai!" << endl;
    }
    gender = Utils::stringToInt(temp);
    if(gender == 0) this->setGioiTinh(NAM);
    else if(gender == 1) this->setGioiTinh(NU);
}

void KhachHang::work() {
    cout << "ID Khach Hang: " << this->IDKhachHang << endl;
    cout << "Ho Ten: " << this->hoTen << endl;
    cout << "Ngay Sinh: " << Utils::dateToString(this->ngaySinh) << endl;
    cout << "So Dien Thoai: " << this->soDienThoai << endl;
    cout << "Gioi Tinh: " << Utils::genderToString(this->gioiTinh) << endl;
}

void KhachHang::huyDatPhong(string IDDatPhong) {
    
}