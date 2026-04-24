#include "Song.h"

Song::Song(int _id, const string& t, const string& a, int p)
    : id(_id), title(t), artist(a), playCount(p), next(nullptr), prev(nullptr) {}

// change upper case to lower case, Usage: when user types & extract from files
string toLowerStr(string s) {
    string res = s;
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = tolower(res[i]);
    }
    return res;
}

// remove spaces
string inputLineTrimmed() {
    string s; getline(cin, s);
    while (!s.empty() && (s.front()==' '||s.front()=='\t')) s.erase(0,1);
    while (!s.empty() && (s.back()==' '||s.back()=='\t')) s.erase(s.size()-1);
    return s;
}

// convert input to ASCll to check if the input contains characters
int stringToIntSimple(const string& s) {
    int num = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return 0;
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

// check string & compare it with input
bool startsWith(string mainStr, string prefix) {
    if (mainStr.length() < prefix.length()) return false;
    for (size_t i = 0; i < prefix.length(); i++) {
        if (mainStr[i] != prefix[i]) return false;
    }
    return true;
}
