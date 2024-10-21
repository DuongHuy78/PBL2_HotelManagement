#include "./header/QLKhachSan.h"


QLKhachSan::QLKhachSan() {
    
}

QLKhachSan::~QLKhachSan() {

}


bool QLKhachSan::canReadFile(string path) {     //kiểm tra đọc file
    ifstream file(path);
    if(!file) {
        cout << "Khong the mo file::" << path << endl;
        return 0;
    }
    file.close();
    return 1;
}


void QLKhachSan::inputTaiKhoan(string path) {   //đọc đầu vào tài khoản

}

void QLKhachSan::inputKhachHang(string) {

}

void QLKhachSan::inputLoaiPhong(string) {

}

void QLKhachSan::inputPhong(string) {

}

void QLKhachSan::inputDatPhong(string) {

}


void QLKhachSan::outputTaiKhoan(string) {

}

void QLKhachSan::outputKhachHang(string) {

}

void QLKhachSan::outputLoaiPhong(string) {

}

void QLKhachSan::outputPhong(string) {

}

void QLKhachSan::outputDatPhong(string) {

}

int QLKhachSan::getRoleById(string) {

}

void QLKhachSan::work() {
    NguoiDung *p;
    while(true) {
        if(role == -1) p = dangNhap();
        p->work();
    }
}

NguoiDung *QLKhachSan::dangNhap() {

}

void QLKhachSan::dangXuat(string) {

}

void QLKhachSan::kiemTraTraPhong() {

}

void QLKhachSan::thongBao(string, string) {

}
void chuanhoaten(std::string &str) {
    // Chuyển tất cả các ký tự thành chữ thường
    for (char &c : str) {
        c = tolower(c);
    }
    // Chuyển ký tự đầu tiên và ký tự sau dấu cách thành chữ hoa
    for (size_t i = 0; i < str.size(); ++i) {
        if (i == 0 || str[i-1] == ' ') {
            str[i] = toupper(str[i]);
        }
    }
}