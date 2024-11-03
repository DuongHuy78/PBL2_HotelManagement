#include "./header/QLKhachHang.h"
QLKhachHang::QLKhachHang() {

}

QLKhachHang::~QLKhachHang() {

}

LinkedList<KhachHang> &QLKhachHang::getDSKH() {
    return this->DSKH;
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
    string IDKhachHang;
    Node<KhachHang> *p = DSKH.getHead()->next;
    if(p == DSKH.getHead()) {
        IDKhachHang = "100000";    //số đầu tên là chia đối tượng kh, nhân viên,...
    }
    else{
        IDKhachHang = p->prev->data.getIDKhachHang();
    }
    return IDKhachHang;
}

string QLKhachHang::taoIDKhachHang() {      //tạo ID khách hàng bằng cách lấy ID khách hàng cuối cùng tăng lên 1
                                            //chứ ko lưu vào file
    string IDKhachHang;
    if( this->getMaxIDKhachHang() == "199999") {
        return "-1";      //đã đạt giới hạn số khách hàng
    }
    else{
        string head =  this->getMaxIDKhachHang().substr(0, 1);   //lấy số đầu
        string tail =  this->getMaxIDKhachHang().substr(1);      //lấy số sau
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
