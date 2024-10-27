#ifndef LOAIPHONG_H
#define LOAIPHONG_H
#include <iostream>
using namespace std;

class LoaiPhong {
    private: 
        string loaiPhong;  // S,D,D2,T,F,F2
        int loaiGiuong; // 1,2
        int soLuongKhach; // hiểu là số lượng khách tối đa trong 1 phòng
        int dienTich;
        int giaPhong;
        string moTaPhong;
    
    public:
        LoaiPhong();
        ~LoaiPhong();
        LoaiPhong(string, int, int, int, int, string); // phong trong data
        LoaiPhong(const LoaiPhong&);

        string getLoaiPhong() const; // mã loại phòng
        int getLoaiGiuong() const; // 1 hoặc 2
        int getSoLuongKhach() const; 
        int getGiaPhong() const;
        int getDienTich() const;
        string getMoTaPhong() const;

        void NhapLoaiPhongMoi();
        void setLoaiPhong(string);
        void setLoaiGiuong(int);
        void setSoLuongKhach(int);
        void setDienTich(int);
        void setGiaPhong(int);
        void setMoTaPhong(string);
};
#endif