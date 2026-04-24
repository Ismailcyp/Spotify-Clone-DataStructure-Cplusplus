#include "Library.h"
#include <fstream>
#include <iostream>

using namespace std;

extern int stringToIntSimple(const string& s);
extern string toLowerStr(string s);

Library::Library(): head(nullptr), lastId(0) {}

Library::~Library() {
    clear();
}

// Clear memory
void Library::clear() {
    Node* cur = head;
    while (cur) {
        Node* t = cur->next;
        delete cur;
        cur = t;
    }
    head = nullptr;
}

// rewrites over the old musics.txt after changing spectifc things,playcount,adding new song o(n)
void Library::saveLibraryToFile(string filename) {
    ofstream fout(filename);
    Node* cur = head;
    while (cur) {
        fout << cur->data.title << "\n";
        fout << cur->data.artist << "\n";
        fout << cur->data.playCount << "\n";
        cur = cur->next;
    }
    fout.close();
}

// read file o(n)
void Library::loadFromFile(string filename) {
    clear();
    lastId = 0;
    ifstream fin(filename);
    string title, artist, playsLine;
    while (getline(fin, title)) {
        if (!getline(fin, artist)) break;
        if (!getline(fin, playsLine)) break;

        int plays = stringToIntSimple(playsLine);

        lastId++;
        Song s(lastId, title, artist, plays);
        Node* n = new Node(s);
        n->next = head;
        head = n;
    }
    fin.close();
}

void Library::addSongToLibrary(const string& t, const string& a, int p) {
    lastId++;
    Song s(lastId, t, a, p);
    Node* n = new Node(s);
    n->next = head;
    head = n;
    saveLibraryToFile("musics.txt");
}
//inc playcount & save changes
void Library::incrementPlayCount(string title) {
    string titleLow = toLowerStr(title);

    Node* cur = head;
    while (cur) {
        if (toLowerStr(cur->data.title) == titleLow) {
            cur->data.playCount++;
            saveLibraryToFile("musics.txt");
            return;
        }
        cur = cur->next;
    }
}
// display song by copying the nodes to dyn. arr , sorting songs by id o(N²)
void Library::display() const {
    cout << "\n--- Library (available songs) ---\n";
    Node* cur = head;
    if (!cur) {
    cout << "(empty)\n";
    return;
    }

    int count = 0;
    Node* tmp = head;
    while(tmp){
    count++;
    tmp = tmp->next;
    }

    Song* arr = new Song[count];
    tmp = head;
    int idx = 0;
    while (tmp) {
        arr[idx++] = tmp->data;
        tmp = tmp->next;
    }


    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (arr[i].id > arr[j].id) {
                Song t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }

    for (int i = 0; i < count; ++i) {
        cout << "[" << arr[i].id << "] " << arr[i].title << " - " << arr[i].artist
             << " (plays: " << arr[i].playCount << ")\n";
    }
    delete[] arr;
}
//o(n)
Song* Library::findById(int id) {
    Node* cur = head;
    while (cur) {
        if (cur->data.id == id)
            return &cur->data;
        cur = cur->next;
    }
    return nullptr;
}

// search title, artist by comp. io in L.C. inc count & add to dyn. arr & sort result
Song* Library::searchByTitleAscending(const string& key, int& outCount) {
    outCount = 0;
    string keyLow = toLowerStr(key);

    Node* cur = head;
    while (cur) {
        string titleLow = toLowerStr(cur->data.title);

        if (startsWith(titleLow, keyLow)) {
            outCount++;
        }
        cur = cur->next;
    }

    if (outCount == 0)
        return nullptr;

    Song* arr = new Song[outCount];
    cur = head;
    int idx = 0;
    while (cur) {
        string titleLow = toLowerStr(cur->data.title);

        if (startsWith(titleLow, keyLow)) {
            arr[idx++] = cur->data;
        }
        cur = cur->next;
    }

    for (int i = 0; i < outCount - 1; i++) {
            for (int j = i + 1; j < outCount; j++) {
                if (arr[i].title > arr[j].title) {
                    Song t = arr[i];
                    arr[i] = arr[j];
                    arr[j] = t;
                }
            }
        }
    return arr;
}

Song* Library::searchByArtistAscending(const string& key, int& outCount) {
    outCount = 0;
    string keyLow = toLowerStr(key);

    Node* cur = head;
    while (cur) {
        string artistLow = toLowerStr(cur->data.artist);

        if (startsWith(artistLow, keyLow)) {
            outCount++;
        }
        cur = cur->next;
    }

    if (outCount == 0) return nullptr;

    Song* arr = new Song[outCount];
    cur = head;
    int idx = 0;
    while (cur) {
        string artistLow = toLowerStr(cur->data.artist);

        if (startsWith(artistLow, keyLow)) {
            arr[idx++] = cur->data;
        }
        cur = cur->next;
    }

    for (int i = 0; i < outCount - 1; i++) {
            for (int j = i + 1; j < outCount; j++) {
                if (arr[i].title > arr[j].title) {
                    Song t = arr[i];
                    arr[i] = arr[j];
                    arr[j] = t;
                }
            }
        }
    return arr;
}
