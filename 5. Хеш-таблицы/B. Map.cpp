#include <iostream>
#include <string>
#include <vector>

int const A = 7;
int const M = 100000;
int const P = 1e8;

using namespace std;

struct Node {
    Node(pair<string, string> x) : data(x), next(nullptr) {}

    pair<string, string> data;
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr), size(0) {}

    bool empty() {
        return head == nullptr;
    }

    void push_back(pair<string, string> x) {
        size++;
        Node* newNode = new Node(x);

        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void erase(string x) {
        if (empty())
            return;

        Node* newNode = head;

        if (newNode->data.first == x) {
            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                delete head;
                head = newNode->next;
            }
            size--;
            return;
        }
        else {
            Node* prev = head;
            Node* cur = prev->next;

            while (cur && cur->data.first != x) {
                prev = cur;
                cur = prev->next;
            }
            if (cur == nullptr)
                return;
            else {
                prev->next = cur->next;
                if (cur == tail)
                    tail = prev;
                size--;
            }
        }
    }

    void push_replace(pair<string, string> x) {
        Node* tmp = head;
        while (tmp) {
            if (tmp->data.first == x.first) {
                tmp->data.second = x.second;
                return;
            }
            tmp = tmp->next;
        }
        push_back(x);
    }

    string get(string x) {
        Node* tmp = head;
        while (tmp) {
            if (tmp->data.first == x) {
                return tmp->data.second;
            }
            tmp = tmp->next;
        }
        return "none";
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
    }

    int h_func(string s) {
        int len = s.size();
        int res = 0;

        for (int i = 0; i < len; ++i) {
            res = (res * A + s[i]) % P;
        }
        return res % M;
    }

    void put(string x, string y) {
        int x_ind = h_func(x);
        elements[x_ind].push_replace(make_pair(x, y));
    }

    void del(string x) {
        int x_ind = h_func(x);
        elements[x_ind].erase(x);
    }

    string get(string x) {
        int x_ind = h_func(x);
        return elements[x_ind].get(x);
    }


private:
    vector<LinkedList> elements;
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
        }
    }
    return 0;
}
