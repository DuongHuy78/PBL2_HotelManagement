#ifndef TAIKHOAN_H
#define TAIKHOAN_H
#include "Utils.h"
#include "NguoiDung.h"
class NguoiDung;
class TaiKhoan {
    string username;
    string password;
    string ID;
    NguoiDung *nguoiDung;
public:
    TaiKhoan();
    TaiKhoan(string, string, string);
    TaiKhoan(const TaiKhoan&);

    string getUsername() const;
    string getPassword() const;
    string getID() const;

    void setUsername(string);
    void setPassword(string);
    void setID(string);

    void setNguoiDung(NguoiDung*);

    role_value getRole() const;
    friend ostream& operator<<(ostream&, const TaiKhoan&);
};
#endif