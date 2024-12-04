#include "./header./QLLoaiPhong.h"
#include <bits/stdc++.h>
LinkedList<string> roomTypes;
QLLoaiPhong::QLLoaiPhong()
{

}

QLLoaiPhong::~QLLoaiPhong()
{
}

// HÀM THÊM CÁC LOẠI PHÒNG vào DSLP (LinkedList)
// void QLLoaiPhong::AddRangeLoaiPhong(string file){ 
//     ifstream inputFile(file);
//     if (!inputFile.is_open()) {
//         cerr << "Error: Could not open file." << endl;
//         return ;
//     }
//     int count = 0;
//     string line; 
//     while (getline(inputFile, line)) {  
//             string str[6]; // chứa  6 trường của loại phòng 
//             int c = 0;
//             string r = "";
//             for (int i = 0; i < line.size(); i++)
//                 {
//                     if (line[i] == ';')
//                     {
//                         str[c++] = r;
//                         r = "";
//                     } 
//                     else r += line[i]; // nếu kí tự không phải dấu ; thì thêm dữ liệu vào r
//                 }
//             if (r.size() > 0)
//                 {
//                     str[c++] = r;
//                 }

//             LoaiPhong A(str[0], stoi(str[1]), stoi(str[2]), stoi(str[3]), stoi(str[4]), str[5]);
//             (this->DSLP).add(A);
//             count++;
//     }
//     inputFile.close();
//     cout << "Da nhap du lieu cua " << count << " loai phong tu file: " << file << endl;
//     return; 
// }

void QLLoaiPhong::themLoaiPhong(const LoaiPhong& NewLP){
    roomTypes.add(NewLP.getLoaiPhong());
    (this->DSLP).add(NewLP);
}

// void QLLoaiPhong::xemLoaiPhong(){
//     cout << "DANH SACH LOAI PHONG CUA KHACH SAN CHUNG TOI:\n" << endl;
//     cout << left << setw(12) << "LoaiPhong" << setw(13) << "LoaiGiuong" << setw(15) << "SoLuongKhach" 
//          << setw(13) << "DienTich" << setw(25) << "Gia" << "MoTaPhong" << endl;
//     // Đặt chiều rộng của cột = setw() để tạo khoảng cách đều giữa các cột.
//     // left: Đảm bảo văn bản được căn trái.
//     cout << string(105, '-') << endl; 
//     // Tạo một đường kẻ ngang để phân cách tiêu đề bảng với dữ liệu

//       Node<LoaiPhong> *p = DSLP.begin();
//       while(p != DSLP.end()){
//         p->data.xuatThongTin();
//         p = p -> next;
//       }
// }

void QLLoaiPhong::suaThongTin(const string& IDLoaiPhong){
    Node<LoaiPhong> *p = DSLP.begin();
    while ((p != DSLP.end()))
    {
        if(p->data.getLoaiPhong() == IDLoaiPhong)
            {
                p->data.capNhatThongTin();
                cout << "Da cap nhat thong tin loai phong voi ID " << IDLoaiPhong << " thanh cong!" << endl;
                return;
            }
        p = p -> next;
    } 
    cout << "Khong tim thay Loai Phong!" << endl;
}


void QLLoaiPhong::xoaLoaiPhong(const string& IDLoaiPhong){
    Node<LoaiPhong> *p = DSLP.begin();
    while( p != DSLP.end())
    {
        if(p->data.getLoaiPhong() == IDLoaiPhong)
            {
                DSLP.remove(p);
                cout << "Da xoa Loai Phong voi ID: " << IDLoaiPhong << endl;
                return;
            }
        p = p -> next;
    }
    cout << "Khong tim thay Loai Phong!" << endl;
}

LoaiPhong *QLLoaiPhong::timLoaiPhong(string IDLoaiPhong){
    Node<LoaiPhong> *p = DSLP.begin();
    while(p != DSLP.end()) {
        if(p->data.getLoaiPhong() == IDLoaiPhong) {
            return &p->data;
        }
        p = p -> next;
    }
    return nullptr;
}


int QLLoaiPhong::soLuongKhach(string maLoaiPhong) {
    return timLoaiPhong(maLoaiPhong)->getSoLuongKhach();
}

int QLLoaiPhong::getGiaPhong(string maLoaiPhong) {
    return timLoaiPhong(maLoaiPhong)->getGiaPhong();
} 

LinkedList<LoaiPhong>& QLLoaiPhong::getDSLP() {
    return DSLP;
}

ostream& operator<<(ostream& os, const QLLoaiPhong& ql) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-LOAI-PHONG----------------\n", CONSOLE);
    Utils::outputData("Danh sach loai phong: \n", CONSOLE);
    Node<LoaiPhong> *p = ql.DSLP.begin();
    while(p != ql.DSLP.end()){
        os << p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}