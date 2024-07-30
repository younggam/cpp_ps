#include <cmath>
#include <iostream>
#include <deque>

using namespace std;

bool solve(deque<char> &S, deque<char> &E) {
    bool ret = true;
    bool flip = false;
    while (S.size() != E.size()) {
        char popped;
        if (flip) {
            popped = E.front();
            E.pop_front();
        } else {
            popped = E.back();
            E.pop_back();
        }
        if (popped == 'Y') flip = !flip;
    }
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != E[flip ? E.size() - 1 - i : i]) {
            ret = false;
            break;
        }
    }
    return ret;
}


int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    cin >> noskipws;
    char c;
    cin >> c;
    for (int i = 0; i < T; i++) {
        deque<char> S, E;
        int xs = 0, ys = 0;
        while (cin >> c) {
            if (isspace(c)) break;
            S.push_back(c);
        }
        while (cin >> c) {
            if (isspace(c)) break;
            E.push_back(c);
        }
        cout << '#' << t << ' ' << (solve(S, E) ? "Yes" : "No") << endl;
        t++;
    }
    return 0;
}
