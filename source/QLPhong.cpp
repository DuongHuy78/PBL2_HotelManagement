#include "./header/QLPhong.h"

QLPhong::QLPhong() {

}

QLPhong::~QLPhong() {

}
    
void QLPhong::xemPhong(){
    cout << "Day la danh sach phong cua Hotel Del Luna: "<< endl;
    cout << left << setw(12) << "MaPhong" << "LoaiPhong" << endl;
    cout << string(24, '-') << endl;

    Node<Phong> *p = DSP.begin();
      while(p != DSP.end()){
        p->data.xuatThongTin();
        p = p -> next;
      }
}

//NEW PHÒNG
void QLPhong::themPhong(const Phong& newPhong) {
    this->DSP.add(newPhong);
}

void QLPhong::xoaPhong(const string& MP){
    Node<Phong> *p = DSP.begin();
    while( p != DSP.end())
    {
        if(p->data.getMaPhong() == MP)
            {
                DSP.remove(p);
                cout << "Da xoa Phong voi ID: " << MP << endl;
                Utils::pauseConsole();
                return;
            }
        p = p -> next;
    }
    cout << "Khong tim thay Phong!" << endl;
}


void QLPhong::suaThongTin(const string& MP){
    Node<Phong> *p = DSP.begin();
    while ((p != DSP.end()))
    {
        if(p->data.getMaPhong() == MP)
            {
                p->data.capNhatThongTin();
                cout << "Da cap nhat thong tin phong voi ID " << MP << " thanh cong!" << endl;
            }
        p = p -> next;
    } 
    cout << "Khong tim thay Phong!" << endl;
}

void QLPhong::setQLLP(QLLoaiPhong *QLLP) {
    this->QLLP = QLLP;
}

Phong *QLPhong::timPhong(string MP){
    Node<Phong> *p = DSP.begin();
    while(p != DSP.end()){
        if(p->data.getMaPhong() == MP)
            {
               return &p->data;
            }
        p = p -> next;
    }
    return NULL;
}

Phong QLPhong::nhapThongTin() {
    string temp;
    Phong tempPhong;
    temp = Utils::inputWithCondition("Nhap Ma Phong: ", 3, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
    tempPhong.setMaPhong(temp);
    temp = Utils::inputWithCondition("Nhap Loai Phong: ",3, MAX_IDLOAIPHONG, ROOM_TYPE);
    //tempPhong.setLoaiPhong(temp);
    return tempPhong;
}

LinkedList<Phong> &QLPhong::getDSP() {
    return this->DSP;
}

// Node<Phong> *QLPhong::getHead() {
//     return this->DSP.getHead();
// }

ostream &operator<<(ostream &os, QLPhong &qlPhong) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-PHONG-----------------\n", CONSOLE);
    Utils::outputData("Danh sach phong: \n", CONSOLE);
    Node<Phong> *p = qlPhong.DSP.begin();
    while (p != qlPhong.DSP.end()) {
        os << p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}



