#include <iostream>
using namespace std;
class LoaiPhong {
    int loaiPhong;
    int loaiGiuong;
    int giaPhong;
    string moTaPhong;
    int soLuongKhach;
public:
    LoaiPhong(int, int, int, string, int);
    LoaiPhong(const LoaiPhong&);
    ~LoaiPhong();

    void getLoaiPhong() const;
    void getLoaiGiuong() const;
    void getGiaPhong() const;
    void getMoTaPhong() const;
    void getSoLuongKhach() const;

    int setLoaiPhong(int);
    int setLoaiGiuong(int);
    int setGiaPhong(int);
    string setMoTaPhong(string);
    int setSoLuongKhach(int);
};