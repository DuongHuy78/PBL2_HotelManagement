#include "./header/DatPhong.h"

/**
 * @brief Hàm khởi tạo mặc định cho lớp DatPhong.
 * 
 * Hàm này khởi tạo một đối tượng DatPhong với các giá trị mặc định.
 */
DatPhong::DatPhong() {
    this->maDatPhong    = "";
    this->maPhong       = "";
    this->IDKhachHang   = "";
    this->ngayNhan      = 0;
    this->ngayTra       = 0;
    this->soLuongKhach  = 0;
    this->donGia        = 0;
}

/**
 * @brief Hàm khởi tạo cho lớp DatPhong.
 * 
 * @param MDP Mã đặt phòng.
 * @param MP Mã phòng.
 * @param MKH Mã khách hàng.
 * @param NNhan Ngày nhận phòng (kiểu time_t).
 * @param NTra Ngày trả phòng (kiểu time_t).
 * @param SL Số lượng khách.
 * @param Gia Đơn giá.
 */
DatPhong::DatPhong(string MDP, string MP, string MKH, time_t NNhan, time_t NTra, int SL, int Gia) {
    this->maDatPhong    = "";
    this->maPhong       = "";
    this->IDKhachHang   = "";
    this->ngayNhan      = 0;
    this->ngayTra       = 0;
    this->soLuongKhach  = 0;
    this->donGia        = 0;
    
    setMaDatPhong(MDP);
    setMaPhong(MP);
    setIDKhachHang(MKH);
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
    this->maPhong       = other.maPhong;
    this->IDKhachHang   = other.IDKhachHang;
    this->ngayNhan      = other.ngayNhan;
    this->ngayTra       = other.ngayTra;
    this->soLuongKhach  = other.soLuongKhach;
    this->donGia        = other.donGia;
}

DatPhong::~DatPhong() {}

/**
 * @brief Lấy mã đặt phòng.
 * 
 * @return Mã đặt phòng dưới dạng chuỗi.
 */
string DatPhong::getMaDatPhong() const {
    return this->maDatPhong;
} 

/**
 * @brief Lấy mã phòng.
 * 
 * @return Mã phòng dưới dạng chuỗi.
 */
string DatPhong::getMaPhong() const {
    return this->maPhong;
}

/**
 * @brief Lấy mã khách hàng.
 * 
 * @return Mã khách hàng dưới dạng chuỗi.
 */
string DatPhong::getIDKhachHang() const {
    return this->IDKhachHang;
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
bool DatPhong::setMaDatPhong(string MDP) {
    if(Utils::isNumberOnly(MDP)) {
        this->maDatPhong = MDP;
        return true;
    } else {
        cerr << "DatPhong::setMaDatPhong::Ma dat phong khong hop le!" << endl;
        return false;
    }
}

/**
 * @brief Thiết lập mã phòng.
 * 
 * Phương thức này sẽ gán giá trị mã phòng cho thuộc tính maPhong của đối tượng DatPhong.
 * 
 * @param MP Mã phòng mới.
 */
bool DatPhong::setMaPhong(string MP) {
    if(Utils::isAlphabetAndNumberOnly(MP)) {
        this->maPhong = Utils::toUpper(MP);
        return true;
    } else {
        cerr << "DatPhong::setMaPhong::Ma phong khong hop le!" << endl;
        return false;
    }
}

/**
 * @brief Thiết lập mã khách hàng.
 * 
 * Phương thức này sẽ gán giá trị mã khách hàng cho thuộc tính IDKhachHang của đối tượng DatPhong.
 * 
 * @param MKH Mã khách hàng mới.
 */
bool DatPhong::setIDKhachHang(string MKH) {
    if(Utils::isNumberOnly(MKH)) {
        this->IDKhachHang = MKH;
        return true;
    } else {
        cerr << "DatPhong::setIDKhachHang::ID khach hang khong hop le!" << endl;
        return false;
    }
}

/**
 * @brief Thiết lập ngày nhận, trả phòng.
 * 
 * Phương thức này sẽ gán giá trị ngày nhận phòng, ngày trả phòng cho thuộc tính ngayNhan, ngayTra của đối tượng DatPhong.
 * 
 * @param NNhan Ngày nhận phòng mới.
 * @param NTra Ngày trả phòng mới.
 */
bool DatPhong::setNgayNhanAndNgayTra(time_t NNhan, time_t NTra) {
    if(Utils::isDate(Utils::dateToString(NNhan)) && 
       Utils::isDate(Utils::dateToString(NTra))) {
        if(NNhan < NTra) {
            this->ngayNhan = NNhan;
            this->ngayTra = NTra;
            return true;
        }
        return false;
    } else {
        cerr << "DatPhong::setNgayNhanAndNgayTra::Ngay nhan hoac ngay tra khong hop le!" << endl;
        cerr << "NNhan: " << Utils::dateToString(NNhan) << endl;
        cerr << "NTra: " << Utils::dateToString(NTra) << endl;
        return false;
    }
}

/**
 * @brief Thiết lập số lượng khách.
 * 
 * Phương thức này sẽ gán giá trị số lượng khách cho thuộc tính soLuongKhach của đối tượng DatPhong.
 * 
 * @param SL Số lượng khách mới.
 */
bool DatPhong::setSoLuongKhach(int SL) {
    if(SL > 0) {
        this->soLuongKhach = SL;
        return true;
    } else {
        cerr << "DatPhong::setSoLuongKhach::So luong khach khong hop le!" << endl;
        return false;
    }
}

/**
 * @brief Thiết lập đơn giá.
 * 
 * Phương thức này sẽ gán giá trị đơn giá cho thuộc tính donGia của đối tượng DatPhong.
 * 
 * @param Gia Đơn giá mới.
 */
bool DatPhong::setDonGia(int Gia) {
    if(Gia > 0) {
        this->donGia = Gia;
        return true;
    } else {
        cerr << "DatPhong::setDonGia::Don gia khong hop le!" << endl;
        return false;
    }
}

int DatPhong::tongTien() {
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
    Utils::outputData("Ma Phong: ", CONSOLE);
    Utils::outputData(dp.maPhong + "\n", CONSOLE_OR_UI);
    Utils::outputData("ID Khach Hang: ", CONSOLE);
    Utils::outputData(dp.IDKhachHang + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ngay Nhan: ", CONSOLE);
    Utils::outputData(Utils::dateToString(dp.ngayNhan) + "\n", CONSOLE_OR_UI);
    Utils::outputData("Ngay Tra: ", CONSOLE);
    Utils::outputData(Utils::dateToString(dp.ngayTra) + "\n", CONSOLE_OR_UI);
    Utils::outputData("So Luong Khach: ", CONSOLE);
    Utils::outputData(Utils::intToString(dp.soLuongKhach) + "\n", CONSOLE_OR_UI);
    Utils::outputData("Don Gia: ", CONSOLE);
    Utils::outputData(Utils::chuanHoaSo(Utils::intToString(dp.donGia)) + " VND\n", CONSOLE_OR_UI);
    Utils::outputData("---------------------------------------\n", CONSOLE);
    return out;
}
