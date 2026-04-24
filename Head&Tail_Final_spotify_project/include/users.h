#ifndef USERS_H
#define USERS_H

#include <string>
#include <fstream>
using namespace std;

bool userExists(const string& username);
bool registerUser(const string& username, const string& password);
bool loginUser(const string& username, const string& password);

#endif
