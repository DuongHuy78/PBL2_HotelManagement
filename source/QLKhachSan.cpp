#include "./header/QLKhachSan.h"

stringstream UI_input_buffer("");
stringstream UI_output_buffer("");
IO_MODE current_mode;
bool UI_enable = false;

/**
 * @brief Hàm khởi tạo của lớp QLKhachSan.
 * 
 * Hàm này khởi tạo đối tượng QLKhachSan, gọi hàm UI_init() để khởi tạo giao diện người dùng
 * và gán con trỏ current_Data trỏ đến đối tượng hiện tại.
 */
QLKhachSan::QLKhachSan() {
    cout << "Ban co muon su dung giao dien do hoa khong? (Y/N): ";
    string choice;
    cin >> choice;
    // cin.ignore();
    if(choice == "Y") {
        UI_enable = true;
        current_mode = UI_STREAM;
        UI_init();
        current_Data = this;
    }
    else {
        current_mode = CONSOLE;
    }
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
        cerr << "Khong the doc file::" << path << endl;
    }
    int count = 0;
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
        ++count;
    }  
    fi.close();
    cout << "Da nhap du lieu cua " << count << " tai khoan tu file: " << path << endl;
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
        cerr << "Khong the doc file::" << path << endl;
    }
    int count = 0;
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
        ++count;
    }  
    fi.close();
    cout << "Da nhap du lieu cua " << count << " khach hang tu file: " << path << endl;
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
    ifstream fi(path);
    if(!fi.is_open()) {
        cerr << "Khong the doc file::" << path << endl;
    }
    int count = 0;
    int index = 0;
    string line, maLoaiPhong, loaiGiuong, soLuongKhach, dienTich, giaPhong, moTaPhong;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        maLoaiPhong = Utils::getSubstringUntilX(line, index, ';');
        loaiGiuong  = Utils::getSubstringUntilX(line, index, ';');
        soLuongKhach = Utils::getSubstringUntilX(line, index, ';');
        dienTich    = Utils::getSubstringUntilX(line, index, ';');
        giaPhong    = Utils::getSubstringUntilX(line, index, ';');
        moTaPhong   = Utils::getSubstringUntilX(line, index, '\n');
        LoaiPhong newLoaiPhong(maLoaiPhong, Utils::stringToInt(loaiGiuong), Utils::stringToInt(soLuongKhach), Utils::stringToInt(dienTich), Utils::stringToInt(giaPhong), moTaPhong);
        QLLP.themLoaiPhong(newLoaiPhong);
        index = 0;
        ++count;
    }  
    fi.close();
    cout << "Da nhap du lieu cua " << count << " loai phong tu file: " << path << endl;
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
    ifstream fi(path);
    if(!fi.is_open()) {
        cerr << "Khong the doc file::" << path << endl;
    }
    int count = 0;
    int index = 0;
    string line, maPhong, maLoaiPhong;
    while(!fi.eof()) {
        getline(fi, line);
        if(line == "") break;
        maPhong     = Utils::getSubstringUntilX(line, index, ';');
        maLoaiPhong = Utils::getSubstringUntilX(line, index, '\n');
        Phong newPhong(maPhong, maLoaiPhong);
        //cout << count << " " << newPhong;
        QLP.themPhong(newPhong);
        index = 0;
        ++count;
    }  
    fi.close();
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
        cerr << "Khong the doc file::" << path << endl;
    }
    int count = 0;
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
        ++count;
    }  
    fi.close();
    cout << "Da nhap du lieu cua " << count << " dat phong tu file: " << path << endl;
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
    system("cls");
    nhanVien.setDSKH(&QLKH);
    nhanVien.setDSDP(&QLDP);
    quanLi.setDSLP(&QLLP);
    quanLi.setDSP(&QLP);
    quanLi.setDSDP(&QLDP);
    QLDP.setDSKH(&QLKH);
    QLDP.setDSLP(&QLLP);
    QLDP.setDSP(&QLP);
    QLP.setQLLP(&QLLP);
    if(UI_enable) {
        gnk_Window_Loop();
    }
    else {
        while(true) {
            system("cls");
            if(role == UNDEFINED_ROLE) {
                cout << "Dang nhap de tiep tuc: " << endl;
                while(!dangNhap()) {
                    cout << "Dang nhap that bai. Vui long thu lai." << endl;               
                }
                QLDP.setcurrentID(this->currentID);
                QLDP.setRole(role);
            }
            else {
                int choice = current_user->work();
                if(choice == SIGN_OUT) {
                    dangXuat();
                }
                else if(choice == USER_BOOK_ROOM) {
                    bookingRoom();
                    cout << QLDP;
                    system("pause");
                }
            }
        }
    }
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
bool QLKhachSan::dangNhap() {
    string username, password;
    Utils::outputData("Username: ", CONSOLE);
    Utils::inputData(username, CONSOLE_OR_UI);
    Utils::outputData("Password: ", CONSOLE);
    Utils::inputData(password, CONSOLE_OR_UI);
    string ID = QLTK.kiemTraTaiKhoan(username, password);
    if(ID != "") {
        if(ID == quanLi.getIDQuanLi()) {
            role = QUANLI;
            current_user = &quanLi;
            return true;
        }
        if(ID == nhanVien.getIDNhanVien()) {
            role = NHANVIEN;
            current_user = &nhanVien;
            return true;
        }
        role = KHACHHANG;
        if(QLKH.timKiemKhachHang(ID) != nullptr) {
            // QLDP.setcurrentID(this->currentID);
            QLDP.setRole(role);
            current_user = QLKH.timKiemKhachHang(ID);
            return true;
        }
    }
    return false;
}

