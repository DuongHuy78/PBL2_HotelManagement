#include "./header./QLLoaiPhong.h"
#include <bits/stdc++.h>
LinkedList<string> roomTypes;

QLLoaiPhong::~QLLoaiPhong() {
    Node<LoaiPhong *> *p = DSLP.begin();
    while(p != DSLP.end()) {
        delete p->data;
        p = p->next;
    }
}

void QLLoaiPhong::themLoaiPhong(LoaiPhong *NewLP){
    roomTypes.add(NewLP->getLoaiPhong());
    DSLP.add(NewLP);
}

void QLLoaiPhong::suaThongTin(const string& IDLoaiPhong){
    Node<LoaiPhong *> *p = DSLP.begin();
    while ((p != DSLP.end()))
    {
        if(p->data->getLoaiPhong() == IDLoaiPhong)
            {
                p->data->capNhatThongTin();
                cout << "Da cap nhat thong tin loai phong voi ID " << IDLoaiPhong << " thanh cong!" << endl;
                return;
            }
        p = p -> next;
    } 
    cout << "Khong tim thay Loai Phong!" << endl;
}


void QLLoaiPhong::xoaLoaiPhong(const string& IDLoaiPhong){
    Node<LoaiPhong *> *p = DSLP.begin();
    while( p != DSLP.end()) {
        if(p->data->getLoaiPhong() == IDLoaiPhong) {
            if(p->data->getSoLuongPhong() > 0) {
                Utils::outputData("Khong the xoa Loai Phong vi con phong thuoc loai phong nay!\n", CONSOLE);
                return;
            }
            else {
                delete p->data;
                DSLP.remove(p);
                Utils::outputData("Da xoa Loai Phong voi ID " + IDLoaiPhong + " thanh cong!\n", CONSOLE);
                return;
            }
        }
        p = p -> next;
    }
    Utils::outputData("Khong tim thay Loai Phong!\n", CONSOLE);
}

LoaiPhong *QLLoaiPhong::timLoaiPhong(string IDLoaiPhong){
    Node<LoaiPhong *> *p = DSLP.begin();
    while(p != DSLP.end()) {
        if(p->data->getLoaiPhong() == IDLoaiPhong) {
            return p->data;
        }
        p = p -> next;
    }
    return nullptr;
}


int QLLoaiPhong::soLuongKhach(string maLoaiPhong) {
    return timLoaiPhong(maLoaiPhong)->getSoLuongKhach();
}

int QLLoaiPhong::getGiaPhong(string maLoaiPhong) {
    return timLoaiPhong(maLoaiPhong)->getGiaPhong();
} 

LinkedList<LoaiPhong *>& QLLoaiPhong::getDSLP() {
    return DSLP;
}

ostream& operator<<(ostream& os, const QLLoaiPhong& ql) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-LOAI-PHONG----------------\n", CONSOLE);
    Utils::outputData("Danh sach loai phong: \n", CONSOLE);
    Node<LoaiPhong *> *p = ql.DSLP.begin();
    while(p != ql.DSLP.end()) {
        os << *p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}