#include <iostream>
#include <utility>

using namespace std;

struct Node {
    Node(int x) : data(x), next(nullptr) {}

    Node(int x, int new_min) : data(x), cur_min(new_min), next(nullptr) {}

    int data;
    int cur_min;
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr), size(0) {}

    bool empty() {
        return head == nullptr;
    }

    void push_front(int x, int cur_min) {
        size++;
        Node* newNode = new Node(x, cur_min);

        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    void remove_first() {
        if (size == 1) {
            head = nullptr;
        } else {
            Node* cur = head;
            head = cur->next;
            delete cur;
        }
    }

    Node* front() {
        return head;
    }

private:
    Node* head;
    Node* tail;
    int size;
};

class stack {
public:
    void push(int x) {
        int cur_min;
        if (list.empty())
            cur_min = x;
        else
            cur_min = min(x, list.front()->cur_min);

        list.push_front(x, cur_min);
    }

    void pop() {
        list.remove_first();
    }

    Node* top() {
        return list.front();
    }

    int getMin() {
        return top()->cur_min;
    }

private:
    LinkedList list;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    stack st;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int operation;
        int x;
        cin >> operation;

        if (operation == 1) {
            cin >> x;
            st.push(x);
        } else if (operation == 2)
            st.pop();
        else
            cout << st.getMin() << '\n';
    }
    return 0;
}
