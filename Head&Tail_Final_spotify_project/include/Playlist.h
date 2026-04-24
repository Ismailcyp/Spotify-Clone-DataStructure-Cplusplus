#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"

class Playlist {
    Song* head;
    Song* tail;
    string playlistName;
    string userFilename;
    Song* lastPlayedPtr;
    int nextId;

public:
    Playlist();
    ~Playlist();

    void setFilename(string username);
    string getFilename() const;
    void setName(const string& n);
    string getName() const;

    void add_node_file(const string& title, const string& artist, int playCount);
    void add_from_library_copy(const Song& s);

    void loadPlaylist();
    void saveToFile();

    void delete_file(const string& targetTitle);
    void printlist() const;
    int countSongs() const;

    Song* play(const string& titleToPlay);
    Song* lastPlayed() const;
    Song* getHead() const;

    void sortByPlayCount(bool descending = true);
};

#endif
