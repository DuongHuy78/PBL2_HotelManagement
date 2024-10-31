#include "./header/QLKhachSan.h"

QLKhachSan::QLKhachSan() {
    UI_init();
    current_Data = this;
}

QLKhachSan::~QLKhachSan() {

}

void QLKhachSan::inputTaiKhoan(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    int index = 0;
    string line, username, password, ID;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        username = Utils::getSubstringUntilX(line, index, ',');
        password = Utils::getSubstringUntilX(line, index, ',');
        ID       = Utils::getSubstringUntilX(line, index, '\n');
        TaiKhoan newTaiKhoan(ID, username, password);
        QLTK.themTaiKhoan(newTaiKhoan);
        role_value role = newTaiKhoan.getRole();
        if(role == NHANVIEN) {
            nhanVien.setIDNhanVien(ID);
        } 
        else if(role == QUANLI) {
            quanLi.setIDQuanLi(ID);
        }
        index = 0;
    }  
    fi.close();
}

void QLKhachSan::inputKhachHang(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    int index = 0;
    string line, ID, name, birthday, phone, gender;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        ID       = Utils::getSubstringUntilX(line, index, ',');
        name     = Utils::getSubstringUntilX(line, index, ',');
        birthday = Utils::getSubstringUntilX(line, index, ',');
        phone    = Utils::getSubstringUntilX(line, index, ',');
        gender   = Utils::getSubstringUntilX(line, index, '\n');
        KhachHang newKhachHang(ID, name, Utils::stringToDate(Utils::trim(birthday)), phone, Utils::stringToGender(gender));
        QLKH.themKhachHang(newKhachHang);
        index = 0;
    }  
    fi.close();
}

void QLKhachSan::inputLoaiPhong(string path) {
    QLLP.AddRangeLoaiPhong(path);
}

void QLKhachSan::inputPhong(string path) {
    //QLP.AddRangePhong(path);
}

void QLKhachSan::inputDatPhong(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    string line;
    int index = 0;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        string maDatPhong   = Utils::getSubstringUntilX(line, index, ',');
        string maPhong      = Utils::getSubstringUntilX(line, index, ',');
        string IDKhachHang  = Utils::getSubstringUntilX(line, index, ',');
        string ngayNhan     = Utils::getSubstringUntilX(line, index, ',');
        string ngayTra      = Utils::getSubstringUntilX(line, index, ',');
        string soLuongKhach = Utils::getSubstringUntilX(line, index, ',');
        string donGia       = Utils::getSubstringUntilX(line, index, '\n');
        DatPhong newDatPhong(maDatPhong, maPhong, IDKhachHang, 
        Utils::stringToDate(ngayNhan), Utils::stringToDate(ngayTra), 
        Utils::stringToInt(soLuongKhach), Utils::stringToInt(donGia));
        QLDP.themDatPhong(newDatPhong);
        index = 0;
    }  
    fi.close();
}


void QLKhachSan::outputTaiKhoan(string) {

}

void QLKhachSan::outputKhachHang(string) {

}

void QLKhachSan::outputLoaiPhong(string) {

}

void QLKhachSan::outputPhong(string) {

}

void QLKhachSan::outputDatPhong(string) {

}

void QLKhachSan::work() {
    gnk_Window_Loop();
}

NguoiDung *QLKhachSan::dangNhap(string username, string password) {
    string ID = QLTK.kiemTraTaiKhoan(username, password);
    if(ID != "") {
        if(ID == quanLi.getIDQuanLi()) {
            role = QUANLI;
            return &quanLi;
        }
        if(ID == nhanVien.getIDNhanVien()) {
            role = NHANVIEN;
            return &nhanVien;
        }
        role = KHACHHANG;
        return QLKH.timKiemKhachHang(ID);
    }
    return NULL;
}

void QLKhachSan::dangXuat() {
    role = UNDEFINED_ROLE;
}

void QLKhachSan::roomAvailability(time_t checkInDate, time_t checkOutDate) {
    LinkedList<Phong> &DSP = QLP.getDanhSachPhong();
    set<string> maPhongDaDat;
    cout << "check in date: " << Utils::dateToString(checkInDate) << endl;
    cout << "check out date: " << Utils::dateToString(checkOutDate) << endl;
    LinkedList<DatPhong> &DSDP = QLDP.getDanhSachDatPhong();
    Node<DatPhong> *p = DSDP.begin();
    while(p != DSDP.end()) {
        time_t ngayNhan = p->data.getNgayNhan();
        time_t ngayTra = p->data.getNgayTra();        
        if(!(ngayTra < checkInDate || checkOutDate < ngayNhan)) {
            cout << Utils::dateToString(ngayNhan) << " " << Utils::dateToString(ngayTra) << endl;
            maPhongDaDat.insert(p->data.getMaPhong());
        }        
        p = p->next;
    }

    Node<Phong> *p2 = DSP.begin();
    while(p2 != DSP.end()) {
        string maPhong = p2->data.getMaPhong();
        for(string i:maPhongDaDat) {
            cout << i << endl;
            if(maPhong == i) {
                p2 = p2->next;
                continue;
            }
        }
        p2->data.thongTinPhong();
        p2 = p2->next;
    }
}
