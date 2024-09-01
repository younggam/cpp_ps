#include <iostream>
#include <set>

using namespace std;

struct MyCmp {
    bool operator ()(const string &a, const string &b) const {
        return a.length() < b.length() || (a.length() == b.length() && a < b);
    }
};

int N;

set<string, MyCmp> words;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char word[50] = {};
        scanf("%s", word);
        words.emplace(word);
    }

    for (auto &word: words) printf("%s\n", word.c_str());
    return 0;
}
