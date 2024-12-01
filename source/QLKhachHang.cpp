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
    return nullptr;
}

KhachHang *QLKhachHang::timKiemKhachHangSDT(string SDT) {
    Node<KhachHang> *p = DSKH.getHead()->next;
    while(p != DSKH.getHead()) {
        if(p->data.getSoDienThoai() == SDT) 
            return &p->data;
        p = p->next;
    }
    return nullptr;
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
    cout<<"Khong tim thay khach hang!"<<endl;
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
    int size = 6;
    string IDKhachHang = "";
    string maxID = this->getMaxIDKhachHang();
    if(maxID == "199999") {
        return "";      //đã đạt giới hạn số khách hàng
    }
    else { 
        string head = maxID.substr(0, 1);   //lấy số đầu
        string tail = maxID.substr(1);      //lấy số sau
        int num = stoi(tail) + 1;
        tail = Utils::intToString(num);
        for(int i=0; i<(5-tail.size()); i++) {
            tail = "0" + tail;
        }
        IDKhachHang = head + tail;
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
    system("cls");
    KhachHang newKH;
    string temp;
    temp = this->taoIDKhachHang();     //tạo ID khách hàng mới
    newKH.setIDKhachHang(temp);

    Utils::outputData("Nhap thong tin khach hang: \n", CONSOLE);
    temp = Utils::inputWithCondition("Nhap ho ten: ", 1, MAX_NAME, ALPHABET_AND_SPACE_ONLY);
    newKH.setHoTen(Utils::chuanHoaTen(temp));
    
    temp = Utils::inputWithCondition("Nhap ngay sinh (dd/mm/yyyy): ", 1, 10, DATE);
    newKH.setNgaySinh(Utils::stringToDate(temp));

    temp = Utils::inputWithCondition("Nhap So dien thoai: ", 1, 10, VIETNAM_PHONE_NUMBER);
    newKH.setSoDienThoai(temp);

    temp = Utils::inputWithCondition("Nhap gioi tinh (Nam/Nu): ", 1, 3, GENDER);
    newKH.setGioiTinh(Utils::stringToGender(temp));

    Utils::outputData("Nhap du lieu khach hang thanh cong!\n", CONSOLE);
    return newKH;
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
    return os;
}