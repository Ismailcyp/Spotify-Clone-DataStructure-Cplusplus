#ifndef BST_H
#define BST_H

#include "Song.h"
#include "Playlist.h"

class BST {
    struct Node {
        Song data;
        Node* left;
        Node* right;
        Node(const Song& s): data(s), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void clear(Node* n);
    void preorderRec(Node* n) const;
    void inorderRec(Node* n) const;
    void postorderRec(Node* n) const;

public:
    BST();
    ~BST();
    void insertIter(const Song& s);
    void preorder() const;
    void inorder() const;
    void postorder() const;
};

void buildBSTFromPlaylist(BST& tree, const Playlist& pl);

#endif
