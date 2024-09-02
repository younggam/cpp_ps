#include <iostream>
#include <stack>

using namespace std;

int N;

int main() {
    scanf("%d", &N);
    stack<int> s;
    char command[6];
    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        if (command[0] == 'p' && command[1] == 'u') {
            int x;
            scanf("%d", &x);
            s.push(x);
        } else if (command[0] == 'p' && command[1] == 'o') {
            if (s.empty()) printf("-1\n");
            else {
                auto top = s.top();
                s.pop();
                printf("%d\n", top);
            }
        } else if (command[0] == 's') {
            printf("%d\n", s.size());
        } else if (command[0] == 'e') {
            printf("%d\n", s.empty());
        } else if (command[0] == 't') {
            printf("%d\n", s.empty() ? -1 : s.top());
        }
    }
    return 0;
}
