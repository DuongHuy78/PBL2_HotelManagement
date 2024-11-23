#include "./header/QLKhachHang.h"
QLKhachHang::QLKhachHang() {

}

QLKhachHang::~QLKhachHang() {
    
}

void QLKhachHang::themKhachHang(KhachHang kh) {
    DSKH.add(kh);
}

KhachHang *QLKhachHang::timKiemKhachHang(string ID) {
    Node<KhachHang> *p = DSKH.getHead()->next;
    while(p != DSKH.getHead()) {
        if(p->data.getIDKhachHang() == ID) 
            return &p->data;
        p = p->next;
    }
    return NULL;
}

void QLKhachHang::suaThongTin(string ID) {
    Node<KhachHang> *p = DSKH.getHead()->next;
    while(p != DSKH.getHead()) {
        if(p->data.getIDKhachHang() == ID) {
            p->data.suaThongTin();
            return;
        }
        p = p->next;
    }
}

string QLKhachHang::getMaxIDKhachHang() {
    string IDKhachHang = "";
    Node<KhachHang> *p = DSKH.getHead();
    if(p->prev == DSKH.getHead()) {
        IDKhachHang = "100000";    //số đầu tên là chia đối tượng kh, nhân viên,...
    }
    else {
        IDKhachHang = p->prev->data.getIDKhachHang();
    }
    return IDKhachHang;
}

string QLKhachHang::taoIDKhachHang() {      //tạo ID khách hàng bằng cách lấy ID khách hàng cuối cùng tăng lên 1
                                            //chứ ko lưu vào file
    string IDKhachHang = "";
    string maxID = this->getMaxIDKhachHang();
    if(maxID == "199999") {
        return "";      //đã đạt giới hạn số khách hàng
    }
    else { 
        string head = maxID.substr(0, 1);   //lấy số đầu
        string tail = maxID.substr(1);      //lấy số sau
        int num = stoi(tail) + 1;
        IDKhachHang = head + to_string(num);
    }
    return IDKhachHang;
}

void QLKhachHang::xoaKhachHang(KhachHang *kh) {
    Node<KhachHang> *p = DSKH.getHead()->next;
    while(p != DSKH.getHead()) {
        if(&p->data == kh) {
            DSKH.remove(p);
            return;
        }
        p = p->next;
    }
}

KhachHang QLKhachHang::nhapThongTin() {
    KhachHang newKH;
    gender_value gender = UNDEFINED_GENDER;
    string temp;
    temp = this->taoIDKhachHang();     //tạo ID khách hàng mới
    newKH.setIDKhachHang(temp);

    cout << "Nhap thong tin khach hang" << endl;
    cout << "Nhap ho ten : ";
    temp = Utils::nhap(2, MAX_NAME+1);
    newKH.setHoTen(Utils::chuanHoaTen(temp));
    
    temp = Utils::nhapNgaySinh();
    newKH.setNgaySinh(Utils::stringToDate(temp));

    cout << "Nhap So dien thoai : ";
    newKH.setSoDienThoai(Utils::NhapSoDienThoai());

    while(1) {
        cout << "Nhap gioi tinh (Nam/Nu): ";
        temp = Utils::nhap(2, 4);
        gender = Utils::stringToGender(temp);
        if(gender != UNDEFINED_GENDER) break;
        system("cls");
        cout << "Nhap sai, vui long nhap lai!" << endl;
    }
    gender = Utils::stringToGender(temp);
    newKH.setGioiTinh(gender);
    return newKH;
}

void QLKhachHang::display() {
    Node<KhachHang> *p = DSKH.begin();
    while(p != DSKH.end()) {
        cout << p->data << endl;
        p = p->next;
    }
}

ostream& operator<<(ostream &os, const QLKhachHang &qlkh) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-KHACH-HANG-----------------\n", CONSOLE);
    Utils::outputData("Danh sach khach hang: \n", CONSOLE);
    Node<KhachHang> *p = qlkh.DSKH.begin();
    while(p != qlkh.DSKH.end()) {
        os << p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    Utils::outputData("--------------------------------------------------------------\n", CONSOLE);
    return os;
}