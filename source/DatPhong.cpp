#include "./header/DatPhong.h"

/**
 * @brief Hàm khởi tạo mặc định cho lớp DatPhong.
 * 
 * Hàm này khởi tạo một đối tượng DatPhong với các giá trị mặc định.
 */
DatPhong::DatPhong() {
    this->maDatPhong    = "";
    this->phong         = nullptr;
    this->khachHang     = nullptr;
    this->ngayNhan      = 0;
    this->ngayTra       = 0;
    this->soLuongKhach  = 0;
    this->donGia        = 0;
}

/**
 * @brief Hàm khởi tạo cho lớp DatPhong.
 * 
 * @param MDP Mã đặt phòng.
 * @param NNhan Ngày nhận phòng (kiểu time_t).
 * @param NTra Ngày trả phòng (kiểu time_t).
 * @param SL Số lượng khách.
 * @param Gia Đơn giá.
 */
DatPhong::DatPhong(string MDP, time_t NNhan, time_t NTra, int SL, int Gia) {
    this->maDatPhong    = "";
    this->phong         = nullptr;
    this->khachHang     = nullptr;
    this->ngayNhan      = 0;
    this->ngayTra       = 0;
    this->soLuongKhach  = 0;
    this->donGia        = 0;
    
    setMaDatPhong(MDP);
    setNgayNhanAndNgayTra(NNhan, NTra);
    setSoLuongKhach(SL);
    setDonGia(Gia);
}

/**
 * @brief Hàm sao chép cho lớp DatPhong.
 * 
 * @param other Đối tượng DatPhong khác để sao chép.
 */
DatPhong::DatPhong(const DatPhong &other) {
    this->maDatPhong    = other.maDatPhong;
    this->phong         = other.phong;
    this->khachHang     = other.khachHang;
    this->ngayNhan      = other.ngayNhan;
    this->ngayTra       = other.ngayTra;
    this->soLuongKhach  = other.soLuongKhach;
    this->donGia        = other.donGia;
}

/**
 * @brief Lấy mã đặt phòng.
 * 
 * @return Mã đặt phòng dưới dạng chuỗi.
 */
string DatPhong::getMaDatPhong() const {
    return this->maDatPhong;
} 

/**
 * @brief Lấy phòng.
 * 
 * @return Phong* con trỏ trỏ tới phòng.
 */
Phong *DatPhong::getPhong() const {
    try {
        if(this->phong == nullptr) {
            throw "DatPhong::getPhong::Phong khong ton tai!";
        }
        return this->phong;
    }
    catch(const string msg) {
        cerr << msg << endl;
    }
    return nullptr;
}

/**
 * @brief Lấy khách hàng.
 * 
 * @return KhachHang* con trỏ trỏ tới khách hàng.
 */
KhachHang *DatPhong::getKhachHang() const {
    try {
        if(this->khachHang == nullptr) {
            throw "DatPhong::getKhachHang::KhachHang khong ton tai!";
        }
        return this->khachHang;
    }
    catch(const string msg) {
        cerr << msg << endl;
    }
    return nullptr;
}

/**
 * @brief Lấy ngày nhận phòng.
 * 
 * @return Ngày nhận phòng dưới dạng time_t.
 */
time_t DatPhong::getNgayNhan() const {
    return this->ngayNhan;
}

/**
 * @brief Lấy ngày trả phòng.
 * 
 * @return Ngày trả phòng dưới dạng time_t.
 */
time_t DatPhong::getNgayTra() const {
    return this->ngayTra;
}

/**
 * @brief Lấy số lượng khách.
 * 
 * @return Số lượng khách.
 */
int DatPhong::getSoLuongKhach() const {
    return this->soLuongKhach;
}

/**
 * @brief Lấy đơn giá.
 * 
 * @return Đơn giá.
 */
int DatPhong::getDonGia() const {
    return this->donGia;
}

/**
 * @brief Thiết lập mã đặt phòng.
 * 
 * Phương thức này sẽ gán giá trị mã đặt phòng cho thuộc tính maDatPhong của đối tượng DatPhong.
 * 
 * @param MDP Mã đặt phòng mới.
 */
void DatPhong::setMaDatPhong(string MDP) {
    try {
        if(Utils::isNumberOnly(MDP)) {
            this->maDatPhong = MDP;
        } else {
            throw "DatPhong::setMaDatPhong::Ma dat phong khong hop le!";
        }
    }
    catch(const char *msg) {
        cerr << msg << endl;
    }
}

/**
 * @brief Thiết lập phòng.
 * 
 * Phương thức này sẽ gán 1 con trỏ Phong* cho thuộc tính phong của đối tượng DatPhong.
 */
void DatPhong::setPhong(Phong *phong) {
    this->phong = phong;
    phong->themDatPhong(this);
}

/**
 * @brief Thiết lập khách hàng.
 * 
 * Phương thức này sẽ gán 1 con trỏ KhachHang* cho thuộc tính khachHang của đối tượng DatPhong.
 */
