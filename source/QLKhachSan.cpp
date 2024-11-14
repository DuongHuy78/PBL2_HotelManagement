#include "./header/QLKhachSan.h"

/**
 * @brief Hàm khởi tạo của lớp QLKhachSan.
 * 
 * Hàm này khởi tạo đối tượng QLKhachSan, gọi hàm UI_init() để khởi tạo giao diện người dùng
 * và gán con trỏ current_Data trỏ đến đối tượng hiện tại.
 */
QLKhachSan::QLKhachSan() {
    UI_init();
    current_Data = this;
    nhanVien.setDSKH(&QLKH);
    nhanVien.setDSDP(&QLDP);
}

QLKhachSan::~QLKhachSan() {}

/**
 * @brief Hàm đọc thông tin tài khoản từ file và thêm vào danh sách tài khoản.
 * 
 * Hàm này sẽ mở file tại đường dẫn được cung cấp, đọc từng dòng trong file và 
 * tách thông tin tài khoản (tên đăng nhập, mật khẩu, ID) từ mỗi dòng. Sau đó, 
 * tạo đối tượng TaiKhoan mới và thêm vào danh sách tài khoản. Nếu tài khoản 
 * có vai trò là nhân viên hoặc quản lý, hàm sẽ thiết lập ID tương ứng cho 
 * đối tượng nhân viên hoặc quản lý.
 * 
 * @param path Đường dẫn tới file chứa thông tin tài khoản.
 */
void QLKhachSan::inputTaiKhoan(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    int index = 0;
    string line, username, password, ID;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        username = Utils::getSubstringUntilX(line, index, ',');
        password = Utils::getSubstringUntilX(line, index, ',');
        ID       = Utils::getSubstringUntilX(line, index, '\n');
        TaiKhoan newTaiKhoan(ID, username, password);
        QLTK.themTaiKhoan(newTaiKhoan);
        role_value role = newTaiKhoan.getRole();
        if(role == NHANVIEN) {
            nhanVien.setIDNhanVien(ID);
        } 
        else if(role == QUANLI) {
            quanLi.setIDQuanLi(ID);
        }
        index = 0;
    }  
    fi.close();
}

/**
 * @brief Hàm đọc thông tin khách hàng từ file và thêm vào danh sách khách hàng.
 * 
 * Hàm này sẽ mở file tại đường dẫn được cung cấp, đọc từng dòng trong file và 
 * tách thông tin khách hàng (ID, tên, ngày sinh, số điện thoại, giới tính) từ mỗi dòng. 
 * Sau đó, tạo đối tượng KhachHang mới và thêm vào danh sách khách hàng.
 * 
 * @param path Đường dẫn tới file chứa thông tin khách hàng.
 */
void QLKhachSan::inputKhachHang(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    int index = 0;
    string line, ID, name, birthday, phone, gender;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        ID       = Utils::getSubstringUntilX(line, index, ',');
        name     = Utils::getSubstringUntilX(line, index, ',');
        birthday = Utils::getSubstringUntilX(line, index, ',');
        phone    = Utils::getSubstringUntilX(line, index, ',');
        gender   = Utils::getSubstringUntilX(line, index, '\n');
        KhachHang newKhachHang(ID, name, Utils::stringToDate(Utils::trim(birthday)), phone, Utils::stringToGender(gender));
        QLKH.themKhachHang(newKhachHang);
        index = 0;
    }  
    fi.close();
}

/**
 * @brief Hàm đọc thông tin loại phòng từ file và thêm vào danh sách loại phòng.
 * 
 * Hàm này sẽ mở file tại đường dẫn được cung cấp, đọc từng dòng trong file và 
 * tách thông tin loại phòng (mã loại phòng, loại giường, số lượng khách, diện tích,
 * giá phòng, mô tả phòng) từ mỗi dòng. 
 * Sau đó, tạo đối tượng LoaiPhong mới và thêm vào danh sách loại phòng.
 * 
 * @param path Đường dẫn tới file chứa thông tin loại phòng.
 */
void QLKhachSan::inputLoaiPhong(string path) {
    QLLP.AddRangeLoaiPhong(path);
}

/**
 * @brief Hàm đọc thông tin phòng từ file và thêm vào danh sách phòng.
 * 
 * Hàm này sẽ mở file tại đường dẫn được cung cấp, đọc từng dòng trong file và 
 * tách thông tin phòng (mã phòng, mã loại phòng) từ mỗi dòng. 
 * Sau đó, tạo đối tượng Phong mới và thêm vào danh sách phòng.
 * 
 * @param path Đường dẫn tới file chứa thông tin phòng.
 */
void QLKhachSan::inputPhong(string path) {
    //QLP.AddRangePhong(path);
}

/**
 * @brief Hàm đọc thông tin đặt phòng từ file và thêm vào danh sách đặt phòng.
 * 
 * Hàm này sẽ mở file tại đường dẫn được cung cấp, đọc từng dòng trong file và 
 * tách thông tin đặt phòng (mã đặt phòng, mã phòng, ID khách hàng, ngày nhận, 
 * ngày trả, số lượng khách, đơn giá) từ mỗi dòng. 
 * Sau đó, tạo đối tượng DatPhong mới và thêm vào danh sách đặt phòng.
 * 
 * @param path Đường dẫn tới file chứa thông tin đặt phòng.
 */
