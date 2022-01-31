#include <iostream>

struct Node {
    int value;
    int h;
    int size;
    Node* left;
    Node* right;

    Node(int value, int h = 1) {
        this->value = value;
        this->h = h;
        size = 1;
        left = nullptr;
        right = nullptr;
    }
};

Node* root;

int h_get(Node* v) {
    return v == nullptr ? 0 : v->h;
}

int h_diff(Node* v) {
    return h_get(v->right) - h_get(v->left);
}

void h_upd(Node* v) {
    v->h = std::max(h_get(v->left), h_get(v->right)) + 1;
}

void size_upd(Node* v) {
    v->size = (v->left == nullptr ? 0 : v->left->size) + (v->right == nullptr ? 0 : v->right->size) + 1;
}

int size(Node* v) {
    return v == nullptr ? 0 : v->size;
}

Node* rotate(Node* a, char how) {
    Node* b;
    if (how == 'l') {
        b = a->right;
        a->right = b->left;
        b->left = a;
    } else {
        b = a->left;
        a->left = b->right;
        b->right = a;
    }
    h_upd(a);
    h_upd(b);

    size_upd(a);
    size_upd(b);
    return b;
}

Node* balance(Node* v) {
    if (v == nullptr)
        return v;
    h_upd(v);
    size_upd(v);
    if (h_diff(v) <= -2) {
        if (h_diff(v->left) >= 1) {
            v->left = rotate(v->left, 'l');
        }
        return rotate(v, 'r');
    } else if (h_diff(v) >= 2) {
        if (h_diff(v->right) <= -1) {
            v->right = rotate(v->right, 'r');
        }
        return rotate(v, 'l');
    }
    return v;
}

Node* insert(int x, Node* v) {
    if (v == nullptr) {
        return new Node(x);
    } else if (x < v->value) {
        v->left = insert(x, v->left);
    } else if (x > v->value) {
        v->right = insert(x, v->right);
    }
    return balance(v);
}

Node* min(Node* v) {
    if (v->left == nullptr)
        return v;
    return min(v->left);
}

Node* next(int x, Node* v, Node* min = nullptr) {
    if (v == nullptr) return min;
    if (v->value > x) return next(x, v->left, v);
    else return next(x, v->right, min);
}


Node* remove(int x, Node* v) {
    if (v == nullptr)
        return v;
    if (x < v->value) {
        v->left = remove(x, v->left);
    } else if (x > v->value) {
        v->right = remove(x, v->right);
    } else if (v->left != nullptr && v->right != nullptr) {
        v->value = next(v->value, root)->value;
        v->right = remove(v->value, v->right);
    } else {
        if (v->left != nullptr) {
            v = v->left;
        } else if (v->right != nullptr) {
            v = v->right;
        } else {
            v = nullptr;
        }
    }
    return balance(v);
}

Node* kth_max(int k, Node* v) {
    if (size(v->right) == k)
        return v;
    if (size(v->right) > k)
        return kth_max(k, v->right);
    return kth_max(k - size(v->right) - 1, v->left);
}

using namespace std;

int main() {
    int n;
    int x;
    int cmd;
    root = nullptr;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cmd >> x;

        if (cmd == 1) {
            root = insert(x, root);
        } else if (cmd == -1) {
            root = remove(x, root);
        } else if (cmd == 0) {
            x--;
            cout << kth_max(x, root)->value << '\n';
        }
    }
    return 0;
}
