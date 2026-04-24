#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>
#include <fstream>
#include <cctype> //tolower

using namespace std;

struct Song {
    int id;
    string title;
    string artist;
    int playCount;
    Song* next;
    Song* prev;

    Song(int _id = 0, const string& t = "", const string& a = "", int p = 0);
};

string toLowerStr(string s);
string inputLineTrimmed();
int stringToIntSimple(const string& s);
bool startsWith(string mainStr, string prefix);

#endif
