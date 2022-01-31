#include <iostream>
#include <string>
#include <vector>

int const A = 7;
int const M = 100000;
int const P = 1e6;

using namespace std;

struct Node {
    Node(pair<string, string> x) : data(x), next(nullptr), prev_el(nullptr), next_el(nullptr) {}

    pair<string, string> data;
    Node* prev_el;
    Node* next_el;
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    bool empty() {
        return head == nullptr;
    }

    void push_back(Node* newNode) {
        size++;

        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void repoint(Node* node) {
        Node* prev = node->prev_el;
        Node* next = node->next_el;

        if (prev == nullptr && next == nullptr)
            return;
        if (prev == nullptr)
            next->prev_el = nullptr;
        else if (next == nullptr)
            prev->next_el = nullptr;
        else {
            prev->next_el = next;
            next->prev_el = prev;
        }
    }

    Node* erase(string x) {
        if (empty())
            return nullptr;

        Node* newNode = head;

        if (newNode->data.first == x) {
            repoint(newNode);
            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            } else {
                head = newNode->next;
            }
            size--;
            return newNode;
        } else {
            Node* prev = head;
            Node* cur = prev->next;

            while (cur != nullptr && cur->data.first != x) {
                prev = cur;
                cur = prev->next;
            }
            if (cur == nullptr)
                return nullptr;
            else {
                repoint(cur);
                prev->next = cur->next;
                if (cur == tail)
                    tail = prev;
                size--;
                return cur;
            }
        }
    }

    void replace(Node* x) {
        Node* tmp = head;
        while (tmp != nullptr) {
            if (tmp->data.first == x->data.first) {
                tmp->data.second = x->data.second;
                return;
            }
            tmp = tmp->next;
        }
    }

    bool exists(Node* x) {
        Node* tmp = head;
        while (tmp != nullptr) {
            if (tmp->data.first == x->data.first)
                return true;
            tmp = tmp->next;
        }
        return false;
    }

    Node* get(string x) {
        Node* tmp = head;

        while (tmp != nullptr) {
            if (tmp->data.first == x) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

private:
    Node* head;
    Node* tail;
    int size;
};

class Map {
public:
    Map() {
        elements = vector<LinkedList>(M);
        last_el = nullptr;
    }

    int h_func(string s) {
        int len = s.size();
        int res = 0;

        for (int i = 0; i < len; i++) {
            res = (res * A + s[i]) % P;
        }
        return res % M;
    }

    void put(string x, string y) {
        Node* newNode = new Node(make_pair(x, y));

        int x_ind = h_func(x);

        if (elements[x_ind].exists(newNode)) {
            elements[x_ind].replace(newNode);
        } else {
            if (last_el != nullptr) {
                newNode->prev_el = last_el;
                last_el->next_el = newNode;
                last_el = newNode;
                elements[x_ind].push_back(newNode);
            } else {
                last_el = newNode;
                elements[x_ind].push_back(newNode);
            }
        }

    }

    void del(string x) {
        int x_ind = h_func(x);
        Node* erased = elements[x_ind].erase(x);
        if (erased != nullptr)
            if (erased->data.first == last_el->data.first)
                last_el = last_el->prev_el;
    }

    string get(string x) {
        Node* tmp = get_node(x);
        return data_to_res(tmp);
    }

    Node* get_node(string x) {
        int x_ind = h_func(x);
        return elements[x_ind].get(x);
    }

    string next(string x) {
        Node* tmp = get_node(x);
        if (tmp) {
            tmp = tmp->next_el;
            return data_to_res(tmp);
        }
        return "none";
    }

    string prev(string x) {
        Node* tmp = get_node(x);
        if (tmp) {
            tmp = tmp->prev_el;
            return data_to_res(tmp);
        }
        return "none";
    }

    string data_to_res(Node* node) {
        if (node) {
            return node->data.second;
        } else
            return "none";
    }

private:
    vector<LinkedList> elements;
    Node* last_el;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Map map;
    string command;

    while (cin >> command) {
        if (command == "put") {
            string x, y;
            cin >> x >> y;
            map.put(x, y);
        } else if (command == "delete") {
            string x;
            cin >> x;
            map.del(x);
        } else if (command == "get") {
            string x;
            cin >> x;
            cout << map.get(x) << '\n';
        } else if (command == "next") {
            string x;
            cin >> x;
            cout << map.next(x) << '\n';
        } else if (command == "prev") {
            string x;
            cin >> x;
            cout << map.prev(x) << '\n';
        }
    }
    return 0;
}