void DatPhong::setKhachHang(KhachHang *khachHang) {
    this->khachHang = khachHang;
    khachHang->themDatPhong(this);
}  

/**
 * @brief Thiết lập ngày nhận, trả phòng.
 * 
 * Phương thức này sẽ gán giá trị ngày nhận phòng, ngày trả phòng cho thuộc tính ngayNhan, ngayTra của đối tượng DatPhong.
 * 
 * @param NNhan Ngày nhận phòng mới.
 * @param NTra Ngày trả phòng mới.
 */
void DatPhong::setNgayNhanAndNgayTra(time_t NNhan, time_t NTra) {
    try {
        if(Utils::isDate(Utils::dateToString(NNhan)) && 
        Utils::isDate(Utils::dateToString(NTra))) {
            if(NNhan < NTra) {
                this->ngayNhan = NNhan;
                this->ngayTra = NTra;
            }
            else throw "DatPhong::setNgayNhanAndNgayTra::Ngay nhan phai nho hon ngay tra!";
        } else {
            throw "DatPhong::setNgayNhanAndNgayTra::Ngay nhap khong hop le!";
        }
    }
    catch(const char *msg) {
        cerr << msg << endl;
    }
}

/**
 * @brief Thiết lập số lượng khách.
 * 
 * Phương thức này sẽ gán giá trị số lượng khách cho thuộc tính soLuongKhach của đối tượng DatPhong.
 * 
 * @param SL Số lượng khách mới.
 */
void DatPhong::setSoLuongKhach(int SL) {
    try {
        if(SL > 0) {
            this->soLuongKhach = SL;
        } else {
            throw "DatPhong::setSoLuongKhach::So luong khach khong hop le!";
        }
    }
    catch(const char *msg) {
        cerr << msg << endl;
    }
}

/**
 * @brief Thiết lập đơn giá.
 * 
 * Phương thức này sẽ gán giá trị đơn giá cho thuộc tính donGia của đối tượng DatPhong.
 * 
 * @param Gia Đơn giá mới.
 */
void DatPhong::setDonGia(int Gia) {
    try {
        if(Gia > 0) {
            this->donGia = Gia;
        } else {
            throw "DatPhong::setDonGia::Don gia khong hop le!";
        }
    }
    catch(const char *msg) {
        cerr << msg << endl;
    }
}

/**
 * @brief Tính tổng tiền.
 * 
 * Phương thức này sẽ tính tổng tiền của đơn đặt phòng dựa trên số ngày thuê và đơn giá.
 */
int DatPhong::tongTien() const{
    int sum = 0;
    int soNgay = (this->getNgayTra() - this->getNgayNhan())/86400;     //86400 = 24*60*60 là số giây trong 1 ngày
    sum = this->getDonGia() * soNgay;
    return sum;
}

/**
 * @brief Hiển thị thông tin đặt phòng.
 * 
 * Hàm này sẽ in ra các thông tin chi tiết của một đặt phòng bao gồm:
 * - Mã đặt phòng
 * - Mã phòng
 * - ID khách hàng
 * - Ngày nhận phòng (định dạng chuỗi)
 * - Ngày trả phòng (định dạng chuỗi)
 * - Số lượng khách
 * - Đơn giá
 */
ostream &operator<<(ostream &out, const DatPhong &dp) {
    Utils::outputData("-----------THONG-TIN-DAT-PHONG---------\n", CONSOLE);
    Utils::outputData("Ma Dat Phong: ", CONSOLE);
    Utils::outputData(dp.maDatPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("Loai Phong: ", CONSOLE);
    Utils::outputData(dp.phong->getLoaiPhong()->getLoaiPhong() + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ma Phong: ", CONSOLE);
    Utils::outputData(dp.phong->getMaPhong() + "\n", CONSOLE_OR_UI);
    Utils::outputData("ID Khach Hang: ", CONSOLE);
    Utils::outputData(dp.khachHang->getIDKhachHang() + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ngay Nhan: ", CONSOLE);
    Utils::outputData(Utils::dateToString(dp.ngayNhan) + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ngay Tra: ", CONSOLE);
    Utils::outputData(Utils::dateToString(dp.ngayTra) + "\n", CONSOLE_OR_UI);
    Utils::outputData("So Luong Khach: ", CONSOLE);
    Utils::outputData(Utils::intToString(dp.soLuongKhach) + "\n", CONSOLE_OR_UI);
    Utils::outputData("Don Gia: ", CONSOLE);
    Utils::outputData(Utils::chuanHoaSo(Utils::intToString(dp.donGia)) + " VND\n", CONSOLE_OR_UI);
    Utils::outputData("Tong Tien: ", CONSOLE);
    Utils::outputData(Utils::chuanHoaSo(Utils::intToString(dp.tongTien())) + " VND\n", CONSOLE_OR_UI);
    Utils::outputData("---------------------------------------\n", CONSOLE);
    return out;
}
