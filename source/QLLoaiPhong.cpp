
// #include "./header/QLPhong.h"
#include "./header/QLLoaiPhong.h"



// QLPhong::QLPhong() {

// }

// QLPhong::~QLPhong() {

// }

// void QLPhong::AddRangePhong(string file)
// {
//     ifstream inputFile(file);
//     if(!inputFile.is_open())
//         {
//             cout << "Error: Could not open file." << endl;
//             return;
//         }

//     cout << "Day la danh sach phong cua chung toi: "<< endl;
//     cout << left << setw(12) << "MaPhong" << "LoaiPhong" << endl;
//     cout << string(24, '-') << endl;

//     string line; 
//     while(getline(inputFile, line))
//         {
//            // cout << line << endl;
//             string str[2]; // chua hai truong : maphong va loaiphong
//             string r = "";
//             int c = 0; 
//             for(int i = 0; i < line.size(); i++)
//             {
//                 if(line[i] == ';')
//                 {
//                     str[c++] = r;  // Lưu giá trị r vào str[c] và tăng c
//                     r = ""; // Reset r về chuỗi rỗng để chuẩn bị cho trường mới
//                 }
//                 else r += line[i];
//             }
//             if(r.size() > 0)
//             {
//                 str[c++] = r;
//             }       
//             Phong A(str[0], str[1]);
//             (this->DSP).add(A); // mỗi khi vòng lặp while kết thúc, một đối tượng loại phòng nới sẽ được tạo ra  và thêm vào DSLP

//             // In thông tin đã đọc được ra màn hình với định dạng
//             cout << left << setw(15) << str[0] << str[1] << endl;
//             cout << string(25, '-') << endl;
//         }

//     inputFile.close();
//     return; 
// }

// void QLPhong::themPhong(Phong) {
    
// }

// void QLPhong::xoaPhong(Phong) {

// }
// Phong QLPhong::timPhong(time_t, time_t) {}


/*
Quản lí loại phòng:
--------------------------------------------------------
- Xem danh sách loại phòng
- Thêm loại phòng()
- Sửa thông tin loại phòng ((chỉ quản lý đc chỉnh, nhân viên chỉ được đc coi)
	Đầu vào: loại phòng,
	Sau đó hiển thị thông tin muốn sửa, ví dụ:
	1. sửa loại giường
	2. sửa giá phòng
	3. sửa mô tả
	...
	sau đó thì chọn số -> sửa bằng các hàm set của 	đối tượng loại phòng)
- Xoá loại phòng()
*/
QLLoaiPhong::QLLoaiPhong()
{
}

QLLoaiPhong::~QLLoaiPhong()
{
}

// HÀM ĐỊNH DẠNG CHO TRƯỜNG MÔ TẢ ( ý là chưa biết bỏ mô nên để tạm đây keke)
void wrapText(const string& text, int width, int indent) {
    istringstream iss(text);
    string word;
    string line;
    bool firstLine = true;

    while (iss >> word) {
        if (line.length() + word.length() + 1 > width) {
            if (!firstLine) cout << setw(indent) << ""; // Thụt lề cho các dòng sau
            cout << line << endl;
            line.clear();
            firstLine = false;
        }
        line += (line.empty() ? "" : " ") + word;
    }
    if (!line.empty()) {
        if (!firstLine) cout << setw(indent) << "";
        cout << line << endl;
    }
}

