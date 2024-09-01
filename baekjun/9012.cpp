#include <iostream>
#include <stack>

using namespace std;

int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char PS[51] = {};
        scanf("%s", PS);
        int j = 0;
        stack<bool> s = {};
        bool good = true;
        while (PS[j] != '\0') {
            if (PS[j] == '(') s.push(true);
            else if (PS[j] == ')') {
                if (s.empty()) {
                    good = false;
                    break;
                }
                s.pop();
            }
            j++;
        }
        good &= s.empty();
        printf(good ? "YES\n" : "NO\n");
    }

    return 0;
}