/**
 * @brief Đăng xuất khỏi hệ thống.
 * 
 * Hàm này đặt vai trò của người dùng hiện tại là UNDEFINED_ROLE.
 */
void QLKhachSan::dangXuat() {
    role = UNDEFINED_ROLE;
    current_user = nullptr;
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
void QLKhachSan::roomAvailability(time_t checkInDate, time_t checkOutDate, 
int soLuongKhach, LinkedList<Phong *> &phongTrong) {
    LinkedList<string> IDPhongDaDat;
    Node<DatPhong> *p = QLDP.getDanhSachDatPhong().begin();
    while(p != QLDP.getDanhSachDatPhong().end()) {
        time_t ngayNhan = p->data.getNgayNhan();
        time_t ngayTra = p->data.getNgayTra();
        if(!(ngayTra < checkInDate || checkOutDate < ngayNhan )) {
            IDPhongDaDat.add(p->data.getMaPhong());
        }        
        p = p->next;
    }

    Node<Phong> *p2 = QLP.getDanhSachPhong().begin();
    while(p2 != QLP.getDanhSachPhong().end()) {
        string maPhong = p2->data.getMaPhong();
        bool isAvailable = true;
        Node<string> *p3 = IDPhongDaDat.begin();
        while(p3 != IDPhongDaDat.end()) {
            if(p3->data == maPhong) {
                isAvailable = false;
                break;
            }
            p3 = p3->next;
        }

        if(isAvailable && QLLP.soLuongKhach(p2->data.getLoaiPhong()) >= soLuongKhach) {
            phongTrong.add(&p2->data);
        }
        p2 = p2->next;
    }
}

void QLKhachSan::bookingRoom() {
    string ngayNhan, ngayTra;
    while(true) {
        ngayNhan = Utils::inputWithCondition("Nhap ngay nhan(dd/mm/yyyy): ", 1, 10, DATE);
        ngayTra = Utils::inputWithCondition("Nhap ngay tra(dd/mm/yyyy): ", 1, 10, DATE);
        if(Utils::stringToDate(ngayNhan) < time(0)) {
            Utils::outputData("Ngay nhan phai lon hon ngay hien tai!\n", CONSOLE_OR_UI);
            continue;
        }
        if(Utils::stringToDate(ngayTra) < Utils::stringToDate(ngayNhan)) {
            Utils::outputData("Ngay tra phai lon hon ngay nhan!\n", CONSOLE_OR_UI);
            continue;
        }
        break;
    }
    
    string soLuongKhach;
    soLuongKhach = Utils::inputWithCondition("Nhap so luong khach: ", 1, 2, NUMBER_ONLY);
    LinkedList<Phong *> phongTrong;
    roomAvailability(Utils::stringToDate(ngayNhan), Utils::stringToDate(ngayTra), Utils::stringToInt(soLuongKhach), phongTrong);
    string maPhong;
    string loaiPhong;
    bool roomNotFound = true;
    while(roomNotFound) {
        int count = 0;
        cout << "Danh sach phong trong: " << endl;
        Node<Phong *> *p = phongTrong.begin();
        while(p != phongTrong.end()) {
            cout << *p->data;
            ++count;
            p = p->next;
        }
        if(count == 0) {
            Utils::outputData("Khong co phong trong cho thoi gian nay!\n", CONSOLE_OR_UI);
            return;
        }
        maPhong = Utils::inputWithCondition("Nhap ma phong: ", 3, 7, ALPHABET_AND_NUMBER_ONLY);
        p = phongTrong.begin();
        while(p != phongTrong.end()) {
            if(p->data->getMaPhong() == maPhong) {
                roomNotFound = false;
                loaiPhong = p->data->getLoaiPhong();
                break;
            }
            p = p->next;
        }
    }
    int donGia = QLLP.getGiaPhong(loaiPhong);
    if(role == NHANVIEN) {
        KhachHang KH = QLKH.nhapThongTin();
        QLKH.themKhachHang(KH);
        DatPhong newDP(QLDP.taoMaDatPhong(), maPhong, KH.getIDKhachHang(), Utils::stringToDate(ngayNhan), Utils::stringToDate(ngayTra), Utils::stringToInt(soLuongKhach), donGia);
        QLDP.themDatPhong(newDP);
    }
    else if(role == KHACHHANG) {
        KhachHang *KH = (KhachHang *)current_user;
        DatPhong newDP(QLDP.taoMaDatPhong(), maPhong, KH->getIDKhachHang(), Utils::stringToDate(ngayNhan), Utils::stringToDate(ngayTra), Utils::stringToInt(soLuongKhach), donGia);
        QLDP.themDatPhong(newDP);
    }
}
