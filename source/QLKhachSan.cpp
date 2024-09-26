#include "./header/QLKhachSan.h"


QLKhachSan::QLKhachSan() {
    
}

QLKhachSan::~QLKhachSan() {

}


bool QLKhachSan::canReadFile(string) {

}


void QLKhachSan::inputTaiKhoan(string) {

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