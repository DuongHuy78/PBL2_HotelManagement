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
        cout << p->data.getUsername() << " " << username << endl;
        cout << p->data.getPassword() << " " << pass << endl;
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