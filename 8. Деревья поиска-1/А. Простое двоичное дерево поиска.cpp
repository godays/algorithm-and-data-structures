#include <iostream>
#include <string>

using namespace std;

struct Node {
    Node(int x) {
        key = x;
        left = nullptr;
        right = nullptr;
    }

    int key;
    Node* left;
    Node* right;
};

Node* ROOT;

Node* insert(Node* v, int x) {
    if (v == nullptr)
        return new Node(x);
    else if (x < v->key)
        v->left = insert(v->left, x);
    else if (x > v->key)
        v->right = insert(v->right, x);
    return v;
}

Node* findMin(Node* v) {
    if (v->left == nullptr)
        return v;
    return findMin(v->left);
}

Node* del(Node* v, int x) {
    if (v == nullptr)
        return v;
    if (x < v->key)
        v->left = del(v->left, x);
    else if (x > v->key)
        v->right = del(v->right, x);
    else if (v->left != nullptr && v->right != nullptr) {
        v->key = findMin(v->right)->key;
        v->right = del(v->right, v->key);
    } else {
        if (v->left != nullptr) {
            v = v->left;
        } else if (v->right != nullptr) {
            v = v->right;
        } else {
            delete v;
            v = nullptr;
        }
    }
    return v;
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
    Node* cur = ROOT;
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
    Node* cur = ROOT;
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

int main() {
    string cmd;
    int x;
    Node* v;
    ROOT = nullptr;

    while (cin >> cmd) {
        cin >> x;

        if (cmd == "insert") {
            ROOT = insert(ROOT, x);
        } else if (cmd == "exists") {
            if (exists(ROOT, x))
                cout << "true\n";
            else
                cout << "false\n";
        } else if (cmd == "delete") {
            ROOT = del(ROOT, x);
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
