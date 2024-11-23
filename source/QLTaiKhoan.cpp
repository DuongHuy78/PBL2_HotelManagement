#include "header/QLTaiKhoan.h"

QLTaiKhoan::QLTaiKhoan() {

}

QLTaiKhoan::~QLTaiKhoan() {

}

void QLTaiKhoan::themTaiKhoan(TaiKhoan tk) {
    DSTK.add(tk);
}

void QLTaiKhoan::xoaTaiKhoan(TaiKhoan *tk) {
    Node<TaiKhoan> *p = DSTK.getHead();
    while(p != DSTK.getHead()) {
        if(&p->data == tk) {
            DSTK.remove(p);
            return;
        }
        p = p->next;
    }
}

void QLTaiKhoan::suaThongTinTaiKhoan(string ID) {
    
}

string QLTaiKhoan::kiemTraTaiKhoan(string username, string pass) {
    Node<TaiKhoan> *p = DSTK.getHead()->next;
    while(p != DSTK.getHead()) {
        if(p->data.getUsername() == username 
        && p->data.getPassword() == pass) return p->data.getID();
        p = p->next;
    }
    return "";
}

TaiKhoan *QLTaiKhoan::getTaiKhoanByID(string ID) {
    Node<TaiKhoan> *p = DSTK.getHead();
    while(p != DSTK.getHead()) {
        if(p->data.getID() == ID) return &p->data;
        p = p->next;
    }
    return NULL;
}

LinkedList<TaiKhoan> &QLTaiKhoan::getDanhSachTaiKhoan() {
    return DSTK;
}

ostream& operator<<(ostream& os, const QLTaiKhoan& ql) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-TAI-KHOAN-----------------\n", CONSOLE);
    Utils::outputData("Danh sach tai khoan: \n", CONSOLE);
    Node<TaiKhoan> *p = ql.DSTK.begin();
    while(p != ql.DSTK.end()) {
        os << p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}