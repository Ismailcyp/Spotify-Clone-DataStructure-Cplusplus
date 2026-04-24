#ifndef LIBRARY_H
#define LIBRARY_H

#include "Song.h"

class Library {
    struct Node {
        Song data;
        Node* next;
        Node(const Song& s): data(s), next(nullptr) {}
    };
    Node* head;
    int lastId;

public:
    Library();
    ~Library();
    void clear();
    void saveLibraryToFile(string filename = "musics.txt");
    void loadFromFile(string filename = "musics.txt");
    void addSongToLibrary(const string& t, const string& a, int p);
    void incrementPlayCount(string title);
    void display() const;
    Song* findById(int id);
    Song* searchByTitleAscending(const string& key, int& outCount);
    Song* searchByArtistAscending(const string& key, int& outCount);
};

#endif
