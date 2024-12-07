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
    cin.ignore();
    if(choice == "Y") {
        UI_enable = true;
        current_mode = UI_STREAM;
        current_Data = this;
    }
    else {
        current_mode = CONSOLE;
    }
}

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
        username = Utils::getSubstringUntilX(line, index, ';');
        password = Utils::getSubstringUntilX(line, index, ';');
        ID       = Utils::getSubstringUntilX(line, index, '\n');
        TaiKhoan *newTaiKhoan = new TaiKhoan(ID, username, password);
        QLTK.themTaiKhoan(newTaiKhoan);
        // add relationship
        Node<KhachHang *> *kh = QLKH.getDSKH().begin();
        while(kh != QLKH.getDSKH().end()) {
            if(kh->data->getIDKhachHang() == ID) {
                newTaiKhoan->setNguoiDung(kh->data);
                break;
            }
            kh = kh->next;
        }
        role_value role = newTaiKhoan->getRole();
        if(role == NHANVIEN) {
            nhanVien.setIDNhanVien(ID);
            QLTK.getDSTK().last()->data->setNguoiDung(&nhanVien);
        } 
        else if(role == QUANLI) {
            quanLi.setIDQuanLi(ID);
            QLTK.getDSTK().last()->data->setNguoiDung(&quanLi);
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
        ID       = Utils::getSubstringUntilX(line, index, ';');
        name     = Utils::getSubstringUntilX(line, index, ';');
        birthday = Utils::getSubstringUntilX(line, index, ';');
        phone    = Utils::getSubstringUntilX(line, index, ';');
        gender   = Utils::getSubstringUntilX(line, index, '\n');
        KhachHang *newKhachHang = new KhachHang(ID, name, Utils::stringToDate(Utils::trim(birthday)), phone, Utils::stringToGender(gender));
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
        maLoaiPhong     = Utils::getSubstringUntilX(line, index, ';');
        loaiGiuong      = Utils::getSubstringUntilX(line, index, ';');
        soLuongKhach    = Utils::getSubstringUntilX(line, index, ';');
        dienTich        = Utils::getSubstringUntilX(line, index, ';');
        giaPhong        = Utils::getSubstringUntilX(line, index, ';');
        moTaPhong       = Utils::getSubstringUntilX(line, index, '\n');
        LoaiPhong *newLoaiPhong = new LoaiPhong(maLoaiPhong, 
            Utils::stringToInt(loaiGiuong), 
            Utils::stringToInt(soLuongKhach), 
            Utils::stringToInt(dienTich), 
            Utils::stringToInt(giaPhong), 
            moTaPhong);
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
        Phong *newPhong = new Phong(maPhong);
        QLP.themPhong(newPhong);
        Node<LoaiPhong *> *lp = QLLP.getDSLP().begin();
        while(lp != QLLP.getDSLP().end()) {
            if(lp->data->getLoaiPhong() == maLoaiPhong) {
                newPhong->setLoaiPhong(lp->data);
                break;
            }
            lp = lp->next;
        }
        index = 0;
        ++count;
    }  
    cout << "Da nhap du lieu cua " << count << " phong tu file: " << path << endl;
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
        string maDatPhong   = Utils::getSubstringUntilX(line, index, ';');
        string maPhong      = Utils::getSubstringUntilX(line, index, ';');
        string IDKhachHang  = Utils::getSubstringUntilX(line, index, ';');
        string ngayNhan     = Utils::getSubstringUntilX(line, index, ';');
        string ngayTra      = Utils::getSubstringUntilX(line, index, ';');
        string soLuongKhach = Utils::getSubstringUntilX(line, index, ';');
        string donGia       = Utils::getSubstringUntilX(line, index, '\n');
        DatPhong *newDatPhong = new DatPhong(
            maDatPhong,
            Utils::stringToDate(ngayNhan), 
            Utils::stringToDate(ngayTra), 
            Utils::stringToInt(soLuongKhach), 
            Utils::stringToInt(donGia)
        );
        QLDP.themDatPhong(newDatPhong);
        Node<Phong *> *p = QLP.getDSP().begin();
        while(p != QLP.getDSP().end()) {
            if(p->data->getMaPhong() == maPhong) {
                newDatPhong->setPhong(p->data);
                break;
            }
            p = p->next;
        }
        Node<KhachHang *> *kh = QLKH.getDSKH().begin();
        while(kh != QLKH.getDSKH().end()) {
            if(kh->data->getIDKhachHang() == IDKhachHang) {
                newDatPhong->setKhachHang(kh->data);
                break;
            }
            kh = kh->next;
        }

        index = 0;
        ++count;
    }  
    fi.close();
    cout << "Da nhap du lieu cua " << count << " dat phong tu file: " << path << endl;
}

