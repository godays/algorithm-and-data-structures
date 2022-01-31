#include <iostream>
#include <string>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int x) {
        key = x;
        left = right = nullptr;
        height = 1;
    }
};

Node* root;

int height(Node* v) {
    return v ? v->height : 0;
}

int bfactor(Node* v) {
    return height(v->right) - height(v->left);
}

void fixheghit(Node* v) {
    int hl = height(v->left);
    int hr = height(v->right);
    v->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheghit(p);
    fixheghit(q);
    return q;
}

Node* rotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheghit(q);
    fixheghit(p);
    return p;
}

Node* balance(Node* p) {
    fixheghit(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

Node* insert(Node* p, int x) {
    if (!p)
        return new Node(x);
    if (p->key == x)
        return p;
    if (x < p->key)
        p->left = insert(p->left, x);
    else
        p->right = insert(p->right, x);
    return balance(p);
}

Node* findMin(Node* p) {
    return p->left ? findMin(p->left) : p;
}

Node* removeMin(Node* p) {
    if (p->left == nullptr)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

Node* remove(Node* p, int x) {
    if (!p)
        return nullptr;
    if (x < p->key)
        p->left = remove(p->left, x);
    else if (x > p->key)
        p->right = remove(p->right, x);
    else {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r)
            return q;
        Node* min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

Node* search(Node* v, int x) {
    if (v == nullptr)
        return nullptr;
    if (v->key == x)
        return v;
    else if (x < v->key)
        return search(v->left, x);
    else
        return search(v->right, x);
}

bool exists(Node* v, int x) {
    if (search(v, x) != nullptr)
        return true;
    return false;
}

Node* next(int x) {
    Node* cur = root;
    Node* res = nullptr;

    while (cur != nullptr) {
        if (cur->key > x) {
            res = cur;
            cur = cur->left;
        } else
            cur = cur->right;
    }
    return res;
}

Node* prev(int x) {
    Node* cur = root;
    Node* res = nullptr;

    while (cur != nullptr) {
        if (cur->key < x) {
            res = cur;
            cur = cur->right;
        } else
            cur = cur->left;
    }
    return res;
}

using namespace std;

int main() {
    string cmd;
    int x;
    Node* v;
    root = nullptr;

    while (cin >> cmd) {
        cin >> x;

        if (cmd == "insert") {
            root = insert(root, x);
        } else if (cmd == "exists") {
            if (exists(root, x))
                cout << "true\n";
            else
                cout << "false\n";
        } else if (cmd == "delete") {
            root = remove(root, x);
        } else if (cmd == "next") {
            v = next(x);
            if (v == nullptr)
                cout << "none\n";
            else
                cout << v->key << '\n';
        } else if (cmd == "prev") {
            v = prev(x);
            if (v == nullptr)
                cout << "none\n";
            else
                cout << v->key << '\n';
        }
    }
    return 0;
}
