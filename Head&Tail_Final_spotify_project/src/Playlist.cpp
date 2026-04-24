#include "Playlist.h"
#include <algorithm> // for swap
#include <iostream>
#include <fstream>

using namespace std;

Playlist::Playlist(): head(nullptr), tail(nullptr), playlistName("My Playlist"), userFilename("playlist.txt"), lastPlayedPtr(nullptr), nextId(1) {}

Playlist::~Playlist() {
    Song* cur = head;
    while (cur) {
    Song* t = cur->next;
     delete cur;
      cur = t;
      }
}

// setters & getters for each user's playlist
void Playlist::setFilename(string username) {
    userFilename = username + "_playlist.txt";
}
string Playlist::getFilename() const {
    return userFilename;
     }

void Playlist::setName(const string& n) {
    playlistName = n;
    }

string Playlist::getName() const {
     return playlistName;
      }

// Make node in DLL
void Playlist::add_node_file(const string& title, const string& artist, int playCount) {
    Song* node = new Song(nextId++, title, artist, playCount);
    node->next = node->prev = nullptr;
    if (!head) { head = tail = node; }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

// Make copy from library and save it to playlist O(N)
void Playlist::add_from_library_copy(const Song& s) {
    add_node_file(s.title, s.artist, s.playCount);
    saveToFile();
}

// Load Playlist from File O(N)
void Playlist::loadPlaylist() {
    Song* cur = head;
    while (cur) {
    Song* t = cur->next;
     delete cur;
    cur = t;
    }

    head = tail = nullptr;
    nextId = 1;
    lastPlayedPtr = nullptr;

    ifstream fin(userFilename);
    if (!fin) {
        ofstream fout(userFilename);
        fout << "Playlist: " << playlistName << "\n0\n";
        fout.close();
        return;
    }

    string line;
    if (!getline(fin, line)) { fin.close(); return; }

    if (line.size() > 0 && startsWith(line, "Playlist:")) {
        size_t p = 0;
        for(size_t k=0; k<line.size(); k++) {
            if(line[k] == ':') { p = k; break; }
        }
        if (p != 0 && p+1 < line.size()) {
            string nm = line.substr(p+1);
            while (!nm.empty() && (nm[0] == ' ' || nm[0] == '\t')) nm.erase(0,1);
            if (!nm.empty()) playlistName = nm;
        }
    } else {
        playlistName = line;
    }

    int songCount = 0;
    if (!getline(fin, line)) { fin.close(); return; }
    songCount = stringToIntSimple(line);

    for (int i = 0; i < songCount; ++i) {
        string title, artist, playsLine;
        if (!getline(fin, title)) break;
        if (!getline(fin, artist)) break;
        if (!getline(fin, playsLine)) break;
        int plays = stringToIntSimple(playsLine);
        add_node_file(title, artist, plays);
    }
    fin.close();
    cout << "Loaded playlist for user from: " << userFilename << "\n";
}

// Save Playlist to File O(N)
void Playlist::saveToFile() {
    ofstream fout(userFilename);
    if (!fout) {
        cout << "Failed to open " << userFilename << " for writing.\n";
        return;
    }
    fout << "Playlist: " << playlistName << "\n";

    int n = 0;
     Song* cur = head;
    while (cur) {
        ++n;
     cur = cur->next;
    }
    fout << n << "\n";

    cur = head;
    while (cur) {
        fout << cur->title << "\n";
        fout << cur->artist << "\n";
        fout << cur->playCount << "\n";
        cur = cur->next;
    }
    fout.close();
}

//O(N)
void Playlist::delete_file(const string& targetTitle) {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* cur = head;

    string targetLow = toLowerStr(targetTitle);

    while (cur) {
        string titleLow = toLowerStr(cur->title);

        if (titleLow == targetLow) {
            if (cur == head)
             head = head->next;
            if (cur == tail)
             tail = tail->prev;
            if (cur->prev)
             cur->prev->next = cur->next;
            if (cur->next)
             cur->next->prev = cur->prev;

            if (cur == lastPlayedPtr)
                lastPlayedPtr = nullptr;

            cout << "Song \"" << cur->title << "\" deleted successfully.\n";
            delete cur;
            saveToFile();
            return;
        }
        cur = cur->next;
    }
    cout << "Song not found in playlist.\n";
}

// Print Playlist O(N)
void Playlist::printlist() const {
    cout << "\n=== " << playlistName << " (File: " << userFilename << ") ===\n";
    if (!head) {
    cout << "(empty)\n";
    return;
    }
    Song* cur = head;
    while (cur) {
        cout << cur->title << " | " << cur->artist << " | plays: " << cur->playCount << "\n";
        cur = cur->next;
    }
}

// Count Songs O(N)
int Playlist::countSongs() const {
    int c = 0; Song* cur = head;
    while (cur) {
    ++c;
    cur = cur->next;
     }
    return c;
}

// Play Song O(N)
Song* Playlist::play(const string& titleToPlay) {
    string inputLow = toLowerStr(titleToPlay);
    Song* cur = head;
    while (cur) {
        string titleLow = toLowerStr(cur->title);
        if (titleLow == inputLow) {
            cur->playCount++;
            lastPlayedPtr = cur;
            cout << "Now playing: " << cur->title << " - " << cur->artist << " (plays: " << cur->playCount << ")\n";
            saveToFile();
            return cur;
        }
        cur = cur->next;
    }
    cout << "Song not found in playlist.\n";
    return nullptr;
}

Song* Playlist::lastPlayed() const {
    return lastPlayedPtr;
    }
Song* Playlist::getHead() const {
    return head;
    }

//O(N²)
void Playlist::sortByPlayCount(bool descending) {
    if (!head || !head->next) {
        cout << "Not enough songs to sort.\n";
        return;
    }
    bool swapped;
    Song* ptr1;
    Song* lptr = nullptr;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {

            bool condition = false;
            if (descending) {
                if (ptr1->playCount < ptr1->next->playCount) condition = true;
            } else {
                if (ptr1->playCount > ptr1->next->playCount) condition = true;
            }

            if (condition) {
                swap(ptr1->id, ptr1->next->id);
                swap(ptr1->title, ptr1->next->title);
                swap(ptr1->artist, ptr1->next->artist);
                swap(ptr1->playCount, ptr1->next->playCount);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    string order = "asc";
    if (descending) {
        order = "desc";
    }
    cout << "Playlist sorted by playCount (" << order << ").\n";
    saveToFile();
}
