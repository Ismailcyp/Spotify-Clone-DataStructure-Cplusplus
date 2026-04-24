#include "SearchHistory.h"

SearchHistory::SearchHistory(): top(nullptr) {}

SearchHistory::~SearchHistory() {
    while (top) {
    Node* t = top->next;
    delete top;
    top = t;
    }
}

void SearchHistory::push(const string& s) {
    Node* n = new Node(s);
    n->next = top;
    top = n;
}
// display search history from top to buttom O(N)
void SearchHistory::display() const {
    cout << "\n--- Search history ---\n";
    Node* cur = top;

    if (!cur) {
        cout << "(empty)\n";
        return;
        }

    while (cur) {
        cout << cur->data << "\n";
        cur = cur->next;
        }
}
