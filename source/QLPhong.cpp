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
void QLPhong::themPhong(const Phong& newPhong) {
    this->DSP.add(newPhong);
}

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


void QLPhong::suaThongTin(const string& MP){
    Node<Phong> *p = DSP.begin();
    while ((p != DSP.end()))
    {
        if(p->data.getMaPhong() == MP)
            {
                p->data.capNhatThongTin();
                cout << "Da cap nhat thong tin phong voi ID " << MP << " thanh cong!" << endl;
            }
        p = p -> next;
    } 
    cout << "Khong tim thay Phong!" << endl;
}

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

Phong QLPhong::nhapThongTin() {
    string temp;
    Phong tempPhong;
    temp = Utils::inputWithCondition("Nhap Ma Phong: ", 3, MAX_MAPHONG, ALPHABET_AND_NUMBER_ONLY);
    tempPhong.setMaPhong(temp);
    temp = Utils::inputWithCondition("Nhap Loai Phong: ",3, MAX_IDLOAIPHONG, ROOM_TYPE);
    tempPhong.setLoaiPhong(temp);
    return tempPhong;
}

LinkedList<Phong> &QLPhong::getDSP() {
    return this->DSP;
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



