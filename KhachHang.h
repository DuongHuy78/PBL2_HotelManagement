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

    void getIDKhachHang() const;
    void getHoTen() const;
    void getNgaySinh() const;
    void getSoDienThoai() const;
    void getGioiTinh() const; 

    string setIDKhachHang(string);
    string setHoTen(string);
    time_t setNgaySinh(time_t);
    string setSoDienThoai(string);
    bool setGioiTinh(bool); 
};