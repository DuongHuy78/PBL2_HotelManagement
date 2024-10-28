#include "./header/QLKhachHang.h"
QLKhachHang::QLKhachHang() {

}

QLKhachHang::~QLKhachHang() {

}


void QLKhachHang::themKhachHang(KhachHang kh) {
    DSKH.add(kh);
}

KhachHang *QLKhachHang::timKiemKhachHang(string ID) {
    Node<KhachHang> *p = DSKH.begin()->next;
    while(p != DSKH.begin()) {
        if(p->data.getIDKhachHang() == ID) return &p->data;
        p = p->next;
    }
    return NULL;
}

void QLKhachHang::suaThongTin(string ID) {
    Node<KhachHang> *p = DSKH.begin()->next;
    while(p != DSKH.begin()) {
        if(p->data.getIDKhachHang() == ID) {
            p->data.suaThongTin();
            return;
        }
        p = p->next;
    }
}

string QLKhachHang::getMaxIDKhachHang() {
    string IDKhachHang;
    Node<KhachHang> *p = DSKH.begin()->next;
    if(p->prev == p) {
        IDKhachHang = "100000";    //số đầu tên là chia đối tượng kh, nhân viên,...
    }
    else{
        IDKhachHang = p->prev->data.getIDKhachHang();
    }
    return IDKhachHang;
}

string QLKhachHang::taoIDKhachHang() {        //tạo ID khách hàng bằng cách lấy ID khách hàng cuối cùng tăng lên 1
                                            //chứ ko lưu vào file
    string IDKhachHang;
    QLKhachHang qlkh;
    if( qlkh.getMaxIDKhachHang() == "199999") {
        return "-1";      //đã đạt giới hạn số khách hàng
    }
    else{
        string head =  qlkh.getMaxIDKhachHang().substr(0, 1);   //lấy số đầu
        string tail =  qlkh.getMaxIDKhachHang().substr(1);      //lấy số sau
        int num = stoi(tail) + 1;
        IDKhachHang = head + to_string(num);
    }
    return IDKhachHang;
}

void QLKhachHang::xoaKhachHang(KhachHang *kh) {
    Node<KhachHang> *p = DSKH.begin()->next;
    while(p != DSKH.begin()) {
        if(&p->data == kh) {
            DSKH.remove(p);
            return;
        }
        p = p->next;
    }
}
