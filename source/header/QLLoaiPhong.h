#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"
#include "LinkedList.h"

class QLLoaiPhong {
    LinkedList <LoaiPhong> DSLP; // danh sach loai phong
    /*Mỗi đối tượng LoaiPhong được quản lý và lưu trữ trực tiếp trong danh sách DSDL,
     và QLLoaiPhong sẽ chịu trách nhiệm thêm, xóa, hoặc quản lý các đối tượng LoaiPhong trong danh sách này.*/
public:
    QLLoaiPhong();
    ~QLLoaiPhong();

    void capNhapDuLieuVaoFile(const string&);
    void xemLoaiPhong(string);
    void themLoaiPhong(LoaiPhong); 
    void suaThongTinLoaiPhong(const string&);
    void xoaLoaiPhong(LoaiPhong);
    void QLChoice();

    void AddRangeLoaiPhong(string); // đọc file -> thêm vào DSLP (linkedlist)
    void updateLoaiPhong(LoaiPhong); // 
};
#endif