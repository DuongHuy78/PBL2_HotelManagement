#ifndef TAIKHOAN_H
#define TAIKHOAN_H
#include "Utils.h"

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

    role_value getRole() const;
    friend ostream& operator<<(ostream&, const TaiKhoan&);
};
#endif