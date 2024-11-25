#include "./header/QLPhong.h"

QLPhong::QLPhong() {

}

QLPhong::~QLPhong() {

}

// HÀM THÊM CÁC LPHÒNG vào DSP (LinkedList)
void QLPhong::AddRangePhong(string file) {
    ifstream inputFile(file);
    if(!inputFile.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    // cout << "Day la danh sach phong cua chung toi: "<< endl;
    // cout << left << setw(12) << "MaPhong" << "LoaiPhong" << endl;
    // cout << string(24, '-') << endl;
    int count = 0;
    string line; 
    while(getline(inputFile, line)) {
        // cout << line << endl;
        string str[2]; // chua hai truong : maphong va loaiphong
        string r = "";
        int c = 0; 
        for(int i = 0; i < line.size(); i++)
        {
            if(line[i] == ';')
            {
                str[c++] = r;  // Lưu giá trị r vào str[c] và tăng c
                r = ""; // Reset r về chuỗi rỗng để chuẩn bị cho trường mới
            }
            else r += line[i];
        }
        if(r.size() > 0)
        {
            str[c++] = r;
        }       
        Phong A(str[0], str[1]);
        (this->DSP).add(A); // mỗi khi vòng lặp while kết thúc, một đối tượng loại phòng nới sẽ được tạo ra  và thêm vào DSLP
        count++;
    }
    inputFile.close();
    cout << "Da nhap du lieu cua " << count << " phong tu file: " << file << endl;
}

//update file
void QLPhong::capNhatFile(Phong* head, string path){
    ofstream inputFile(path);
    if(!inputFile)
        {
            cout << "Khong the mo file de ghi!" << endl;
            return;
        }
    Phong *p = head;
    while( p != nullptr) 
        {
            inputFile << p->getMaPhong() << ";"; 
            inputFile << p->getLoaiPhong() <<";";     
            cout << endl;
        }
    inputFile.close();
    cout << "Cap nhat phong.txt thanh cong!" << endl;
}
    
void QLPhong::xemPhong(){
    cout << "Day la danh sach phong cua Hotel Del Luna: "<< endl;
    cout << left << setw(12) << "MaPhong" << "LoaiPhong" << endl;
    cout << string(24, '-') << endl;

    Node<Phong> *p = DSP.begin();
      while(p != DSP.end()){
        p->data.xuatThongTin();
        p = p -> next;
      }
}

//NEW PHÒNG
void QLPhong::themPhong(Phong newPhong) {
    this->DSP.add(newPhong);
}

// void QLPhong::taoPhongMoi(Phong newPhong) {
//     string MaPhongMoi;
//     cout << "Nhap Ma Phong: "; 
//     MaPhongMoi = Utils::nhap(5,MAX_MAPHONG+1);
//     newPhong.setMaPhong(MaPhongMoi);

//     string MaLoaiPhong;
//     cout << "Nhap Loai Phong: ";
//     MaLoaiPhong = Utils::nhap(5,MAX_IDLOAIPHONG+1);

//     while(this->QLLP->timLoaiPhong(MaLoaiPhong) == nullptr)
//     {
//         cout << "Loai phong nay khong ton tai!" << endl;
//         cout << "Hay nhap lai loai phong: ";
//             MaLoaiPhong = Utils::nhap(5,MAX_IDLOAIPHONG+1);
//     }
//     newPhong.setLoaiPhong(MaLoaiPhong);

//     (this->DSP).add(newPhong);
// }

void QLPhong::xoaPhong(const string& MP){
    Node<Phong> *p = DSP.begin();
    while( p != DSP.end())
    {
        if(p->data.getMaPhong() == MP)
            {
                DSP.remove(p);
                cout << "Da xoa Phong voi ID: " << MP << endl;
                return;
            }
        p = p -> next;
    }
    cout << "Khong tim thay Phong!" << endl;
}


// void QLPhong::suaThongTinPhong(const string& MP){
//     Node<Phong> *p = DSP.begin();
//     while ((p != DSP.end()))
//     {
//         if(p->data.getMaPhong() == MP)
//             {
//                 string tempStr = p->data.capNhatThongTin();
//                 if(this->QLLP->timLoaiPhong(tempStr)!=nullptr)
//                 {
//                     p->data.setLoaiPhong(tempStr);
//                 }
//                 cout << "Da cap nhat thong tin Phong: " << MP << " thanh cong!" << endl;
//                 return;
//             }
//         p = p -> next;
//     } 
//     cout << "Khong tim thay Phong!" << endl;
// }

void QLPhong::setQLLP(QLLoaiPhong *QLLP) {
    this->QLLP = QLLP;
}

Phong *QLPhong::timPhong(string MP){
    Node<Phong> *p = DSP.begin();
    while(p != DSP.end()){
        if(p->data.getMaPhong() == MP)
            {
               return &p->data;
            }
        p = p -> next;
    }
    return NULL;
}

// void QLPhong::QLPhong_Choice()
// {
  
//     int Choice;
//     do {
//         cout << "XIN CHAO QUAN LY CUA DREAM HOTEL: " << endl;
//         cout << "Vui Long Nhap Lua Chon " << endl;
//         cout << "1. Xem Danh Sach Phong " << endl;
//         cout << "2. Them Phong" << endl;
//         cout << "3. Sua Thong Tin Phong" << endl;
//         cout << "4. Xoa Phong" << endl;
//         cout << "5. Thoat!" << endl;
        
//         Choice = stoi(Utils::nhap(1,2));
//         switch (Choice)
//             {
//             case 1:
//             {
//                 xemPhong();
//                 system("pause");
//                 system("cls");     
//                 break;
//             }
//             case 2: 
//             {
//                 Phong NewP;
//                 Phong* DSP = nullptr;
//                 cout << "Hay nhap thong tin phong moi: " << endl;
//                 taoPhongMoi(NewP);
//                 capNhatFile(DSP,"./data/phong.txt");
//                 cout << "Them Phong thanh cong!" << endl;
//                 system("pause");
//                 system("cls");
//                 break;
//             }
//             case 3:
//             {
//                 Phong* DSP = nullptr;
//                 string MaPhong_Sua;
//                 cout << "Nhap Ma Phong ma ban muon sua: ";
//                 MaPhong_Sua = Utils::nhap(5,MAX_MAPHONG+1);
//                 suaThongTinPhong(MaPhong_Sua);
//                 capNhatFile(DSP, "./data/phong.txt");
//                 system("pause");
//                 system("sls");
//                 break;    
//             }
//             case 4:
//             {
//                 Phong* DSP = nullptr;
//                 string MaPhong_Xoa;
//                 cout << "Nhap Ma Phong ma ban muon xoa: ";
//                 MaPhong_Xoa = Utils::nhap(5,MAX_MAPHONG+1);
//                 xoaPhong(MaPhong_Xoa);
//                 capNhatFile(DSP, "./data/phong.txt");
//                 system("pause");
//                 system("sls");
//                 break;    
//             }
//             case 5:
//             {
//                 cout << "Ban dang thoat khoi QLPhong........" << endl;
//                 return;
//             }
//             default:
//                 cout << "Lua chon khong hop le";
//                 cout << "Vui long nhap lai!" << endl;
//                 break;
//             } 
//         } while(Choice!=5);
// } 

Phong QLPhong::timPhong(time_t, time_t) {
    return Phong();
}

LinkedList<Phong> &QLPhong::getDanhSachPhong() {
    return this->DSP;
}

Node<Phong> *QLPhong::getHead() {
    return this->DSP.getHead();
}

ostream &operator<<(ostream &os, QLPhong &qlPhong) {
    Utils::outputData("-----------------THONG-TIN-QUAN-LI-PHONG-----------------\n", CONSOLE);
    Utils::outputData("Danh sach phong: \n", CONSOLE);
    Node<Phong> *p = qlPhong.DSP.begin();
    while (p != qlPhong.DSP.end()) {
        os << p->data;
        Utils::outputData("\n", CONSOLE);
        p = p->next;
    }
    return os;
}