// HÀM GHI DỮ LIỆU LẠI VÀO FILE
void QLLoaiPhong::capNhapDuLieuVaoFile(const string& file) 
{
    ofstream outputFile(file);
    if (!outputFile.is_open()) 
    {
        cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    Node<LoaiPhong>* current = DSLP.begin(); // Bắt đầu từ nút đầu tiên
    while (current != DSLP.end())// Duyệt đến điểm kết thúc
    { 
        outputFile << current->data.getLoaiPhong() << ";"
                   << current->data.getLoaiGiuong() << ";"
                   << current->data.getSoLuongKhach() << ";"
                   << current->data.getDienTich() << ";"
                   << current->data.getGiaPhong() << ";"
                   << current->data.getMoTaPhong() << endl; // Ghi dữ liệu vào file
        current = current->next; // Chuyển đến nút tiếp theo
    }
    outputFile.close(); // Đóng file
    cout << "Du lieu da duoc ghi vao file." << endl;
}

// HÀM IN RA DANH SÁCH LOẠI PHÒNG (loaiphong.txt)
void QLLoaiPhong::xemLoaiPhong(string file) // file = loaiphong.txt
{
    ifstream inputFile(file);
    if(!inputFile.is_open())
        {
           cerr << "Error: Khong the mo data LoaiPhong!" << endl; 
           return;
        }
    cout << "DANH SACH LOAI PHONG CUA KHACH SAN CHUNG TOI:\n" << endl;
    cout << left << setw(12) << "LoaiPhong" << setw(13) << "LoaiGiuong" << setw(15) << "SoLuongKhach" 
        << setw(13) << "DienTich" << setw(25) << "Gia" << "MoTaPhong" << endl;
        // Đặt chiều rộng của cột = setw() để tạo khoảng cách đều giữa các cột.
        // left: Đảm bảo văn bản được căn trái.
    cout << string(105, '-') << endl; 
        // Tạo một đường kẻ ngang để phân cách tiêu đề bảng với dữ liệu

    string line; 
    while (getline(inputFile, line)) 
        {  
            string str[6]; // chứa  6 trường của loại phòng 
            int c = 0;
            string r = "";
            for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ';')
                    {
                        str[c++] = r;
                        r = "";
                    } 
                    else r += line[i]; // nếu kí tự không phải dấu ; thì thêm dữ liệu vào r
                }
            if (r.size() > 0)
                {
                    str[c++] = r;
                }
             // In thông tin đã đọc được ra màn hình với định dạng
            cout << left << setw(16) << str[0] << setw(14) << str[1] << setw(13) << str[2]
                 << setw(9) << str[3] << setw(13) << str[4];  wrapText(str[5], 40, 65);
            cout << string(105, '-') << endl;
    }
    inputFile.close();
    return; 
}

// HÀM THÊM LOẠI PHÒNG (loaiphong.txt)
void QLLoaiPhong::themLoaiPhong(LoaiPhong LP) {
    ofstream inputFile("./data/loaiphong.txt", ios::app); // Mở tệp ở chế độ ghi đè cuối (append)
    if(inputFile.is_open())
    {
        inputFile << LP.getLoaiPhong() << ";";
        inputFile << LP.getLoaiGiuong() << ";";
        inputFile << LP.getSoLuongKhach() << ";";
        inputFile << LP.getDienTich() << ";";
        inputFile << LP.getGiaPhong() << ";";
        inputFile << LP.getMoTaPhong();
        inputFile.close();
        cout << "Da luu thong in loai phong moi vao file data loaiphong!" << endl;
    }
    else 
    {
        cout << "Khong the mo data loaiphong!" << endl;
        return;
    }
}

// HÀM THÊM CÁC LOẠI PHÒNG vào DSLP (LinkedList)
void QLLoaiPhong::AddRangeLoaiPhong(string file){ 
    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return ;
    }
    string line; 
    while (getline(inputFile, line)) 
        {  
            string str[6]; // chứa  6 trường của loại phòng 
            int c = 0;
            string r = "";
            for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == ';')
                    {
                        str[c++] = r;
                        r = "";
                    } 
                    else r += line[i]; // nếu kí tự không phải dấu ; thì thêm dữ liệu vào r
                }
            if (r.size() > 0)
                {
                    str[c++] = r;
                }
          //  cout << str[0] << "\n" << str[1] << "\n" << str[2] << "\n"<< str[3] << "\n" <<str[4] << "\n" << str[5] << "\n";

            LoaiPhong A(str[0], stoi(str[1]), stoi(str[2]), stoi(str[3]), stoi(str[4]), str[5]);
            DSLP.add(A);
    }
    inputFile.close();
    return; 
}


