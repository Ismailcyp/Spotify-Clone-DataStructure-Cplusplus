#include <iostream>
#include "Song.h"
#include "Library.h"
#include "Playlist.h"
#include "Users.h"
#include "RecentlyPlayed.h"
#include "SearchHistory.h"
#include "BST.h"

using namespace std;

int main() {
    Library library;
    library.loadFromFile("musics.txt");

    Playlist playlist;
    RecentlyPlayed recent(20);
    SearchHistory history;

    string currentUser = "";
    cout << "Welcome to the Music Player (login required)\n";

    while (true) {
        cout << "\n1) Login\n"
        << "2) Register\n"
        << "0) Exit\nChoose: ";

        string optStr = inputLineTrimmed();
        int opt = stringToIntSimple(optStr);

        if (opt == 0 && optStr == "0")
            return 0;

        if (opt == 2) {
            cout << "Enter new username: ";
             string u = inputLineTrimmed();
            cout << "Enter password: ";
             string p = inputLineTrimmed();

            if (u.empty() || p.empty()) {
                cout << "username/password cannot be empty\n";
                continue;
            }

            if (registerUser(u,p))
                cout << "Registered successfully. Please login.\n";
            else
            cout << "User exists or cannot register.\n";
            continue;
        }
        if (opt == 1) {
            cout << "Username: ";
             string u = inputLineTrimmed();
            cout << "Password: ";
             string p = inputLineTrimmed();

            if (loginUser(u,p)) {
                cout << "Login successful. Welcome " << u << "!\n";
                currentUser = u;
                playlist.setFilename(currentUser);
                playlist.loadPlaylist();
                break;
            } else {
                cout << "Login failed. Try again or register.\n";
            }
        }
    }

    while (true) {
        cout << "\n===== MAIN MENU <" << currentUser << "> =====\n";
        cout << "1  Create/Rename playlist\n";
        cout << "2  Add song from library to playlist (by ID)\n";
        cout << "3  Add song manually to playlist\n";
        cout << "4  Play a song (by title)\n";
        cout << "5  Display entire playlist\n";
        cout << "6  Display total number of songs in playlist\n";
        cout << "7  Shuffle playlist\n";
        cout << "8  Search song by title (ascending)\n";
        cout << "9  Search song by artist (ascending)\n";
        cout << "10 Track search history\n";
        cout << "11 Last played song\n";
        cout << "12 Sort playlist by play count\n";
        cout << "13 Reverse sort playlist by play count\n";
        cout << "14 Recently played\n";
        cout << "15 Delete song from playlist\n";
        cout << "0  Logout & Exit\n";
        cout << "Choose: ";

        string choiceStr = inputLineTrimmed();
        int choice = stringToIntSimple(choiceStr);

        if (choice == 0 && choiceStr != "0" && choiceStr != "") {
             cout << "Invalid input.\n";
             continue;
        }

        if (choice == 0) {
            cout << "Logging out. Goodbye.\n";
            break;
        }

        if (choice == 1) {
            cout << "Enter new playlist name: ";
            string pname = inputLineTrimmed();
            if (!pname.empty()) {
                playlist.setName(pname);
                playlist.saveToFile();
                cout << "Playlist name updated.\n";
            }
        }
        else if (choice == 2) {
            library.display();
            cout << "Enter library song ID to add: ";
            int id = stringToIntSimple(inputLineTrimmed());

            Song* s = library.findById(id);
            if (!s)
                cout << "Song not found in library\n";
            else {
                playlist.add_from_library_copy(*s);
                cout << "Song successfully added\n";
             }
        }
        else if (choice == 3) {
            cout << "Manual add - Title: ";
             string t = inputLineTrimmed();
            cout << "Artist: ";
             string a = inputLineTrimmed();
            cout << "Play count: ";
            int p = stringToIntSimple(inputLineTrimmed());

            library.addSongToLibrary(t, a, p);
            playlist.add_node_file(t, a, p);
            playlist.saveToFile();

            cout << "Song successfully added to Playlist AND Library.\n";
        }
        else if (choice == 4) {
            cout << "Enter title to play: ";
            string t = inputLineTrimmed();
            Song* playedSong = playlist.play(t);

            if (playedSong) {
                recent.push(*playedSong);
                library.incrementPlayCount(playedSong->title);
            }
        }
        else if (choice == 5) {
            playlist.printlist();
        }
        else if (choice == 6) {
            cout << "Total songs in playlist: " << playlist.countSongs() << "\n";
        }
        else if (choice == 7) {
            if (!playlist.getHead()) {
                cout << "Playlist empty.\n";
                continue;
            }
            cout << "Shuffle types: 1=Preorder, 2=Inorder, 3=Postorder. Choose: ";

            int t = stringToIntSimple(inputLineTrimmed());

            BST tree;
            buildBSTFromPlaylist(tree, playlist);
            if (t == 1) tree.preorder();
            else if (t == 2) tree.inorder();
            else if (t == 3) tree.postorder();
            else cout << "Unknown shuffle type.\n";
        }
        else if (choice == 8) {
            cout << "Enter title: ";
            string q = inputLineTrimmed();
            history.push(q);
            int outCount = 0;
            Song* arr = library.searchByTitleAscending(q, outCount);
            cout << "\nSearch results (ascending by title):\n";
            if (!arr) cout << "(none)\n";
            else {
                for (int i = 0; i < outCount; ++i)
                    cout << "[" << arr[i].id << "] " << arr[i].title << " - " << arr[i].artist << " (plays: " << arr[i].playCount << ")\n";
                delete[] arr;
            }
        }
        else if (choice == 9) {
            cout << "Enter artist name: ";
            string q = inputLineTrimmed();
            history.push(q);
            int outCount = 0;
            Song* arr = library.searchByArtistAscending(q, outCount);
            cout << "\nSearch results (ascending by title):\n";
            if (!arr) cout << "(none)\n";
            else {
                for (int i = 0; i < outCount; ++i)
                    cout << "[" << arr[i].id << "] " << arr[i].title << " - " << arr[i].artist << " (plays: " << arr[i].playCount << ")\n";
                delete[] arr;
            }
        }
        else if (choice == 10) {
            history.display();
        }
        else if (choice == 11) {
            Song* lp = playlist.lastPlayed();
            if (!lp) cout << "No last played song.\n";
            else cout << "Last played: " << lp->title << " - " << lp->artist << " (plays: " << lp->playCount << ")\n";
        }
        else if (choice == 12) {
            playlist.sortByPlayCount(true);
        }
        else if (choice == 13) {
            playlist.sortByPlayCount(false);
        }
        else if (choice == 14) {
            recent.display();
        }
        else if (choice == 15) {
            cout << "Enter title to delete: ";
            string t = inputLineTrimmed();
            playlist.delete_file(t);
        }
        else {
            cout << "Unknown option.\n";
        }
    }

    return 0;
}
