#include<bits/stdc++.h>
#include "./header/QLPhong.h"
QLPhong::QLPhong() {

}

QLPhong::~QLPhong() {

}

void QLPhong::AddRangePhong(string file)
{
    ifstream inputFile(file);
    if(!inputFile.is_open())
        {
            cout << "Error: Could not open file." << endl;
            return;
        }
    string str[3];
    string line;
    int c = 0; 
    string r = "";
    while(getline(inputFile, line))
        {
            cout << line << endl;
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

            (this->DSP).add(A);
        } // mỗi khi vòng lặp while kết thúc, một đối tượng loại phòng nới sẽ được tạo ra  và thêm vào DSLP
   
    inputFile.close();
    return; 
}

void QLPhong::themPhong(Phong) {

}

void QLPhong::xoaPhong(Phong) {

}

void QLPhong::suaThongTin(string) {

}


Phong QLPhong::timPhong(time_t, time_t) {

}
