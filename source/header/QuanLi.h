#ifndef QUANLI_H
#define QUANLI_H
#include "NguoiDung.h"
class QuanLi: public NguoiDung {
    string IDQuanLi;
public:
    QuanLi();
    ~QuanLi();
    void work();
};
#endif