void QLKhachSan::inputDatPhong(string path) {
    ifstream fi(path);
    if(!fi.is_open()) {
        cout << "Không thể đọc file::" << path << endl;
    }
    string line;
    int index = 0;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        string maDatPhong   = Utils::getSubstringUntilX(line, index, ',');
        string maPhong      = Utils::getSubstringUntilX(line, index, ',');
        string IDKhachHang  = Utils::getSubstringUntilX(line, index, ',');
        string ngayNhan     = Utils::getSubstringUntilX(line, index, ',');
        string ngayTra      = Utils::getSubstringUntilX(line, index, ',');
        string soLuongKhach = Utils::getSubstringUntilX(line, index, ',');
        string donGia       = Utils::getSubstringUntilX(line, index, '\n');
        DatPhong newDatPhong(maDatPhong, maPhong, IDKhachHang, 
        Utils::stringToDate(ngayNhan), Utils::stringToDate(ngayTra), 
        Utils::stringToInt(soLuongKhach), Utils::stringToInt(donGia));
        QLDP.themDatPhong(newDatPhong);
        index = 0;
    }  
    fi.close();
}


void QLKhachSan::outputTaiKhoan(string path) {
    
}

void QLKhachSan::outputKhachHang(string path) {

}

void QLKhachSan::outputLoaiPhong(string path) {

}

void QLKhachSan::outputPhong(string path) {

}

void QLKhachSan::outputDatPhong(string path) {
    

}

void QLKhachSan::work() {
    // cout << "Test Quan Li Khach Hang" << endl;
    // KhachHang *kh = QLKH.timKiemKhachHang("100048");
    // cout << *kh << endl;
    // QLKH.suaThongTin(kh->getIDKhachHang());
    // cout << *kh << endl;
    // cout << "Test Loai Phong" << endl;
    // QLLP.QLChoice();
    gnk_Window_Loop();
}


/**
 * @brief Đăng nhập vào hệ thống.
 * 
 * Hàm này kiểm tra thông tin đăng nhập của người dùng và xác định vai trò của họ trong hệ thống.
 * 
 * @param username Tên đăng nhập của người dùng.
 * @param password Mật khẩu của người dùng.
 * @return NguoiDung* Con trỏ đến đối tượng người dùng nếu đăng nhập thành công, NULL nếu thất bại.
 */
NguoiDung *QLKhachSan::dangNhap(string username, string password) {
    string ID = QLTK.kiemTraTaiKhoan(username, password);
    if(ID != "") {
        if(ID == quanLi.getIDQuanLi()) {
            role = QUANLI;
            return &quanLi;
        }
        if(ID == nhanVien.getIDNhanVien()) {
            role = NHANVIEN;
            return &nhanVien;
        }
        role = KHACHHANG;
        return QLKH.timKiemKhachHang(ID);
    }
    return nullptr;
}

/**
 * @brief Đăng xuất khỏi hệ thống.
 * 
 * Hàm này đặt vai trò của người dùng hiện tại là UNDEFINED_ROLE.
 */
void QLKhachSan::dangXuat() {
    role = UNDEFINED_ROLE;
}

sign_up_return_value QLKhachSan::taoTaiKhoan(string firstName, string surname, string birthday, string gender, string username, string password) {
    if(firstName == "" || surname == "" || birthday == "" || gender == "" || username == "" || password == "") {
        return SIGN_UP_BLANK_INFO;
    }
    LinkedList<TaiKhoan> &DSTK = QLTK.getDanhSachTaiKhoan();
    Node<TaiKhoan> *p = DSTK.begin();
    while(p != DSTK.end()) {
        if(p->data.getUsername() == username) {
            return SIGN_UP_USERNAME_EXISTED;
        }
        p = p->next;
    }
    string ID = QLKH.taoIDKhachHang();
    KhachHang newKhachHang(ID, Utils::trim(firstName) + " " + \
    Utils::trim(surname), Utils::stringToDate(birthday), "",  \
    Utils::stringToGender(gender));
    cout << newKhachHang << endl;
    QLKH.themKhachHang(newKhachHang);
    QLTK.themTaiKhoan(TaiKhoan(ID, username, password));
    return SIGN_UP_SUCCESS;
}

/**
 * @brief Kiểm tra sự sẵn có của phòng trong khoảng thời gian nhất định.
 * 
 * Hàm này duyệt qua danh sách đặt phòng và kiểm tra xem các phòng nào đang được đặt
 * trong khoảng thời gian từ checkInDate đến checkOutDate. Sau đó, in ra danh sách các
 * phòng không có trạng thái bận.
 * 
 * @param checkInDate Ngày nhận phòng.
 * @param checkOutDate Ngày trả phòng.
 */
void QLKhachSan::roomAvailability(time_t checkInDate, time_t checkOutDate) {
    LinkedList<Phong> &DSP = QLP.getDanhSachPhong();
    set<string> maPhongDaDat;
    cout << "check in date: " << Utils::dateToString(checkInDate) << endl;
    cout << "check out date: " << Utils::dateToString(checkOutDate) << endl;
    LinkedList<DatPhong> &DSDP = QLDP.getDanhSachDatPhong();
    Node<DatPhong> *p = DSDP.begin();
    while(p != DSDP.end()) {
        time_t ngayNhan = p->data.getNgayNhan();
        time_t ngayTra = p->data.getNgayTra();        
        if(!(ngayTra < checkInDate || checkOutDate < ngayNhan)) {
            cout << Utils::dateToString(ngayNhan) << " " << Utils::dateToString(ngayTra) << endl;
            maPhongDaDat.insert(p->data.getMaPhong());
        }        
        p = p->next;
    }

    Node<Phong> *p2 = DSP.begin();
    while(p2 != DSP.end()) {
        string maPhong = p2->data.getMaPhong();
        for(string i:maPhongDaDat) {
            cout << i << endl;
            if(maPhong == i) {
                p2 = p2->next;
                continue;
            }
        }
        p2->data.thongTinPhong();
        p2 = p2->next;
    }
}
