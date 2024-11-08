#ifndef QLLOAIPHONG_H
#define QLLOAIPHONG_H
#include "LoaiPhong.h"
#include "LinkedList.h"
class QLLoaiPhong {
    /**
    * ### Danh sách loại phòng:
    * ---
    * 1. Mỗi đối tượng LoaiPhong được quản lý và lưu trữ trực tiếp trong danh sách DSDL.
    * 2. QLLoaiPhong sẽ chịu trách nhiệm thêm, xóa, hoặc quản lý các đối tượng LoaiPhong.
    */
    LinkedList<LoaiPhong> DSLP; 
public:
    QLLoaiPhong();
    ~QLLoaiPhong();

    void capNhapDuLieuVaoFile(const string&);   // cân nhắc chuyển vào QLKhachSan
    void themLoaiPhong(LoaiPhong); 
    void suaThongTinLoaiPhong(const string&);
    void xoaLoaiPhong(LoaiPhong);
    void QLChoice();

    void AddRangeLoaiPhong(string); // cân nhắc chuyển vào QLKhachSan
    void updateLoaiPhong(LoaiPhong);     
};
#endif