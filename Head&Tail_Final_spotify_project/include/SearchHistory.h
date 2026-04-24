#ifndef SEARCHHISTORY_H
#define SEARCHHISTORY_H

#include <string>
#include <iostream>
using namespace std;

class SearchHistory {
    struct Node {
        string data;
        Node* next;
        Node(const string& s): data(s), next(nullptr) {}
    };
    Node* top;
public:
    SearchHistory();
    ~SearchHistory();
    void push(const string& s);
    void display() const;
};

#endif
