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

Node<DatPhong> *QLDatPhong::getHead() {
    return this->DSDP.getHead();
}
LinkedList<DatPhong> &QLDatPhong::getDanhSachDatPhong() {
    return this->DSDP;
}

DatPhong QLDatPhong::nhapThongTin() {
    int Ktra = 1;
    string temp, soLuongKhach;
    time_t ngayNhan, ngayTra;
    cout <<"Nhap thong tin dat phong :" << endl;
    while(Ktra){                                        //Kiểm tra xem ngày nhận và ngày trả có hợp lệ không
        Ktra = 0;           //Ktra = 0 nếu nhập đúng
        cout <<"Nhap ngay nhan: ";
        temp = Utils::nhap(4, 11);              //ngày nhận có 10 ký tự 01/34/6789
        ngayNhan = Utils::stringToTime(temp);
        if(ngayNhan < time(0)){
            cout <<"Ngay nhan phai lon hon ngay hien tai" << endl;
            Ktra = 1;
        }
        cout <<"Nhap ngay tra: ";
        temp = Utils::nhap(4, 11);              //ngày nhận có 10 ký tự 01/34/6789
        ngayNhan = Utils::stringToTime(temp);
        if(ngayTra < ngayNhan){
            cout <<"Ngay tra phai lon hon ngay nhan" << endl;
            Ktra = 1;
        }
        if(Ktra) {
            system("clear");
            cout <<"Có vẻ đã có sai sot vui long nhap lai!" << endl;
        }
    }

    Ktra = 1;
    while(Ktra) {                           //Kiểm tra số lượng khách có hợp lệ không
        Ktra = 0;
        cout <<"Nhap so luong khach (neu lon hon 4 vui long dat 2 phong): ";
        soLuongKhach = Utils::nhap(1, 2);           //số lượng khách có 1 ký tự
        if(Utils::stringToInt(soLuongKhach) > 4) {
            cout <<"So luong khach qua nhieu, vui long dat 2 phong" << endl;
            Ktra = 1;
        }
        else if(Utils::stringToInt(soLuongKhach) < 1) {
            cout <<"So luong khach khong hop le, vui long nhap lai" << endl;
            Ktra = 1;
        }
    }
    
    cout <<"Nhap ma phong: ";

}

