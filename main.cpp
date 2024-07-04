#include <cmath>
#include <iostream>
// #include <fstream>
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
    // ifstream cin("../sample_input.txt");
    // ifstream answer("../sample_output.txt");

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
            if (c == 'X') xs--;
            else ys--;
        }
        while (cin >> c) {
            if (isspace(c)) break;
            E.push_back(c);
            if (c == 'X') xs++;
            else ys++;
        }
        cout << '#' << t << ' ' << (solve(S, E) ? "Yes" : "No") << endl;

        // string result = solve(S, E) ? "Yes" : "No";
        // string a;
        // string skip;
        // answer >> a;
        // if (result == a) cout << "success" << endl;
        // else cout << a << " != " << result << endl;
        t++;
    }
    return 0;
}
