#include "./header/QLKhachSan.h"


QLKhachSan::QLKhachSan() {
    
}

QLKhachSan::~QLKhachSan() {

}

void QLKhachSan::inputTaiKhoan(string path) {
    
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

void QLKhachSan::work() {
    NguoiDung *p;
    while(role == UNDEFINED) {
        if(role == -1) p = dangNhap();
        if(p != NULL) p->work();
    }
}

NguoiDung *QLKhachSan::dangNhap() {
    string username, password;
    cout << "Nhap username: ";
    cin >> username;
    cout << "Nhap password: ";
    cin >> password;
    Node<TaiKhoan> *i = DSTKKH.head->next;
    while(i != DSTKKH.head) {
        if(i->data.getUsername() == username && i->data.getPassword() == password) {
            role = KHACHHANG;
            return QLKH.timKiemKhachHang(i->data.getID()); 
        }
        i = i->next;
    }

    if(username == TKNhanVien.getUsername() && password == TKNhanVien.getPassword()) {
        role = NHANVIEN;
        return &NV;
    }

    if(username == TKQuanLi.getUsername() && password == TKQuanLi.getPassword()) {
        role = QUANLI;
        return &QL;
    }
    cout << "Sai username hoac password" << endl;
    return NULL;
}

void QLKhachSan::dangXuat(string) {

}

void QLKhachSan::kiemTraTraPhong() {

}

void QLKhachSan::thongBao(string, string) {

}