void QLKhachSan::outputTaiKhoan(string path) {
    ofstream fo(path);
    if(!fo.is_open()) {
        cerr << "Khong the mo file::" << path << endl;
    }
    int count = 0;
    Node<TaiKhoan *> *temp = QLTK.getDSTK().begin();
    while(temp != QLTK.getDSTK().end()) {
        fo << temp->data->getUsername() << ";" 
        << temp->data->getPassword() << ";" 
        << temp->data->getID() << endl;
        temp = temp->next;
        count++;
    }
    fo.close();
    cout << "Da xuat du lieu cua " << count << " tai khoan ra file: " << path << endl;
}

void QLKhachSan::outputKhachHang(string path) {
    ofstream fo(path);
    if(!fo.is_open()) {
        cerr << "Khong the mo file::" << path << endl;
    }
    int count = 0;
    Node<KhachHang *> *temp = QLKH.getDSKH().begin();
    while(temp != QLKH.getDSKH().end()) {
        fo << temp->data->getIDKhachHang() << ";" 
            << temp->data->getHoTen() << ";" 
            << Utils::dateToString(temp->data->getNgaySinh()) << ";" 
            << temp->data->getSoDienThoai() << ";" 
            << Utils::genderToString(temp->data->getGioiTinh()) 
            << endl;
        temp = temp->next;
        count++;
    }
    fo.close();
    cout << "Da xuat du lieu cua " << count << " khach hang ra file: " << path << endl;
}

void QLKhachSan::outputLoaiPhong(string path) {
    ofstream fo(path);
    if(!fo.is_open()) {
        cerr << "Khong the mo file::" << path << endl;
    }
    int count = 0;
    Node<LoaiPhong *> *temp = QLLP.getDSLP().begin();
    while(temp != QLLP.getDSLP().end()) {
        fo << temp->data->getLoaiPhong() << ";" 
            << temp->data->getLoaiGiuong() << ";" 
            << temp->data->getSoLuongKhach() << ";" 
            << temp->data->getDienTich() << ";" 
            << temp->data->getGiaPhong() << ";" 
            << temp->data->getMoTaPhong() 
            << endl;
        temp = temp->next;
        count++;
    }
    fo.close();
    cout << "Da xuat du lieu cua " << count << " loai phong ra file: " << path << endl;
}

void QLKhachSan::outputPhong(string path) {
    ofstream fo(path);
    if(!fo.is_open()) {
        cerr << "Khong the mo file::" << path << endl;
    }
    int count = 0;
    Node<Phong *> *temp = QLP.getDSP().begin();
    while(temp != QLP.getDSP().end()) {
        fo << temp->data->getMaPhong() << ";" 
            << temp->data->getLoaiPhong() 
            << endl;
        temp = temp->next;
        count++;
    }
    fo.close();
    cout << "Da xuat du lieu cua " << count << " phong ra file: " << path << endl;
}

