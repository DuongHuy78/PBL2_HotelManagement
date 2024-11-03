#include "./header/QLDatPhong.h"
QLDatPhong::QLDatPhong() {
    
}

QLDatPhong::~QLDatPhong() {
    
}

void QLDatPhong::themDatPhong(DatPhong DP) {
    DSDP.add(DP);
}

void QLDatPhong::xoaDatPhong(DatPhong *DP) {
    Node<DatPhong> *p = DSDP.getHead()->next;
    while(p != DSDP.getHead()) {
        if(&p->data == DP) {
            DSDP.remove(p);
            return;
        }
        p = p->next;
    }
}

DatPhong *QLDatPhong::timKiemDatPhong(string MDP) {
    Node<DatPhong> *p = DSDP.getHead()->next;
    while(p != DSDP.getHead()) {
        if(p->data.getMaDatPhong() == MDP) 
            return &p->data;
        p = p->next;
    }
    return NULL;
}

/**
 * @brief Lấy mã đặt phòng lớn nhất
 * Nếu danh sách rỗng thì trả về 00000
 */
string QLDatPhong::getMaxMaDatPhong() {
    string MDP;
    Node<DatPhong> *p = DSDP.getHead()->next;
    if(p == DSDP.getHead()) {
        MDP = "00000";
    }
    else{
        MDP = p->prev->data.getMaDatPhong();
    }
    return MDP;
}
/**
 * @brief Tạo mã đặt phòng mới
 * Nêu mã đặt phòng cuối cùng là 99999 thì trả về 000001
 */
string QLDatPhong::taoMaDatPhong(){
    string MDPNew;
    Node<DatPhong> *p = DSDP.getHead()->next;
    if (this->getMaxMaDatPhong() == "99999") {
        MDPNew = "000001";
    }
    else{
        MDPNew = Utils::intToString(Utils::stringToInt(getMaxMaDatPhong()) + 1);
    }
}
LinkedList<DatPhong> &QLDatPhong::getDanhSachDatPhong() {
    return this->DSDP;
}
