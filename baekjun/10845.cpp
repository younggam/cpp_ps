#include <iostream>
#include <queue>

using namespace std;

int N;

int main() {
    scanf("%d", &N);
    queue<int> q;
    char command[6];
    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        if (command[0] == 'p' && command[1] == 'u') {
            int x;
            scanf("%d", &x);
            q.push(x);
        } else if (command[0] == 'p' && command[1] == 'o') {
            if (q.empty()) printf("-1\n");
            else {
                auto top = q.front();
                q.pop();
                printf("%d\n", top);
            }
        } else if (command[0] == 's') {
            printf("%d\n", q.size());
        } else if (command[0] == 'e') {
            printf("%d\n", q.empty());
        } else if (command[0] == 'f') {
            printf("%d\n", q.empty() ? -1 : q.front());
        } else if (command[0] == 'b') {
            printf("%d\n", q.empty() ? -1 : q.back());
        }
    }
    return 0;
}