// HÀM SỬA THÔNG TIN LOẠI PHÒNG (loaiphong.txt)
void QLLoaiPhong::suaThongTinLoaiPhong(const string& MaLoaiPhong) 
{
    if (MaLoaiPhong.empty()) 
    {
        cerr << "Error: Mã loại phòng không được để trống!" << endl;
        return;
    }
  //  AddRangeLoaiPhong("./data/loaiphong.txt"); // DSLP

    Node<LoaiPhong>* current = DSLP.begin(); // Bắt đầu từ nút đầu tiên
    while (current != DSLP.end()) 
    { // Duyệt đến điểm kết thúc
        if (current->data.getLoaiPhong() == MaLoaiPhong) // So sánh mã loại phòng
        {    
            int thongTin; 
            // Nếu tìm thấy loại phòng phù hợp, tiến hành chỉnh sửa
            do{
                cout << "1. Sua Loai Giuong: " << endl;
                cout << "2. Sua So Luong Khach: " << endl;
                cout << "3. Sua Dien Tich: " << endl;
                cout << "4. Sua Gia: " << endl;
                cout << "5. Sua Mo Ta Phong: " << endl;
                cout << "6. Thoat Chinh Sua Loai Phong nay!" << endl;

                cout << "Hay chon thong tin muon sua: ";
                cin >> thongTin;
                //Xử lý từng lựa chọn của người dùng
                switch(thongTin)
                {
                    case 1: 
                        {
                            int LoaiGiuong;
                            cout << "Nhap Loai Giuong Moi(1/2/1,2): ";
                            cin >> LoaiGiuong;
                            current->data.setLoaiGiuong(LoaiGiuong);
                            break;
                        }
                    case 2: 
                        {
                            int SoLuongKhach;
                            cout << "Nhap So Luong Khach Moi: ";
                            cin >> SoLuongKhach;
                            current->data.setSoLuongKhach(SoLuongKhach);
                            break;
                        }
                    case 3: 
                        {
                            int DienTich;
                            cout << "Nhap Dien Tich Moi: ";
                            cin >> DienTich;
                            current->data.setDienTich(DienTich);
                            break;
                        }
                    case 4: 
                        {
                            int Gia;
                            cout << "Nhap Gia Moi: ";
                            cin >> Gia;
                            current->data.setGiaPhong(Gia);
                            break;
                        }
                    case 5: 
                        {
                            string MoTa;
                            cout << "Nhap Mo Ta";
                            getline(cin, MoTa);
                            current->data.setMoTaPhong(MoTa);
                            break;
                        }
                    case 6: 
                            cout << "Ban dang thoat khoi chuc nang chinh sua loai phong......" << endl;
                            return ;
                    default: 
                        cout << "Lua chon cua ban khong hop le, vui long nhap lai: " << endl;
                        break;
                }
              } while(thongTin != 6);
              cout << "Helo";
            capNhapDuLieuVaoFile("./data/loaiphong.txt"); // Ghi dữ liệu vào file sau khi chỉnh sửa
            cout << "Thong tin loai phong da duoc cap nhat." << endl;
            return; // Kết thúc hàm sau khi đã chỉnh sửa
        }
        current = current->next;
    } 
    // Kết thúc vòng while mà không tìm thấy mã loại phòng tương ứng 
    cout << "Loai phong khong ton tai." << endl; // Nếu không tìm thấy loại phòng
}


// HÀM XÓA LOẠI PHÒNG (xóa trong file)
// void QLLoaiPhong::xoaLoaiPhong(LoaiPhong LP) {
//    (this->DSLP).remove(LP);
// }

//Các lựa chọn trong hàm này sẽ thao tác với file loaiphong.txt
void QLLoaiPhong::QLChoice()
{
    AddRangeLoaiPhong("./data/loaiphong.txt"); // DSLP
    int Choice;
    do {
        cout << "XIN CHAO QUAN LY CUA DREAM HOTEL: " << endl;
        cout << "Vui Long Nhap Lua Chon: " << endl;
        cout << "1. Xem Danh Sach Loai Phong " << endl;
        cout << "2. Them Loai Phong" << endl;
        cout << "3. Sua Thong Tin Loai Phong" << endl;
        cout << "4. Xoa Loai Phong" << endl;
        cout << "5. Thoat!" << endl;
        cin >> Choice;

        switch (Choice)
            {
            case 1:
                xemLoaiPhong("./data/loaiphong.txt");
                break;
            case 2: 
            {
                LoaiPhong LPM;
                cout << "Hay nhap tat ca thong tin cua loai phong moi: " << endl;
                LPM.NhapLoaiPhongMoi();
                themLoaiPhong(LPM);
                break;
            }
            case 3:
            {
            string PhongMuonSua;
            cout << "Nhap Ma Loai Phong ma ban muon sua: ";
            cin >> PhongMuonSua; // Đọc mã loại phòng
            suaThongTinLoaiPhong(PhongMuonSua);
            break;    
            }
    // case 4:
            // Gọi hàm xóa phòng nếu đã định nghĩa
            // xoaLoaiPhong();
        //   break;
            case 4: 
                cout << "Dang thoat khoi chuc nang Quan Ly Loai Phong......" << endl;
                return;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                break;
            } 
        } while(Choice!=4);
} 