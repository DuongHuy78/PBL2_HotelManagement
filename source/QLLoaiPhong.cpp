#include "./header/QLLoaiPhong.h"
#include <bits/stdc++.h>
#include "LinkedList.h"
QLLoaiPhong::QLLoaiPhong() {

}

QLLoaiPhong::~QLLoaiPhong() {
    
}

void QLLoaiPhong::AddRangeLoaiPhong(string file){ // file = loaiphong.txt
    ifstream inputFile(file);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return ;
    }
    string line; 
    while (getline(inputFile, line)) 
        {  
            cout << line << endl; 

            string str[5];
            int c = 0;
            string r = "";
            for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] == '|')
                    {
                        str[c++] = r;
                        r = "";
                    } 
                    else r = r + line[i]; // nếu kí tự không phải dấu |, thêm dữ liệu vào r
                }
            if (r.size() > 0)
                {
                    str[c++] = r;
                }

            LoaiPhong A(stoi(str[0]),stoi(str[1]),stoi(str[2]),str[3],stoi(str[4]));

            (this->DSLP).add(A);
        }
    inputFile.close();
    return; 
}

void QLLoaiPhong::themLoaiPhong(LoaiPhong A) {
    (this->DSLP).add(A);
}

void QLLoaiPhong::xoaLoaiPhong(LoaiPhong ) {

}

void QLLoaiPhong::suaThongTin(string) {

}
