#include <iostream>
using namespace std;
class Phong {
    string maPhong;
    string loaiPhong;
    bool trangThai;
public:
    Phong(string, string, bool);
    Phong(const Phong&);
    ~Phong();

    string getMaPhong() const;
    string getLoaiPhong() const;
    bool getTrangThai() const;

    void setMaPhong(string);
    void setLoaiPhong(string);
    void setTrangThai(bool);
};