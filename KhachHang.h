#include <iostream>
using namespace std;
class KhachHang {
    string IDKhachHang; // PK
    string hoTen;
    time_t ngaySinh;
    string soDienThoai;
    bool gioiTinh; 
public:
    KhachHang(string, string, time_t, bool);
    KhachHang(const KhachHang&);
    ~KhachHang();

    string getIDKhachHang() const;
    string getHoTen() const;
    time_t getNgaySinh() const;
    string getSoDienThoai() const;
    bool getGioiTinh() const; 

    void setIDKhachHang(string);
    void setHoTen(string);
    void setNgaySinh(time_t);
    void setSoDienThoai(string);
    void setGioiTinh(bool); 
};