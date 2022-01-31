#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Heap {
public:
    Heap() : size(0) {}

    void push(int x, int order) {
        size++;
        if (elements.size() < size)
            elements.push_back(make_pair(x, order));
        else
            elements[size - 1] = make_pair(x, order);
        siftUp(size - 1);
    }

    void siftUp(int i) {
        while (i != 0 && elements[i] < elements[(i - 1) / 2]) {
            swap(elements[i], elements[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        while (2 * i + 1 < size) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int j = left;
            if (right < size)
                if (elements[right] < elements[left])
                    j = right;
            if (elements[i] <= elements[j])
                break;
            swap(elements[i], elements[j]);
            i = j;
        }
    }

    pair<int, int> extractMin() {
        if (size == 1) {
            size--;
            return elements[0];
        }

        pair<int, int> minima = elements[0];
        swap(elements[0], elements[size - 1]);

        size--;
        siftDown(0);
        return minima;
    }

    bool empty() {
        return size == 0;
    }

    void decKey(int id, int v) {
        for (int i = 0; i < size; i++)
            if (elements[i].second == id) {
                elements[i].first = v;
                siftUp(i);
                break;
            }
    }

private:
    vector<pair<int, int>> elements;
    int size;
};

int main() {
    string operation;
    int op_num = 0;
    Heap heap;

    while (cin >> operation) {
        op_num++;
        if (operation == "push") {
            int x;
            cin >> x;
            heap.push(x, op_num);

        } else if (operation == "extract-min") {
            if (heap.empty())
                cout << "*\n";
            else {
                pair<int, int> tmp = heap.extractMin();
                cout << tmp.first << " " << tmp.second << '\n';
            }

        } else if (operation == "decrease-key") {
            int id;
            int v;

            cin >> id >> v;
            heap.decKey(id, v);
        }
    }
    return 0;
}
