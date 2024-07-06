#include <cmath>
#include <iostream>
#include <deque>

using namespace std;

void solve(deque<char> &S, deque<char> &E, bool flip, bool &result) {
    if (result) {
    } else if (S.size() != E.size()) {
        char front = E.front();
        char back = E.back();
        if (flip) {
            char temp = front;
            front = back;
            back = temp;
        }

        if (front != 'X' || back != 'Y') {
            if (back == 'X') {
                if (flip) E.pop_front();
                else E.pop_back();
                solve(S, E, flip, result);
                if (flip) E.push_front('X');
                else E.push_back('X');
            }
            if (front == 'Y') {
                if (flip) E.pop_back();
                else E.pop_front();
                solve(S, E, !flip, result);
                if (flip) E.push_back('Y');
                else E.push_front('Y');
            }
        }
    } else {
        result = true;
        for (int i = 0; i < S.size(); i++) {
            if (S[i] != E[flip ? E.size() - 1 - i : i]) {
                result = false;
                break;
            }
        }
    }
}


int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    cin >> noskipws;
    char c;
    cin >> c;
    for (int i = 0; i < T; i++) {
        deque<char> S, E;
        while (cin >> c) {
            if (isspace(c)) break;
            S.push_back(c);
        }
        while (cin >> c) {
            if (isspace(c)) break;
            E.push_back(c);
        }
        bool r = false;
        solve(S, E, false, r);
        cout << '#' << t << ' ' << (r ? "Yes" : "No") << endl;
        t++;
    }
    return 0;
}
