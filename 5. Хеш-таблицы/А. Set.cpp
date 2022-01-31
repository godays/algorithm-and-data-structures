#include <iostream>
#include <string>
#include <vector>

int const A = 7;
int const M = 1000000;
int const P = M + 15;
int const NULL_NUM = 2e9 + 1;
int const RIP_EL = -NULL_NUM;
int const MAX_INT = 1e9;

class Set {
public:
    Set() {
        elements = std::vector<int>(M, NULL_NUM);
    }

    int h_func(int x) {
        return ((A * (long long) x) % P) % M;
    }

    int next(int i) {
        return (i + 1) % M;
    }

    void insert(int x) {
        x = normalize_num(x);
        int pos = h_func(x);

        while (elements[pos] != NULL_NUM && elements[pos] != RIP_EL) {
            if (elements[pos] == x)
                return;
            pos = next(pos);
        }
        elements[pos] = x;
    }

    void del(int x) {
        x = normalize_num(x);
        int pos = h_func(x);
        int first_pos = pos;

        while (elements[pos] != x) {
            pos = next(pos);
            if (pos == first_pos)
                return;
            if (elements[pos] == NULL_NUM)
                return;
        }

        elements[pos] = RIP_EL;
    }

    bool exists(int x) {
        x = normalize_num(x);
        int pos = h_func(x);
        int first_pos = pos;

        while (elements[pos] != x) {
            pos = next(pos);
            if (pos == first_pos)
                return false;
            if (elements[pos] == NULL_NUM)
                return false;
        }
        return true;
    }

    int normalize_num(int x) {
        return x + MAX_INT;
    }

private:
    std::vector<int> elements;
};

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Set set;
    string command;

    while (cin >> command) {
        int x;
        cin >> x;

        if (command == "insert")
            set.insert(x);
        else if (command == "delete")
            set.del(x);
        else if (command == "exists")
            if (set.exists(x))
                cout << "true\n";
            else
                cout << "false\n";
    }
    return 0;
}
