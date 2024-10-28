#include "./header/QuanLi.h"
QuanLi::QuanLi() {

}

QuanLi::~QuanLi() {

}

string QuanLi::getIDQuanLi() const {
    return this->IDQuanLi;
}
void QuanLi::setIDQuanLi(string ID) {
    this->IDQuanLi = ID;
}

void QuanLi::work() {
    cout << "Da dang nhap vao tai khoan quan li" << endl;
}