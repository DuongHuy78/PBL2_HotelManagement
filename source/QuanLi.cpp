#include "./header/QuanLi.h"
QuanLi::QuanLi() {

}

QuanLi::~QuanLi() {

}

string QuanLi::getIDQuanLi() const {
    return this->IDQuanLi;
}

void QuanLi::setIDQuanLi(string ID) {
    this->IDQuanLi = ID;
}

string operator+(const string &time,const int &n) {
    int day, month, year;
    int maxDaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    stringstream ss(time);
    string temp_day, temp_month, temp_year;

    getline(ss, temp_day, '/');
    getline(ss, temp_month, '/');
    getline(ss, temp_year, '/');

    // Chuyển chuỗi sang số nguyên
    day = atoi(temp_day.c_str());
    month = atoi(temp_month.c_str());
    year = atoi(temp_year.c_str());

    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        maxDaysInMonth[1] = 29;
    }
    for(int i = 0; i < n; i++) {
        day++;
        if(day > maxDaysInMonth[month - 1]) {
            day = 1;
            month++;
            if(month > 12) {
                month = 1;
                year++;
            }
        }
    }
    string dayStr = Utils::intToString(day) + "/" + Utils::intToString(month) + "/" + Utils::intToString(year);
    return dayStr;
}
void QuanLi::taoLoaiPhong() {
    LoaiPhong newLP = DSLP->nhapThongTin(); // chỉnh 
    this->DSLP->themLoaiPhong(newLP);
}

void QuanLi::suaLoaiPhong(const string& maLoaiPhong) {
    LoaiPhong *LP = DSLP->timKiemLoaiPhong(maLoaiPhong);
    if(LP == NULL) {
        cout << "Khong tim thay loai phong!" << endl;
        return;
    }
    LP->suaThongTin();
}

void QuanLi::xoaLoaiPhong(const string& maLoaiPhong) {
    LoaiPhong *LP = DSLP->timKiemLoaiPhong(maLoaiPhong);
    if(LP == NULL) {
        cout << "Khong tim thay loai phong!" << endl;
        return;
    }
    DSLP->xoaLoaiPhong(*LP);
}

void QuanLi::taoPhong() {
    Phong newP = DSP->nhapThongTin();       //chưa có hàm này
    this->DSP->themPhong(newP);
}

void QuanLi::suaPhong(const string& maPhong) {
    Phong *P = DSP->timKiemPhong(maPhong);      //chưa có hàm này
    if(P == NULL) {
        cout << "Khong tim thay phong!" << endl;
        return;
    }
    P->suaThongTin();          //chưa viết xong
}

void QuanLi::xoaPhong(const string& maPhong){
    Phong *P = DSP->timKiemPhong(maPhong);
    if(P == NULL) {
        cout << "Khong tim thay loai phong!" << endl;
        return;
    }
    DSP->xoaPhong(*P);
}

/**
 * hàm này để tính doanh thu từ ngày bắt đầu đến ngày kết thúc
 */
string QuanLi::thongKe(string t_begin, string t_end){
    string doanhThu;
    time_t timeBegin, timeEnd;
    Node<DatPhong>* time1,*time2;
    timeBegin = Utils::stringToTime(t_begin);
    timeEnd = Utils::stringToTime(t_end);
    time1 = DSDP->getHead()->next;
    time2 = DSDP->getHead()->next;
    while(time1 != DSDP->getHead() || time2 != DSDP->getHead()){
        if(time1->data.getNgayNhan() == timeBegin){
            if(time2->data.getNgayTra() == timeEnd){
                doanhThu = Utils::intToString(time1->data.getDonGia() + time2->data.getDonGia());
                return doanhThu;
            }
            time2 = time2->next;
        }
        time1 = time1->next;
    }
}
void QuanLi::xemDanhSachLuaChonXemDoanhThu(){
    cout<<"1. XEM DOANH THU THEO NGAY."<<endl;
    cout<<"2. XEM DOANH THU THEO THANG."<<endl;
    cout<<"3. XEM DOANH THU THEO NAM."<<endl;
}
void QuanLi::xemDoanhThu() {
    string temp, doanhThu;
    int ktra = 1;
    while(ktra){
        ktra = 0;
        xemDanhSachLuaChonXemDoanhThu();
        cout<<"Vui long nhap lua chon: "<<endl;
        temp = Utils::nhap(1, 2);
        if(temp != "1" && temp != "2" && temp != "3"){
            cout<<"Nhap sai, vui long nhap lai!"<<endl;
            ktra = 1;
        }
    }
    if(temp == "1"){
        temp = Utils::nhapNgayThangNam();
        doanhThu = thongKe(temp, temp+1);
    }
    else if (temp == "2")
    {
        int ktra;
        string month, year, date;
        ktra = 1;
        while(ktra){
            ktra = 0;
            cout<<"Nhap thang muon xem (theo dinh dang mm/yyyy): ";
            date = Utils::nhap(4, 8);
            stringstream ss(date);
            getline(ss, month, '/');
            getline(ss, year, '/');
            if(Utils::stringToInt(month) > 12 || Utils::stringToInt(month) < 1){
                ktra = 1;
            }
            if(ktra){
                system("clear");
                cout<<"Nhap sai, vui long nhap lai!"<<endl;
            }
        }
        doanhThu = thongKe("01/"+ month +"/" + year, "31/" + month + "/" + year);
    }
    else if(temp == "3"){
        int ktra;
        string year, date;
        ktra = 1;
        while(ktra){
            ktra = 0;
            cout<<"Nhap nam muon xem (theo dinh dang yyyy): ";
            date = Utils::nhap(1, 5);
            if(Utils::stringToInt(date) < 1900){
                ktra = 1;
            }
            if(ktra){
                system("clear");
                cout<<"Nhap sai, vui long nhap lai!"<<endl;
            }
        }
        doanhThu = thongKe("01/01/"+date, "31/12/"+date);
    }
}
void QuanLi::work() {
    cout << "Da dang nhap vao tai khoan quan li" << endl;
}