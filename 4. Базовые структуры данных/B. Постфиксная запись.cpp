#include <iostream>

class Vector {
public:
    Vector() : elements(0), size(0), capacity(2) {
        elements = new int[capacity];
    }

    int get(int i) {
        if (i < 0 | i >= size) {
            throw std::runtime_error("index out of range");
        }
        return elements[i];
    }

    void add(int x) {
        if (size + 1 > capacity)
            ensureCapacity();
        elements[size] = x;
        size++;
    }

    void ensureCapacity() {
        capacity *= 2;
        int* newElements = new int[capacity];

        for (int i = 0; i < size; i++)
            newElements[i] = elements[i];

        delete elements;
        elements = newElements;
    }

    void decreaseCapacity() {
        capacity /= 2;
        int* newElements = new int[capacity];

        for (int i = 0; i < size; i++)
            newElements[i] = elements[i];

        delete elements;
        elements = newElements;
    }

    void erase_last() {
        if (size - 1 < capacity / 4)
            decreaseCapacity();

        size--;
    }

    int back() {
        return get(size - 1);
    }

private:
    int size;
    int capacity;
    int* elements;
};

class Stack {
public:
    Stack() {}

    void push(int x) {
        vec.add(x);
    }

    void pop() {
        vec.erase_last();
    }

    int top() {
        return vec.back();
    }

    int pop_back() {
        int top_el = top();
        pop();
        return top_el;
    }

private:
    Vector vec;
};

int apply_operation(int a, int b, char op) {
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
}

using namespace std;

int main() {
    char cur_char;
    Stack st;
    while (cin >> cur_char) {
        if (cur_char <= '9' & cur_char >= '0')
            st.push(cur_char - '0');

        else {
            int first_el = st.pop_back();
            int second_el = st.pop_back();
            st.push(apply_operation(second_el, first_el, cur_char));
        }
    }
    cout << st.top();
    return 0;
}
