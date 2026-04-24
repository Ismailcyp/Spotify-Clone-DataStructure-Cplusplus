#include "BST.h"

BST::BST(): root(nullptr) {}
BST::~BST() { clear(root); }

void BST::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}
//avg. O(log N), wor. O(N)
void BST::insertIter(const Song& s) {
    Node* n = new Node(s);
    if (!root) { root = n; return; }
    Node* cur = root;
    while (true) {
        if (s.title < cur->data.title) {
            if (!cur->left) { cur->left = n; return; }
            cur = cur->left;
        } else {
            if (!cur->right) { cur->right = n; return; }
            cur = cur->right;
        }
    }
}

void BST::preorderRec(Node* n) const {
    if (!n)
        return;
    cout << n->data.title << " - " << n->data.artist << "\n";
     preorderRec(n->left);
     preorderRec(n->right);
}

void BST::inorderRec(Node* n)  const {
    if (!n)
        return;
    inorderRec(n->left);
     cout << n->data.title << " - " << n->data.artist << "\n";
     inorderRec(n->right); }

void BST::postorderRec(Node* n) const {
     if (!n)
        return;
     postorderRec(n->left);
     postorderRec(n->right);
     cout << n->data.title << " - " << n->data.artist << "\n"; }

void BST::preorder() const {
     cout << "\n--- Preorder (shuffle) ---\n";
      preorderRec(root);}

void BST::inorder()  const {
    cout << "\n--- Inorder (sorted) ---\n";
     inorderRec(root); }

void BST::postorder() const {
     cout << "\n--- Postorder (shuffle) ---\n";
      postorderRec(root); }

//copies songs from playlist(linkedlist) to BST avg. o(N logN), wor. o(N²)
void buildBSTFromPlaylist(BST& tree, const Playlist& pl) {
    Song* cur = pl.getHead();
    while (cur) {
    tree.insertIter(*cur);
    cur = cur->next;
    }
}