void QLKhachSan::outputDatPhong(string path) {
    ofstream fo(path);
    if(!fo.is_open()) {
        cerr << "Khong the mo file::" << path << endl;
    }
    int count = 0;
    Node<DatPhong *> *temp = QLDP.getDSDP().begin();
    while(temp != QLDP.getDSDP().end()) {
        fo << temp->data->getMaDatPhong() << ";" 
            << temp->data->getPhong()->getMaPhong() << ";" 
            << temp->data->getKhachHang()->getIDKhachHang() << ";" 
            << Utils::dateToString(temp->data->getNgayNhan()) << ";" 
            << Utils::dateToString(temp->data->getNgayTra()) << ";" 
            << temp->data->getSoLuongKhach() << ";" 
            << temp->data->getDonGia() 
            << endl;
        temp = temp->next;
        count++;
    }
    fo.close();
    cout << "Da xuat du lieu cua " << count << " dat phong ra file: " << path << endl;
}

void QLKhachSan::work() {
    system("cls");
    // quanLi.setDSLP(&QLLP);
    // quanLi.setDSP(&QLP);
    // quanLi.setDSDP(&QLDP);
    // QLDP.setDSKH(&QLKH);
    // QLDP.setDSLP(&QLLP);
    // QLDP.setDSP(&QLP);
    // QLP.setQLLP(&QLLP);
    if(UI_enable) {
        gnk_Window_Loop();
    }
    else {
        while(true) {
            system("cls");
            if(role == UNDEFINED_ROLE) {
                string choice_str;
                Utils::outputData("----------------LUA-CHON---------------\n", CONSOLE);
                Utils::outputData("1. Dang nhap\n", CONSOLE);
                Utils::outputData("2. Dang ky\n", CONSOLE);
                Utils::outputData("3. Thoat\n", CONSOLE);
                Utils::outputData("---------------------------------------\n", CONSOLE);
                choice_str = Utils::inputWithCondition("Nhap lua chon cua ban: ", 1, 2, NUMBER_ONLY);
                int choice = Utils::stringToInt(choice_str);
                if(choice == 1) {
                    Utils::outputData("---------------DANG-NHAP---------------\n", CONSOLE);
                    while(!dangNhap()) {
                        Utils::outputData("Dang nhap that bai. Vui long thu lai.\n", CONSOLE);           
                    }
                }
                else if(choice == 2) {
                    Utils::outputData("---------------DANG-KY---------------\n", CONSOLE);
                    string firstName, surname, birthday, gender, username, password;
                    firstName = Utils::inputWithCondition("Nhap ho: ", 1, MAX_NAME, ALPHABET_AND_SPACE_ONLY);
                    surname = Utils::inputWithCondition("Nhap ten: ", 1, MAX_NAME, ALPHABET_AND_SPACE_ONLY);
                    birthday = Utils::inputWithCondition("Nhap ngay sinh (dd/mm/yyyy): ", 1, 10, DATE);
                    gender = Utils::inputWithCondition("Nhap gioi tinh (Nam/Nu): ", 1, 3, GENDER);
                    username = Utils::inputWithCondition("Nhap ten dang nhap: ", 1, 35, ALPHABET_AND_NUMBER_ONLY);
                    password = Utils::inputWithCondition("Nhap mat khau: ", 1, 35, ALPHABET_AND_NUMBER_ONLY);
                    sign_up_return_value result = taoTaiKhoan(firstName, surname, birthday, gender, username, password);
                    if(result == SIGN_UP_USERNAME_EXISTED) {
                        Utils::outputData("Ten dang nhap da ton tai!\n", CONSOLE);
                    }
                    else if(result == SIGN_UP_SUCCESS) {
                        Utils::outputData("Dang ky thanh cong!\n", CONSOLE);
                    }
                }
                else if(choice == 3) {
                    Utils::outputData("Cam on ban da su dung dich vu!\n", CONSOLE);
                    Utils::pauseConsole();
                    return;
                }
            }
            else {
                user_option_value choice = current_user->work();
                requestHandling(choice);
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
    Node<TaiKhoan *> *p = QLTK.getDSTK().begin();
    while(p != QLTK.getDSTK().end()) {
        if(p->data->getUsername() == username) {
            return SIGN_UP_USERNAME_EXISTED;
        }
        p = p->next;
    }
    string ID = QLKH.taoIDKhachHang();
    KhachHang *newKhachHang = new KhachHang(ID, Utils::trim(firstName) + " " + \
    Utils::trim(surname), Utils::stringToDate(birthday), "",  \
    Utils::stringToGender(gender));
    QLKH.themKhachHang(newKhachHang);
    TaiKhoan *newTaiKhoan = new TaiKhoan(ID, username, password);
    QLTK.themTaiKhoan(newTaiKhoan);
    return SIGN_UP_SUCCESS;
}

void QLKhachSan::requestHandling(user_option_value choice) {
    if(choice == CONTINUE) {
        return;
    }
    else if(choice == SIGN_OUT) {
        dangXuat();
    }
    else if(choice == USER_BOOK_ROOM) {
        system("cls");
        string ngayNhan, ngayTra, soLuongKhach;
        LinkedList<Phong *> phongTrong;
        LinkedList<loaiPhongAvailable> listlpa;

        searchTypeRoom(ngayNhan, ngayTra, soLuongKhach, phongTrong, listlpa);
        bookingRoom(ngayNhan, ngayTra, soLuongKhach, phongTrong, listlpa);
        Utils::outputData("Dat phong thanh cong!\n", CONSOLE);
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSKH) {
        cout << QLKH;
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSDP) {
        cout << QLDP;
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSLP) {
        cout << QLLP;
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSP) {
        cout << QLP;
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSKH_ID) {
        string ID = Utils::inputWithCondition("Nhap ID khach hang: ", 1, 10, ALPHABET_AND_NUMBER_ONLY);
        KhachHang *kh = QLKH.timKiemKhachHang(ID);
        if(kh != nullptr) {
            cout << *kh;
        }
        else {
            Utils::outputData("Khong tim thay khach hang!\n", CONSOLE);
        }
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSDP_ID) {
        string ID = Utils::inputWithCondition("Nhap ID dat phong: ", 1, 10, ALPHABET_AND_NUMBER_ONLY);
        DatPhong *dp = QLDP.timKiemDatPhong(ID);
        if(dp != nullptr) {
            cout << *dp;
        }
        else {
            Utils::outputData("Khong tim thay dat phong!\n", CONSOLE);
        }
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSKH_SDT) {
        string SDT = Utils::inputWithCondition("Nhap so dien thoai khach hang: ", 1, 10, VIETNAM_PHONE_NUMBER);
        KhachHang *kh = QLKH.timKiemKhachHangSDT(SDT);
        if(kh != nullptr) {
            cout << *kh;
        }
        else {
            Utils::outputData("Khong tim thay khach hang!\n", CONSOLE);
        }
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSP_ID) {
        string ID = Utils::inputWithCondition("Nhap ID phong: ", 1, 10, ALPHABET_AND_NUMBER_ONLY);
        Phong *p = QLP.timPhong(ID);
        if(p != nullptr) {
            cout << *p;
            Node<DatPhong *> *dp = QLDP.getDSDP().begin();
            while(dp != QLDP.getDSDP().end()) {
                if(dp->data->getPhong()->getMaPhong() == ID) {
                    if(dp->data->getNgayNhan() > time(0) && dp->data->getNgayTra() < time(0)) {
                        cout << dp->data;
                    }
                }
                dp = dp->next;
            }
        }
        Utils::pauseConsole();
    }
    else if(choice == PRINT_DSP_LOAIPHONG) {
        string loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, 7, ALPHABET_AND_NUMBER_ONLY);
        LoaiPhong *lp = QLLP.timLoaiPhong(loaiPhong);
        if(lp == nullptr) {
            Utils::outputData("Khong tim thay loai phong!\n", CONSOLE);
            Utils::pauseConsole();
            return;
        }
        Node<Phong *> *p = QLP.getDSP().begin();
        while(p != QLP.getDSP().end()) {
            if(p->data->getLoaiPhong()->getLoaiPhong() != loaiPhong) {
                p = p->next;
                continue;
            }
            cout << p->data;
            Node<DatPhong *> *dp = QLDP.getDSDP().begin();
            while(dp != QLDP.getDSDP().end()) {
                if(dp->data->getPhong()->getMaPhong() == p->data->getMaPhong()) {
                    if(dp->data->getNgayNhan() > time(0) && dp->data->getNgayTra() < time(0)) {
                        cout << dp->data;
                    }
                }
                dp = dp->next;
            }
            p = p->next;
        }
        Utils::pauseConsole();
    }
    else if(choice == ADD_KHACHHANG) {
        KhachHang *newKhachHang = new KhachHang(QLKH.nhapThongTin());
        QLKH.themKhachHang(newKhachHang);
        Utils::pauseConsole();
    }
    else if(choice == USER_BOOK_ROOM_HISTORY) {
        system("cls");
        KhachHang *KH = (KhachHang *)current_user;
        string ID = KH->getIDKhachHang();
        Node<DatPhong *> *dp = QLDP.getDSDP().begin();
        while(dp != QLDP.getDSDP().end()) {
            if(dp->data->getKhachHang()->getIDKhachHang() == ID) {
                Utils::outputData("-----------LICH-SU-DAT-PHONG---------\n", CONSOLE);
                Utils::outputData("Ma Dat Phong: ", CONSOLE);
                Utils::outputData(dp->data->getMaDatPhong() + "\n", CONSOLE_OR_UI);
                Node<Phong *> *p = QLP.getDSP().begin();
                while(p != QLP.getDSP().end()) {
                    if(p->data->getMaPhong() == dp->data->getPhong()->getMaPhong()) {
                        Utils::outputData("Loai phong: ", CONSOLE);
                        Utils::outputData(p->data->getLoaiPhong()->getLoaiPhong() + "\n", CONSOLE_OR_UI);
                    }
                    p = p->next;
                }
                Utils::outputData("Ma Phong: ", CONSOLE);
                Utils::outputData(dp->data->getPhong()->getMaPhong() + "\n", CONSOLE_OR_UI);
                Utils::outputData("Ngay Nhan: ", CONSOLE);
                Utils::outputData(Utils::dateToString(dp->data->getNgayNhan()) + "\n", CONSOLE_OR_UI);
                Utils::outputData("Ngay Tra: ", CONSOLE);
                Utils::outputData(Utils::dateToString(dp->data->getNgayTra()) + "\n", CONSOLE_OR_UI);
                Utils::outputData("So Luong Khach: ", CONSOLE);
                Utils::outputData(Utils::intToString(dp->data->getSoLuongKhach()) + "\n", CONSOLE_OR_UI);
                Utils::outputData("Gia Phong: ", CONSOLE);
                Utils::outputData(Utils::chuanHoaSo(Utils::intToString(dp->data->getDonGia())) + " VND\n", CONSOLE_OR_UI);
                Utils::outputData("Tong Tien: ", CONSOLE);
                Utils::outputData(Utils::chuanHoaSo(Utils::intToString(dp->data->tongTien())) + " VND\n", CONSOLE_OR_UI);
                Utils::outputData("-------------------------------------\n", CONSOLE);
            }
            dp = dp->next;
        }
        Utils::pauseConsole();
    }
    else if(choice == ADD_PHONG){
        Phong *newPhong = new Phong(QLP.nhapThongTin());
        QLP.themPhong(newPhong);
        Utils::outputData("Tao phong " + newPhong->getMaPhong() + " thanh cong!\n", CONSOLE);
        Utils::pauseConsole();
    }
    else if(choice == UPDATE_PHONG){
        string loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
        Phong *P = QLP.timPhong(loaiPhong);
        if(P == nullptr) {
            Utils::outputData("Khong tim thay phong" + loaiPhong + "!\n", CONSOLE);
            Utils::pauseConsole();
            return;
        }
        else{
            P->capNhatThongTin();
        }
    }
    else if(choice == DELETE_PHONG){
        string loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
        Phong *P = QLP.timPhong(loaiPhong);
        if(P == nullptr) {
            Utils::outputData("Khong tim thay phong!\n", CONSOLE);
            Utils::pauseConsole();
            return;
        }
        else{
            QLP.xoaPhong(loaiPhong);
        }
    }
    else if(choice == ADD_LOAI_PHONG) {
        LoaiPhong *newLP = new LoaiPhong(LoaiPhong::nhapThongTin());
        Node<LoaiPhong *> *p = QLLP.getDSLP().begin();
        while(p != QLLP.getDSLP().end()) {
            if(p->data->getLoaiPhong() == newLP->getLoaiPhong()) {
                Utils::outputData("Loai phong da ton tai!\n", CONSOLE);
                Utils::pauseConsole();
                return;
            }
            p = p->next;
        }
        QLLP.themLoaiPhong(newLP);
    }
    else if(choice == UPDATE_LOAIPHONG){
        string loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
        LoaiPhong *LP = QLLP.timLoaiPhong(loaiPhong);
        if(LP == nullptr) {
            Utils::outputData("Khong tim thay loai phong!\n", CONSOLE);
            Utils::pauseConsole();
            return;
        }
        else{
            LP->capNhatThongTin();
            system("cls");
            Utils::outputData("Loai phong da duoc cap nhat!\n", CONSOLE);
            Utils::pauseConsole();
        }
    }
    else if(choice == DELETE_LOAIPHONG){
        string loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
        LoaiPhong *LP = QLLP.timLoaiPhong(loaiPhong);
        if(LP == nullptr) {
            Utils::outputData("Khong tim thay loai phong!\n", CONSOLE);
            Utils::pauseConsole();
            return;
        }
        else{
            QLLP.xoaLoaiPhong(loaiPhong);
        }
    }
    else if(choice == PRINT_KHACHHANG) {
        KhachHang *kh = (KhachHang *)current_user;
        cout << *kh;
    }
    else if(choice == CHANGE_PROFILE) {
        KhachHang *kh = (KhachHang *)current_user;
        kh->suaThongTin();
        Utils::pauseConsole();
    }
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
void QLKhachSan::roomAvailability(time_t checkInDate, time_t checkOutDate, int soLuongKhach, LinkedList<Phong *> &phongTrong) {
    LinkedList<string> IDPhongDaDat;
    Node<DatPhong *> *p = QLDP.getDSDP().begin();
    while(p != QLDP.getDSDP().end()) {
        time_t ngayNhan = p->data->getNgayNhan();
        time_t ngayTra = p->data->getNgayTra();
        if(!(ngayTra < checkInDate || checkOutDate < ngayNhan )) {
            IDPhongDaDat.add(p->data->getPhong()->getMaPhong());
        }        
        p = p->next;
    }

    Node<Phong *> *p2 = QLP.getDSP().begin();
    while(p2 != QLP.getDSP().end()) {
        string maPhong = p2->data->getMaPhong();
        bool isAvailable = true;
        Node<string> *p3 = IDPhongDaDat.begin();
        while(p3 != IDPhongDaDat.end()) {
            if(p3->data == maPhong) {
                isAvailable = false;
                break;
            }
            p3 = p3->next;
        }

        if(isAvailable && QLLP.soLuongKhach(p2->data->getLoaiPhong()->getLoaiPhong()) >= soLuongKhach) {
            phongTrong.add(p2->data);
        }
        p2 = p2->next;
    }
}

void QLKhachSan::searchTypeRoom(string &ngayNhan, string &ngayTra, string &soLuongKhach, LinkedList<Phong *> &phongTrong, LinkedList<loaiPhongAvailable> &listlpa) {
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

    soLuongKhach = Utils::inputWithCondition("Nhap so luong khach: ", 1, 2, NUMBER_ONLY);
    roomAvailability(Utils::stringToDate(ngayNhan), Utils::stringToDate(ngayTra), Utils::stringToInt(soLuongKhach), phongTrong);

    Node<Phong *> *p = phongTrong.begin();
    while(p != phongTrong.end()) {
        bool found = false;
        Node<loaiPhongAvailable> *lpa = listlpa.begin();
        while(lpa != listlpa.end()) {
            if(lpa->data.loaiphong->getLoaiPhong() == p->data->getLoaiPhong()->getLoaiPhong()) {
                lpa->data.amount++;
                found = true;
                break;
            }
            lpa = lpa->next;
        }
        if(!found) {
            loaiPhongAvailable newlpa;
            newlpa.loaiphong = QLLP.timLoaiPhong(p->data->getLoaiPhong()->getLoaiPhong());
            newlpa.amount = 1;
            listlpa.add(newlpa);
        }
        p = p->next;
    }
}

void QLKhachSan::bookingRoom(const string &ngayNhan, const string &ngayTra, const string &soLuongKhach, LinkedList<Phong *> &phongTrong, LinkedList<loaiPhongAvailable> &listlpa) {
    string maPhong;
    string loaiPhong;
    bool typeRoomNotFound = true;
    while(typeRoomNotFound) {
        system("cls");
        int count = 0;
        Utils::outputData("Danh sach loai phong co the dat:\n", CONSOLE);
        Node<loaiPhongAvailable> *lpa = listlpa.begin();
        while(lpa != listlpa.end()) {
            cout << *(lpa->data.loaiphong);
            Utils::outputData("So luong phong trong: ", CONSOLE);
            Utils::outputData(lpa->data.amount, CONSOLE);
            Utils::outputData("\n\n", CONSOLE);
            ++count;
            lpa = lpa->next;
        }
        if(count == 0) {
            Utils::outputData("Khong co loai phong nao phu hop!\n", CONSOLE);
            Utils::pauseConsole();
            return;
        }
        loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, 7, ALPHABET_AND_NUMBER_ONLY);
        lpa = listlpa.begin();
        while(lpa != listlpa.end()) {
            if(lpa->data.loaiphong->getLoaiPhong() == loaiPhong) {
                typeRoomNotFound = false;
                break;
            }
            lpa = lpa->next;
        }
        if(typeRoomNotFound) {
            Utils::outputData("Loai phong ban nhap khong nam trong danh sach!\n", CONSOLE);
            Utils::pauseConsole();
        }
    }

    bool roomNotFound = true;
    while(roomNotFound) {
        system("cls");
        cout << *(QLLP.timLoaiPhong(loaiPhong));
        Utils::outputData("Danh sach phong:\n", CONSOLE);
        Node<Phong *> *p = phongTrong.begin();
        while(p != phongTrong.end()) {
            if(p->data->getLoaiPhong()->getLoaiPhong() == loaiPhong) {
                Utils::outputData(p->data->getMaPhong() + "\n", CONSOLE);
            }
            p = p->next;
        }
        maPhong = Utils::inputWithCondition("Nhap ma phong: ", 3, 7, ALPHABET_AND_NUMBER_ONLY);
        p = phongTrong.begin();
        while(p != phongTrong.end()) {
            if(p->data->getMaPhong() == maPhong && p->data->getLoaiPhong()->getLoaiPhong() == loaiPhong) {
                roomNotFound = false;
                maPhong = p->data->getMaPhong();
                break;
            }
            p = p->next;
        }
        if(roomNotFound) {
            Utils::outputData("Phong ban nhap khong nam trong danh sach!\n", CONSOLE);
            Utils::pauseConsole();
        }
    }

    if(role == NHANVIEN) {
        string ID, temp;
        while(1) {
            Utils::outputData("1. Khach hang da co tai khoan \n", CONSOLE);
            Utils::outputData("2. Khach hang chua co tai khoan \n", CONSOLE);
            temp = Utils::inputWithCondition("Nhap lua chon: ", 1, 1, NUMBER_ONLY);
            if(temp == "1") {
                ID = Utils::inputWithCondition("Nhap ID cua KHACH HANG: ", SIZE_ID_USER - 1 , SIZE_ID_USER ,NUMBER_ONLY);
                KhachHang *p = QLKH.timKiemKhachHang(ID);
                if(p == nullptr) {
                    Utils::outputData("Khong ton tai ID khach hang!", CONSOLE);
                    Utils::pauseConsole();
                    continue;
                }
                break;
            }
            else if(temp == "2") {
                KhachHang *KH = new KhachHang(QLKH.nhapThongTin());
                QLKH.themKhachHang(KH);
                ID = KH->getIDKhachHang();
                break;
            }
            system("cls");
            Utils::outputData("Da co sai sot vui long nhap lai!",CONSOLE);
        }
        DatPhong *newDP = new DatPhong(
            QLDP.taoMaDatPhong(), 
            Utils::stringToDate(ngayNhan), 
            Utils::stringToDate(ngayTra), 
            Utils::stringToInt(soLuongKhach), 
            QLLP.timLoaiPhong(loaiPhong)->getGiaPhong()
        );
        QLDP.themDatPhong(newDP);
    }
    else if(role == KHACHHANG) {
        KhachHang *KH = (KhachHang *)current_user;
        DatPhong *newDP = new DatPhong(
            QLDP.taoMaDatPhong(), 
            Utils::stringToDate(ngayNhan), 
            Utils::stringToDate(ngayTra), 
            Utils::stringToInt(soLuongKhach), 
            QLLP.timLoaiPhong(loaiPhong)->getGiaPhong()
        );
        QLDP.themDatPhong(newDP);
    }
}

void QLKhachSan::list_Type_Room_Available() {
    string ngayNhan, ngayTra, soLuongKhach;
    LinkedList<Phong *> phongTrong;
    LinkedList<loaiPhongAvailable> listlpa;
    searchTypeRoom(ngayNhan, ngayTra, soLuongKhach, phongTrong, listlpa);
    Node<loaiPhongAvailable> *lpa = listlpa.begin();
    while(lpa != listlpa.end()) {
        cout << *(lpa->data.loaiphong);
        Utils::outputData("So luong phong trong: ", CONSOLE);
        Utils::outputData(Utils::intToString(lpa->data.amount) + "\n", CONSOLE_OR_UI);
        Utils::outputData("\n\n", CONSOLE);
        lpa = lpa->next;
    }
}

void QLKhachSan::list_Room_Available() {
    string ngayNhan, ngayTra, soLuongKhach;
    LinkedList<Phong *> phongTrong;
    LinkedList<loaiPhongAvailable> listlpa;
    searchTypeRoom(ngayNhan, ngayTra, soLuongKhach, phongTrong, listlpa);
    string loaiPhong;
    loaiPhong = Utils::inputWithCondition("Nhap loai phong: ", 3, 7, ALPHABET_AND_NUMBER_ONLY);
    Utils::outputData("Danh sach phong:\n", CONSOLE);
    Node<Phong *> *p = phongTrong.begin();
    while(p != phongTrong.end()) {
        if(p->data->getLoaiPhong()->getLoaiPhong() == loaiPhong) {
            Utils::outputData(p->data->getMaPhong() + "\n", CONSOLE_OR_UI);
        }
        p = p->next;
    }
}

void QLKhachSan::list_all_type_room() {
    LinkedList<LoaiPhong *> &DSLP = QLLP.getDSLP();
    Node<LoaiPhong *> *p = DSLP.begin();
    while(p != DSLP.end()) {
        Utils::outputData(p->data->getLoaiPhong() + "\n", CONSOLE_OR_UI);
        p = p->next;
    }
}

role_value QLKhachSan::getCurrentRole() {
    return role;
}

bool QLKhachSan::GuestExist(string ID) {
    return this->QLKH.timKiemKhachHang(ID) != nullptr;
}
