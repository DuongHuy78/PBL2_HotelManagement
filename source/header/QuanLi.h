#ifndef QUANLI_H
#define QUANLI_H
#include "NguoiDung.h"
#include "Utils.h"
class QuanLi: public NguoiDung {
    string IDQuanLi;
public:
    QuanLi();
    ~QuanLi();

    string getIDQuanLi() const;
    void setIDQuanLi(string);
    
    void work();
};
#endif