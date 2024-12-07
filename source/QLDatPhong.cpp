#include "./header/QLDatPhong.h"
QLDatPhong::QLDatPhong() {
    
}

QLDatPhong::~QLDatPhong() {
    Node<DatPhong *> *p = DSDP.begin();
    while(p != DSDP.end()) {
        delete p->data;
        p = p->next;
    }
}

// void QLDatPhong::setDSLP(QLLoaiPhong *DSLP) {
//     this->DSLP = DSLP;
// }

// void QLDatPhong::setDSP(QLPhong *DSP) {
//     this->DSP = DSP;
// }

// void QLDatPhong::setDSKH(QLKhachHang *DSKH) {
//     this->DSKH = DSKH;
// }

// void QLDatPhong::setcurrentID(string ID) {
//     this->currentID = ID;
// }

// void QLDatPhong::setRole(role_value role) {
//     this->role = role;
// }
void QLDatPhong::themDatPhong(DatPhong *DP) {
    DSDP.add(DP);
}

void QLDatPhong::xoaDatPhong(DatPhong *DP) {
    Node<DatPhong *> *p = DSDP.begin();
    while(p != DSDP.end()) {
        if(p->data == DP) {
            DSDP.remove(p);
            return;
        }
        p = p->next;
    }
}

DatPhong *QLDatPhong::timKiemDatPhong(string MDP) {
    Node<DatPhong *> *p = DSDP.begin();
    while(p != DSDP.end()) {
        if(p->data->getMaDatPhong() == MDP) 
            return p->data;
        p = p->next;
    }
    return nullptr;
}

/**
 * @brief Lấy mã đặt phòng lớn nhất
 * Nếu danh sách rỗng thì trả về 00000
 */
string QLDatPhong::getMaxMaDatPhong() {
    string MDP;
    Node<DatPhong *> *p = DSDP.begin();
    if(p == DSDP.end()) {
        MDP = "00000";
    }
    else{
        MDP = p->prev->prev->data->getMaDatPhong();
    }
    return MDP;
}
/**
 * @brief Tạo mã đặt phòng mới
 * Nêu mã đặt phòng cuối cùng là 99999 thì trả về 000001
 */
string QLDatPhong::taoMaDatPhong(){
    string MDPNew;
    if (this->getMaxMaDatPhong() == "99999") {
        MDPNew = "000001";
    }
    else{
        MDPNew = Utils::intToString(Utils::stringToInt(getMaxMaDatPhong()) + 1);
        int size = MDPNew.size();
        for(int i=0; i<(5-size); i++){
            MDPNew="0"+MDPNew;
        }
    }
    return MDPNew;
}

LinkedList<DatPhong *> &QLDatPhong::getDSDP() {
    return this->DSDP;
}

ostream &operator<<(ostream &os, const QLDatPhong &ql) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-DAT-PHONG-----------------\n", CONSOLE);
    Utils::outputData("Danh sach dat phong: \n", CONSOLE);
    Node<DatPhong *> *p = ql.DSDP.begin();
    while(p != ql.DSDP.end()) {
        os << *p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}