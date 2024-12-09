#include "./header/QLPhong.h"

QLPhong::~QLPhong() {
    Node<Phong *> *p = DSP.begin();
    while(p != DSP.end()) {
        delete p->data;
        p = p->next;
    }
}

void QLPhong::themPhong(Phong *newPhong) {
    this->DSP.add(newPhong);
}

void QLPhong::xoaPhong(const string& MP){
    Node<Phong *> *p = DSP.begin();
    while(p != DSP.end()) {
        if(p->data->getMaPhong() == MP) {
            if(p->data->getSoLuongDatPhong() > 0) {
                Utils::outputData("Phong " + MP + " da duoc su dung!\n", CONSOLE);
                Utils::pauseConsole();
                return;
            }
            else {
                p->data->clearLoaiPhong();
                delete p->data;
                DSP.remove(p);
                Utils::outputData("Da xoa Phong voi ID: " + MP + "\n", CONSOLE);
                Utils::pauseConsole();
                return;
            }
        }
        p = p -> next;
    }
    Utils::outputData("Khong tim thay phong: " + MP + "\n", CONSOLE);
}

void QLPhong::setQLLP(QLLoaiPhong *QLLP) {
    this->QLLP = QLLP;
}

Phong *QLPhong::timPhong(string MP){
    Node<Phong *> *p = DSP.begin();
    while(p != DSP.end()){
        if(p->data->getMaPhong() == MP) {
            return p->data;
        }
        p = p -> next;
    }
    return nullptr;
}

LinkedList<Phong *> &QLPhong::getDSP() {
    return this->DSP;
}

ostream &operator<<(ostream &os, QLPhong &qlPhong) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-PHONG-----------------\n", CONSOLE);
    Utils::outputData("Danh sach phong: \n", CONSOLE);
    Node<Phong *> *p = qlPhong.DSP.begin();
    while (p != qlPhong.DSP.end()) {
        os << *p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}



