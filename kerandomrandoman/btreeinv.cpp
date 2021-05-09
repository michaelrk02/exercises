// Google: 90% of our engineers use the software you wrote (Homebrew), but you
// can't invert a binary tree on a whiteboard so f**k off
//  - Max Howell
#include <iostream>

using namespace std;

struct BSTNode;
struct BSTNode {
    int value;
    BSTNode *left, *right;
};

void BSTInsert(BSTNode **node, int value) {
    if (*node == NULL) {
        *node = new BSTNode;
        (*node)->value = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }
    if (value < (*node)->value) {
        BSTInsert(&(*node)->left, value);
        return;
    }
    if (value > (*node)->value) {
        BSTInsert(&(*node)->right, value);
        return;
    }
}

void BSTPrint(BSTNode *node, int depth = 0) {
    if (depth == 0) {
        cout << "Contents: ";
    }
    if (node != NULL) {
        BSTPrint(node->left, depth + 1);
        cout << node->value << ' ';
        BSTPrint(node->right, depth + 1);
    }
    if (depth == 0) {
        cout << endl;
    }
}

void BSTInvert(BSTNode *node) {
    if (node != NULL) {
        BSTNode *temp = node->right;
        node->right = node->left;
        node->left = temp;
        BSTInvert(node->left);
        BSTInvert(node->right);
    }
}

int main() {
    BSTNode *tree = NULL;;

    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        BSTInsert(&tree, data[i]);
    }

    cout << "Original:" << endl;
    BSTPrint(tree);
    cout << endl;

    BSTInvert(tree);

    cout << "Inverted:" << endl;
    BSTPrint(tree);
    cout << endl;

    return 0;
}

