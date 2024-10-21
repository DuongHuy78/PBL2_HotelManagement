#ifndef TAIKHOAN_H
#define TAIKHOAN_H
#include <iostream>
using namespace std;
class TaiKhoan {
    string username;
    string password;
    string ID;
public:
    TaiKhoan();
    TaiKhoan(string, string, string);
    TaiKhoan(const TaiKhoan&);
    ~TaiKhoan();

    string getUsername() const;
    string getPassword() const;
    string getID() const;

    void setUsername(string);
    void setPassword(string);
    void setID(string);
};
#endif