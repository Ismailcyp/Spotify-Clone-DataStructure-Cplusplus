#ifndef RECENTLYPLAYED_H
#define RECENTLYPLAYED_H

#include "Song.h"

class RecentlyPlayed {
    struct Node {
        Song data;
        Node* next;
        Node(const Song& s): data(s), next(nullptr) {}
    };
    Node* head;
    int size;
    int maxSize;
public:
    RecentlyPlayed(int mx = 10);
    ~RecentlyPlayed();
    void push(const Song& s);
    void display() const;
};

#endif
