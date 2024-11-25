#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <cctype>
#include <conio.h>
#include <iomanip>

#define MAX_NAME 50
using namespace std;

enum role_value {
    UNDEFINED_ROLE = -1,
    KHACHHANG,
    NHANVIEN,
    QUANLI,
};    

enum gender_value {
    UNDEFINED_GENDER = -1,
    NAM,
    NU,
};

enum sign_up_return_value {
    SIGN_UP_SUCCESS,
    SIGN_UP_USERNAME_EXISTED,
    SIGN_UP_BLANK_INFO,
    SIGN_UP_INVALID_INFO,
};

enum IO_MODE {
    CONSOLE,        // Nhập xuất trên console
    UI_STREAM,      // Nhập xuất từ UI
    CONSOLE_OR_UI, // Nhập xuất trên console và từ UI
};

enum condition_value {
    GENDER,
    NUMBER_ONLY,
    ALPHABET_ONLY,
    ALPHABET_AND_NUMBER_ONLY,
    ALPHABET_AND_SPACE_ONLY,
    ALPHABET_AND_NUMBER_AND_SPACE_ONLY,
    VIETNAM_PHONE_NUMBER,
    DATE,
    ROOM_TYPE,
    ROOM_BED_TYPE,
};

enum user_option_value {
    CONTINUE,
    SIGN_OUT,
    USER_BOOK_ROOM,
    PRINT_DSKH,
    PRINT_DSDP,
    PRINT_DSLP,
    PRINT_DSP,
    PRINT_DSKH_ID,
    PRINT_DSDP_ID,
    PRINT_DSKH_SDT,
    PRINT_DSP_ID,
    PRINT_DSP_LOAIPHONG,
    ADD_KHACHHANG,
};

extern stringstream UI_input_buffer;
extern stringstream UI_output_buffer;
extern IO_MODE current_mode;    // Chế độ hiện tại: {CONSOLE, UI_STREAM}

/**
 * Chứa các hàm tiện ích
 */
class Utils {
public:
    static string intToString(int n) {
        stringstream ss;
        ss << n;
        return ss.str();
    }

    static int stringToInt(string s) {
        stringstream ss(s);
        int n;
        ss >> n;
        return n;
    }

    static string timeToString(time_t t) {
        struct tm *timeinfo = localtime(&t);
        string buffer = "";
        try {
            if(timeinfo == NULL) {
                throw runtime_error("Loi: khong the lay timeinfo.");
            }
            buffer += intToString(timeinfo->tm_hour) + ':'
                + intToString(timeinfo->tm_min) + ':'
                + intToString(timeinfo->tm_sec) + ' '
                + intToString(timeinfo->tm_mday) + '/'
                + intToString(timeinfo->tm_mon + 1) + '/'
                + intToString(timeinfo->tm_year + 1900);
        }
        catch (const runtime_error &e){
            cout << e.what() << endl;
        }
        catch (const exception &e) {
            cout << e.what() << endl;
        }
        
        return buffer;
    }

    /**
     * Định dạng của chuỗi s: "HH-MM-SS DD/MM/YYYY"
     */
    static time_t stringToTime(string s) {
        struct tm timeinfo;
        try {
            if(s.size() != 19) {
                throw runtime_error("Loi: do dai thoi gian khong hop le.");
            }
            timeinfo.tm_hour = stringToInt(s.substr(0, 2));
            timeinfo.tm_min = stringToInt(s.substr(3, 2));
            timeinfo.tm_sec = stringToInt(s.substr(6, 2));
            timeinfo.tm_mday = stringToInt(s.substr(9, 2));     
            timeinfo.tm_mon = stringToInt(s.substr(12, 2)) - 1;    
            timeinfo.tm_year = stringToInt(s.substr(15, 4)) - 1900;            
        }
        catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
        catch (const exception &e) {
            cout << e.what() << endl;
        }
        return mktime(&timeinfo);
    }

    static string dateToString(time_t t) {
        struct tm *timeinfo = localtime(&t);
        string buffer = "";
        try {
            if(timeinfo == NULL) {
                throw runtime_error("Loi: khong the lay timeinfo.");
            }
            buffer += intToString(timeinfo->tm_mday) + '/'
                + intToString(timeinfo->tm_mon + 1)+ '/'
                + intToString(timeinfo->tm_year + 1900);
        }
        catch (const runtime_error &e){
            cout << e.what() << endl;
        }
        catch (const exception &e) {
            cout << e.what() << endl;
        }
        
        return buffer;
    }

