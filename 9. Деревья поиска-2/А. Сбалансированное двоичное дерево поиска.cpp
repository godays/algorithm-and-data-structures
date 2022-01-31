#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    int prior;
    Node* left;
    Node* right;

    Node(int key, int prior) : key(key), prior(prior),
                               left(nullptr), right(nullptr) {}
};

void split(Node* t, int key, Node*&left, Node*&right) {
    if (!t)
        left = right = nullptr;
    else if (key < t->key) {
        split(t->left, key, left, t->left);
        right = t;
    } else {
        split(t->right, key, t->right, right);
        left = t;
    }
}

void insert(Node*&t, Node* it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior) {
        split(t, it->key, it->left, it->right);
        t = it;
    } else {
        insert(it->key < t->key ? t->left : t->right, it);
    }
}

void merge(Node*&t, Node* left, Node* right) {
    if (!left || !right)
        t = left ? left : right;
    else if (left->prior > right->prior) {
        merge(left->right, left->right, right);
        t = left;
    } else {
        merge(right->left, left, right->left);
        t = right;
    }
}

void erase(Node*&t, int key) {
    if (t->key == key)
        merge(t, t->left, t->right);
    else
        erase(key < t->key ? t->left : t->right, key);
}

bool exists(Node*& t, int x) {
    if (t == nullptr)
        return false;

    if (x == t->key)
        return true;

    if (x < t->key) {
        return exists(t->left, x);
    } else
        return exists(t->right, x);
}

Node* next(Node*& t, int x) {
    Node* cur = t;
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

Node* prev(Node*& t, int x) {
    Node* cur = t;
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string cmd;
    int x;
    int prior = 0;
    Node* root = nullptr;

    while (cin >> cmd) {
        cin >> x;
        if (cmd == "insert") {
            if (!exists(root, x)) {
                insert(root, new Node(x, prior));
                prior++;
            }
        }
        else if (cmd == "delete") {
            if (exists(root, x))
                erase(root, x);
        }
        else if (cmd == "exists")
            cout << boolalpha << exists(root, x) << '\n';
        else if (cmd == "next") {
            Node* tmp = next(root, x);
            if (tmp)
                cout << tmp->key << '\n';
            else
                cout << "none\n";
        }
        else if (cmd == "prev") {
            Node* tmp = prev(root, x);
            if (tmp)
                cout << tmp->key << '\n';
            else
                cout << "none\n";
        }
    }
    return 0;
}
