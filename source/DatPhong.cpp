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
    this->maDatPhong    = MDP;
    this->maPhong       = MP;
    this->IDKhachHang   = MKH;
    this->ngayNhan      = NNhan;
    this->ngayTra       = NTra;
    this->soLuongKhach  = SL;
    this->donGia        = Gia;
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
void DatPhong::setMaDatPhong(string MDP) {
    this->maDatPhong = MDP;
}

/**
 * @brief Thiết lập mã phòng.
 * 
 * Phương thức này sẽ gán giá trị mã phòng cho thuộc tính maPhong của đối tượng DatPhong.
 * 
 * @param MP Mã phòng mới.
 */
void DatPhong::setMaPhong(string MP) {
    this->maPhong = MP;
}

/**
 * @brief Thiết lập mã khách hàng.
 * 
 * Phương thức này sẽ gán giá trị mã khách hàng cho thuộc tính IDKhachHang của đối tượng DatPhong.
 * 
 * @param MKH Mã khách hàng mới.
 */
void DatPhong::setIDKhachHang(string MKH) {
    this->IDKhachHang = MKH;
}

/**
 * @brief Thiết lập ngày nhận phòng.
 * 
 * Phương thức này sẽ gán giá trị ngày nhận phòng cho thuộc tính ngayNhan của đối tượng DatPhong.
 * 
 * @param NNhan Ngày nhận phòng mới.
 */
void DatPhong::setNgayNhan(time_t NNhan) {
    this->ngayNhan = NNhan;
}

/**
 * @brief Thiết lập ngày trả phòng.
 * 
 * Phương thức này sẽ gán giá trị ngày trả phòng cho thuộc tính ngayTra của đối tượng DatPhong.
 * 
 * @param NTra Ngày trả phòng mới.
 */
void DatPhong::setNgayTra(time_t NTra) {
    this->ngayTra = NTra;
}

/**
 * @brief Thiết lập số lượng khách.
 * 
 * Phương thức này sẽ gán giá trị số lượng khách cho thuộc tính soLuongKhach của đối tượng DatPhong.
 * 
 * @param SL Số lượng khách mới.
 */
void DatPhong::setSoLuongKhach(int SL) {
    this->soLuongKhach = SL;
}

/**
 * @brief Thiết lập đơn giá.
 * 
 * Phương thức này sẽ gán giá trị đơn giá cho thuộc tính donGia của đối tượng DatPhong.
 * 
 * @param Gia Đơn giá mới.
 */
void DatPhong::setDonGia(int Gia) {
    this->donGia = Gia;
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
void DatPhong::xemThongTin() {
    cout << maDatPhong << endl;
    cout << maPhong << endl;
    cout << IDKhachHang << endl;
    cout << Utils::dateToString(ngayNhan) << endl;
    cout << Utils::dateToString(ngayTra) << endl;
    cout << soLuongKhach << endl;
    cout << donGia << endl;
}