    /**
     * Định dạng của chuỗi s: "DD/MM/YYYY"
     */
    static time_t stringToDate(string s) {
        struct tm timeinfo;
        try {
            if(s.size() != 10) {
                throw runtime_error("Loi: do dai thoi gian khong hop le.");
            }
            timeinfo.tm_mday = stringToInt(s.substr(0, 2));
            timeinfo.tm_mon = stringToInt(s.substr(3, 2)) - 1;
            timeinfo.tm_year = stringToInt(s.substr(6, 4)) - 1900;
            timeinfo.tm_hour = 0;
            timeinfo.tm_min = 0;
            timeinfo.tm_sec = 0;
        }
        catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
        catch (const exception &e) {
            cout << e.what() << endl;
        }
        return mktime(&timeinfo);
    }

    /**
     * Hàm này dùng để lấy chuỗi con từ chuỗi s từ vị trí pos
     * cho đến khi gặp kí tự x
     */
    static string getSubstringUntilX(const string &s, int &pos, char x) {
        string substring = "";
        for(int i = pos; i < s.size(); ++i) {
            if(s[i] == x) {
                pos = i + 1;
                break;
            }
            substring += s[i];
        }
        return substring;
    }

    static string trim(const string &s) {
        int begin_s, end_s;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] != ' ' && s[i] != '\n' && s[i] != '\t') {
                begin_s = i;
                break;
            }
        }

        for(int i = s.size() - 1; i >= 0; --i) {
            if(s[i] != ' ' && s[i] != '\n' && s[i] != '\t') {
                end_s = i;
                break;
            }
        }

        if(end_s > begin_s) {
            return s.substr(begin_s, end_s - begin_s + 1);
        }
        else return "";
    }

    static string chuanHoaTen(const string& ten) {
        string tenChuanHoa;
        bool vietHoa = true;

        for (char c : ten) {
            if (c == ' ') { // Kiểm tra khoảng trắng
                vietHoa = true;
                tenChuanHoa += c;
            } else if (vietHoa) {
                tenChuanHoa += toupper(c);
                vietHoa = false;
            } else {
                tenChuanHoa += tolower(c);
            }
        }
    return tenChuanHoa; 
    }

    static string toLower(const string &s) {
        string newS = "";
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] >= 'A' && s[i] <= 'Z') {
                newS += s[i] - 'A' + 'a';
            }
            else {
                newS += s[i];
            }
        }
        return newS;
    }

    static string toUpper(const string &s) {
        string newS = "";
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] >= 'a' && s[i] <= 'z') {
                newS += s[i] - 'a' + 'A';
            }
            else {
                newS += s[i];
            }
        }
        return newS;
    }

    static string genderToString(gender_value gender) {
        if(gender == NAM) return "Nam";
        if(gender == NU) return "Nu";
        return "Undefined";
    }

    static gender_value stringToGender(string s) {
        string tmp = trim(toLower(s));
        if(tmp == "nam") return NAM;
        if(tmp == "nu") return NU;
        return UNDEFINED_GENDER;
    }

    static string inputWithCondition(string message, int minSize, int maxSize, condition_value condition) {
        outputData(message, CONSOLE);
        string input;
        inputData(input, CONSOLE_OR_UI);
        bool (*isVaild)(const string &) = nullptr;
        if(condition == GENDER) isVaild = isGender;
        if(condition == NUMBER_ONLY) isVaild = isNumberOnly;
        if(condition == ALPHABET_ONLY) isVaild = isAlphabetOnly;
        if(condition == ALPHABET_AND_NUMBER_ONLY) isVaild = isAlphabetAndNumberOnly;
        if(condition == ALPHABET_AND_SPACE_ONLY) isVaild = isAlphabetAndSpaceOnly;
        if(condition == ALPHABET_AND_NUMBER_AND_SPACE_ONLY) isVaild = isAlphabetAndNumberAndSpaceOnly;
        if(condition == VIETNAM_PHONE_NUMBER) isVaild = isVietNamPhoneNumber;
        if(condition == DATE) isVaild = isDate;
        if(condition == ROOM_TYPE) isVaild = isRoomType;
        if(condition == ROOM_BED_TYPE) isVaild = isRoomBedType;
        while (input.size() < minSize || input.size() > maxSize || !isVaild(input)) {
            if(input.size() < minSize || input.size() > maxSize) 
            outputData("Do dai khong hop le. Vui long nhap lai: \n", CONSOLE);
            else outputData("Du lieu khong hop le. Vui long nhap lai: \n", CONSOLE);
            inputData(input, CONSOLE_OR_UI);
        }
        return input;
    }
    // add utils function here . . . 
    static bool isGender(const string &s) {
        if(stringToGender(s) == UNDEFINED_GENDER) {
            return false;
        }
        return true;
    }

    static bool isNumberOnly(const string &s) {
        for (char c : s) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    static bool isAlphabetOnly(const string &s) {
        for (char c : s) {
            if (!isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    static bool isAlphabetAndNumberOnly(const string &s) {
        for (char c : s) {
            if (!isalnum(c)) {
                return false;
            }
        }
        return true;
    }

    static bool isAlphabetAndSpaceOnly(const string &s) {
        for (char c : s) {
            if (!isalpha(c) && c != ' ') {
                return false;
            }
        }
        return true;
    }

    static bool isAlphabetAndNumberAndSpaceOnly(const string &s) {
        for (char c : s) {
            if (!isalnum(c) && c != ' ') {
                return false;
            }
        }
        return true;
    }

    static bool isVietNamPhoneNumber(const string &s) {
        if (s.length() != 10) {
            return false;
        }
        for (char c : s) {
            if (!isdigit(c)) {
                return false;
            }
        }
        string prefix_list[] = {"032", "033", "034", "035", "036", "037", "038", "039",
            "096", "097", "098", "086", "083", "084", "085", "081", "082", "088", "091",
            "094", "070", "079", "077", "076", "078", "090", "093", "089", "056", "058",
            "092", "059", "099"};
        string prefix = s.substr(0, 3);
        for(string p : prefix_list) {
            if (prefix == p) {
                return true;
            }
        }
        return false;
    }

    static bool isLeapYear(int year) {
        if(year % 400 == 0) return true;
        if(year % 4 == 0 && year % 100 != 0) return true;
        return false;
    }

    static int monthDays(int month, int year) {
        if(isLeapYear(year)) {
            //                01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12
            int maxDay[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            return maxDay[month - 1];
        }
        else {
            //                01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12
            int maxDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            return maxDay[month - 1];
        }
    }

    static bool isDate(const string &s) {
        if(s.length() != 10) {
            return false;
        }
        int slashCount = 0;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] != '/' && !isdigit(s[i])) {
                return false;
            }
            if(s[i] == '/') {
                slashCount++;
            }
        }
        if(slashCount != 2) {
            return false;
        }
        string day = "", month = "", year = "";
        int pos = 0;
        day = getSubstringUntilX(s, pos, '/');
        month = getSubstringUntilX(s, pos, '/');
        year = getSubstringUntilX(s, pos, '\n');
        if(day.size() != 2 || month.size() != 2 || year.size() != 4) {
            return false;
        }
        if(isNumberOnly(day) == false || isNumberOnly(month) == false || isNumberOnly(year) == false) {
            return false;
        }
        int d = stringToInt(day);
        int m = stringToInt(month);
        int y = stringToInt(year);
        if (m < 1 || m > 12) {
            return false;
        }
        if (d < 1 || d > monthDays(m, y)) {
            return false;
        }
        return true;
    }

    static bool isRoomType(const string &s) {
        string roomTypes[] = {"S", "D", "D2", "T", "F", "F2"};
        for (string roomType : roomTypes) {
            if (s == "ST" + roomType || s == "VIP" + roomType) {
                return true;
            }
        }
        return false;
    }

    static bool isRoomBedType(const string &str) {
        int s = stringToInt(str);
        int roomBedTypes[] = {1, 2, 12};
        for (int roomBedType : roomBedTypes) {
            if (s == roomBedType) {
                return true;
            }
        }
        return false;
    }

    static void wrapText(const string& text, int width, int indent) {
        // Chinh sua de dung chung voi UI
        istringstream iss(text);
        string word;
        string line;
        string result = "";
        while (iss >> word) {
            if (line.length() + word.length() + 1 > width) {
                result += string(indent, ' ') + line + '\n';
                line.clear();
            }
            line += (line.empty() ? "" : " ") + word;
        }
        if (!line.empty()) {
            result += string(indent, ' ') + line + '\n';
        }
        outputData(result, CONSOLE_OR_UI);
    }
    
    template<typename T>
    static void inputData(T &data, IO_MODE mode) {
        if(cin.rdbuf()->in_avail()) {
            if(cin.peek() == '\n') cin.ignore();
        }
        if(UI_input_buffer.rdbuf()->in_avail()) {
            if(UI_input_buffer.peek() == '\n') UI_input_buffer.ignore();
        }
        try {
            if(current_mode == CONSOLE) {
                if(mode == CONSOLE || mode == CONSOLE_OR_UI) {
                    std::getline(cin, data);
                }
            }
            else if(current_mode == UI_STREAM) {
                if(mode == UI_STREAM || mode == CONSOLE_OR_UI) {
                    std::getline(UI_input_buffer, data);
                }
            }
        }
        catch (const exception &e) {
            cout << e.what() << endl;
        }
    }

    template<typename T>
    static void outputData(T data, IO_MODE mode) {
        if(current_mode == CONSOLE) {
            if(mode == CONSOLE || mode == CONSOLE_OR_UI) {
                cout << data;
                cout.flush();
            }
        }
        else if(current_mode == UI_STREAM) {
            if(mode == UI_STREAM || mode == CONSOLE_OR_UI) {
                UI_output_buffer << data;
            }
        }
    }
};
#endif