#include <iostream>

using namespace std;

class Vector {
public:
    Vector() : begin(-1), end(-1), capacity(2) {
        elements = new int[capacity];
    }

    int get(int i) {
        if (i < 0 || i >= size())
            return NULL;
        return elements[(begin + i) % capacity];
    }

    bool isFull() {
        if (begin == 0 && end == capacity - 1)
            return true;
        if (begin == end + 1)
            return true;
        if (size() + 1 > capacity)
            return true;

        return false;
    }

    void add(int x) {
        if (isFull())
            ensureCapacity();

        if (begin == -1) begin = 0;
        end = next(end);
        elements[end] = x;
    }

    int* copyElements(int newElements[]) {
        int i = begin;
        int new_i = 0;

        while (i != end) {
            newElements[new_i] = elements[i];
            i = next(i);
            new_i++;
        }
        newElements[new_i] = elements[i];

        begin = 0;
        end = new_i;
        return newElements;
    }

    void ensureCapacity() {
        int* newElements = new int[capacity * 2];
        newElements = copyElements(newElements);

        delete elements;
        capacity *= 2;
        elements = newElements;
    }

    void decreaseCapacity() {
        int* newElements = new int[capacity / 2];
        newElements = copyElements(newElements);

        delete elements;
        capacity /= 2;
        elements = newElements;
    }

    void pop() {
        if (size() - 1 < capacity / 4 && capacity > 2)
            decreaseCapacity();

        if (begin == end) {
            begin = -1;
            end = -1;
        }

        if (size() != 0) {
            begin = next(begin);
        }
    }

    int front() {
        return elements[begin];
    }

    int next(int i) {
        return (i + 1) % capacity;
    }

    int size() {
        return (end + capacity - begin) % capacity;
    }

private:
    int* elements;
    int begin;
    int end;
    int capacity;
};

class Queue {
public:
    Queue() {}

    void push(int x) {
        vec.add(x);
    }

    void pop() {
        vec.pop();
    }

    int popBack() {
        int top;
        top = vec.front();
        pop();
        return top;
    }

private:
    Vector vec;
};

int main() {
    Queue queue;
    int n;
    char operation;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> operation;
        if (operation == '+') {
            int x;
            cin >> x;
            queue.push(x);
        } else
            cout << queue.popBack() << '\n';
    }

    return 0;
}

