#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int const WORD_MAX_LEN = 30;
int const MAX_WORD_CNT = 1e5;

class Trie {
public:
    Trie() {
        size = 1;
        isTerminal.assign(WORD_MAX_LEN, false);
    }

    void insert(string s) {
        int v = 0;
        for (int i = 0; i < s.length(); i++) {
            if (next[v][s[i]] == -1) {
                next[v][s[i]] = size;
                size += 1;
            }
            v = next[v][s[i]];
        }
        isTerminal[v] = true;
    }

    vector<int> contains(string s) {
        int v = 0;
        vector<int> res;

        for (int i = 0; i < s.length(); i++) {
            if (next[v][s[i]] == -1)
                return res;
            v = next[v][s[i]];
            if (isTerminal[v])
                res.push_back(i);
        }
        return res;
    }

    vector<unordered_map<char, int>> next;
private:
    int size;
    vector<bool> isTerminal;
};

int main() {
    string str;
    int m;

    cin >> str >> m;
    Trie trie;
    unordered_map<string, int> res;
    vector<string> words(m);

    unordered_map<char, int> ch_map;
    for (char i = 'a'; i <= 'z'; ++i)
        ch_map[i] = -1;
    trie.next.assign(MAX_WORD_CNT, ch_map);

    for (int i = 0; i < m; ++i) {
        cin >> words[i];
        trie.insert(words[i]);
    }


    int len = min(WORD_MAX_LEN, int(str.length()));

    for (int i = 0; i < str.length(); ++i) {
        string tmp = string(str.begin() + i, str.begin() + i + len);
        vector<int> possible_words = trie.contains(tmp);

        for (int j = 0; j < possible_words.size(); ++j) {
            tmp = string(str.begin() + i, str.begin() + i + possible_words[j] + 1);
            res[tmp] = 1;
        }
    }

    for (int i = 0; i < words.size(); ++i) {
        if (res.find(words[i]) != res.end())
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}
