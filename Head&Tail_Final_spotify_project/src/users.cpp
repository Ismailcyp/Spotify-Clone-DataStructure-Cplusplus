#include "Users.h"
// open file line by line to check if the username is already taken
// Returns true if a match is found to prevent duplicate registrations
bool userExists(const string& username) {
    ifstream fin("users.txt");
    if (!fin)
        return false;
    string line;
    while (getline(fin,line)) {
        if (line.empty())
            continue;
        size_t p = 0;
        bool found = false;
        for(size_t k=0; k<line.size(); k++) {
            if(line[k] == '|') {
            p = k;
            found = true;
         break;
          }
        }
        if (!found)
            continue;

        string uname = line.substr(0,p);
        if (uname == username) {
            fin.close();
        return true;
        }
    }
    fin.close();
    return false;
}
// add username & password in user.txt O(N)
bool registerUser(const string& username, const string& password) {
    if (userExists(username))
        return false;
    ofstream fout("users.txt", ios::app);
    fout << username << "|" << password << "\n";
    fout.close();
    return true;
}
//check if user & password are correct
bool loginUser(const string& username, const string& password) {
    ifstream fin("users.txt");
    if (!fin)
        return false;
    string line;
    while (getline(fin,line)) {
        if (line.empty())
            continue;
        size_t p = 0;
        bool found = false;

        for(size_t k=0; k<line.size(); k++) {
            if(line[k] == '|') {
                 p = k;
                 found = true;
                 break;
                 }
            }
        if (!found) continue;
        string uname = line.substr(0,p);
        string pass = line.substr(p+1);
        if (uname == username && pass == password) {
                fin.close();
        return true;
        }
    }
    fin.close();
    return false;
}
