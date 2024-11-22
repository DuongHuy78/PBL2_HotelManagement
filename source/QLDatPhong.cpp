#include "./header/QLDatPhong.h"
QLDatPhong::QLDatPhong() {
    
}

QLDatPhong::~QLDatPhong() {
    
}

void QLDatPhong::setDSLP(QLLoaiPhong *DSLP) {
    this->DSLP = DSLP;
}

void QLDatPhong::setDSP(QLPhong *DSP) {
    this->DSP = DSP;
}

void QLDatPhong::setDSKH(QLKhachHang *DSKH) {
    this->DSKH = DSKH;
}

void QLDatPhong::setcurrentID(string ID) {
    this->currentID = ID;
}

void QLDatPhong::setRole(role_value role) {
    this->role = role;
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
        MDP = p->prev->prev->data.getMaDatPhong();
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
        int size = MDPNew.size();
        for(int i=0; i<(5-size); i++){
            MDPNew="0"+MDPNew;
        }
    }
    return MDPNew;
}

Node<DatPhong> *QLDatPhong::getHead() {
    return this->DSDP.getHead();
}
LinkedList<DatPhong> &QLDatPhong::getDanhSachDatPhong() {
    return this->DSDP;
}

/**
 * Duyệt qua 'danh sách đặt phòng' kiểm tra các phòng đang được đặt
 * Từ đó đặt trạng thái phòng của các phòng đó là bận 
 * Sau đó in ra danh sách những phòng không có trạng thái bận
 */
void QLDatPhong::roomAvailability(time_t checkInDate, time_t checkOutDate, int soLuongKhach, LinkedList<Phong> &phongTrong) {
    set<string> maPhongDaDat;
    cout << "check in date: " << Utils::dateToString(checkInDate) << endl;
    cout << "check out date: " << Utils::dateToString(checkOutDate) << endl;

    Node<DatPhong> *p = DSDP.getHead()->next;

    while(p != DSDP.getHead()) {
        time_t ngayNhan = p->data.getNgayNhan();
        time_t ngayTra = p->data.getNgayTra();
        if(!(ngayTra < checkInDate || checkOutDate < ngayNhan )) {
            maPhongDaDat.insert(p->data.getMaPhong());
        }        
        p = p->next;
    }

    Node<Phong> *p2 = DSP->getHead()->next;
    while(p2 != DSP->getHead()) {
        string maPhong = p2->data.getMaPhong();
        bool isAvailable = true;
        for(string i:maPhongDaDat) {
            if(maPhong == i) {
                isAvailable = false;
                break;
            }
        }
        if(isAvailable && DSLP->soLuongKhach(p2->data.getLoaiPhong()) >= soLuongKhach) {
            cout << p2->data;
            phongTrong.add(p2->data);
        }
        p2 = p2->next;
    }

    if(phongTrong.getHead()->next == phongTrong.getHead()) {
        cout << "Khong co phong trong cho thoi gian nay!\n";
    }
}

DatPhong QLDatPhong::nhapThongTin() {

    int ktra = 1, donGia;
    string temp, soLuongKhach;
    time_t ngayNhan, ngayTra;
    Node<Phong> *p = DSP->getHead()->next;          // lấy để lấy đơn giá

    cout <<"Nhap thong tin dat phong :" << endl;
    while(ktra){                                        //Kiểm tra xem ngày nhận và ngày trả có hợp lệ không
        ktra = 0;           //ktra = 0 nếu nhập đúng
        temp = Utils::nhapNgayThangNam("Nhap ngay nhan(theo dinh dang dd/mm/yyyy): ");              //ngày nhận có 10 ký tự 01/34/6789
        ngayNhan = Utils::stringToDate(temp);
        if(ngayNhan < time(0)){
            cout <<"Ngay nhan phai lon hon ngay hien tai" << endl;
            ktra = 1;
            continue;
        }
        temp = Utils::nhapNgayThangNam("Nhap ngay tra(theo dinh dang dd/mm/yyyy): ");              //ngày nhận có 10 ký tự 01/34/6789
        ngayTra = Utils::stringToDate(temp);

        if(ngayTra < ngayNhan){
            cout <<"Ngay tra phai lon hon ngay nhan" << endl;
            ktra = 1;
        }
        if(ktra) {
            system("cls");
            cout << "Co ve da co sai sot vui long nhap lai!" << endl;
        }
    }

    ktra = 1;
    while(ktra) {                           //Kiểm tra số lượng khách có hợp lệ không
        ktra = 0;
        cout <<"Nhap so luong khach (neu lon hon 4 vui long dat 2 phong): ";
        soLuongKhach = Utils::nhap(1, 2);           //số lượng khách có 1 ký tự
        if(Utils::stringToInt(soLuongKhach) > 4) {
            cout <<"So luong khach qua nhieu, vui long dat 2 phong" << endl;
            ktra = 1;
        }
        else if(Utils::stringToInt(soLuongKhach) < 1) {
            cout <<"So luong khach khong hop le, vui long nhap lai" << endl;
            ktra = 1;
        }
    }
    LinkedList<Phong> phongTrong;
                                                        //in ra danh sách phòng trống sau đó ktra
    roomAvailability(ngayNhan, ngayTra, Utils::stringToInt(soLuongKhach), phongTrong);
    ktra = 1;        //Kiểm tra mã phòng có hợp lệ không
    while(ktra){
        cout <<"Nhap ma phong: ";
        temp = Utils::nhap(3, 7);
        Node<Phong> *p = phongTrong.getHead()->next;
        while(p!=phongTrong.getHead()) {
            if(p->data.getMaPhong() == temp) {
                ktra = 0;
                break;
            }
            p = p->next;
        }
    }

    donGia = DSLP->getGiaPhong(p->data.getLoaiPhong());
    //Lựa chọn đăng nhập cho ai
    if( role == NHANVIEN){
        KhachHang KH = DSKH->nhapThongTin();
        DSKH->themKhachHang(KH);
        DatPhong newDP(taoMaDatPhong(), temp, KH.getIDKhachHang(), ngayNhan, ngayTra, Utils::stringToInt(soLuongKhach), donGia);
        return newDP;
    }
    else if(role == KHACHHANG){
        string ma=taoMaDatPhong();
        DatPhong newDP(ma, temp, currentID, ngayNhan, ngayTra, Utils::stringToInt(soLuongKhach), donGia);
        return newDP;
    }
}

