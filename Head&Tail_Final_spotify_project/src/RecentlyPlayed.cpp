#include "RecentlyPlayed.h"

RecentlyPlayed::RecentlyPlayed(int mx): head(nullptr), size(0), maxSize(mx) {}

RecentlyPlayed::~RecentlyPlayed() {
    Node* cur = head;
    while (cur) {
        Node* t = cur->next;
        delete cur;
        cur = t;
         }
}
//o(n)
void RecentlyPlayed::push(const Song& s) {
    Node* n = new Node(s);
    n->next = head;
    head = n;
    size++;

    if (size > maxSize) {
        Node* cur = head;
        while (cur->next && cur->next->next)
            cur = cur->next;
        if (cur->next) {
             delete cur->next;
             cur->next = nullptr;
        }
        size = maxSize;
    }
}
//o(n)
void RecentlyPlayed::display() const {
    cout << "\n--- Recently played (most recent first) ---\n";
    Node* cur = head;
    if (!cur) {
        cout << "(empty)\n";
        return;
        }
    while (cur) {
        cout << cur->data.title << " - " << cur->data.artist << " (plays: " << cur->data.playCount << ")\n";
        cur = cur->next;
    }
}
