#include <iostream>

using namespace std;

int N;

int main() {
    scanf("%d", &N);
    bool s[20] = {};
    char command[7];
    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        int x;
        if (command[0] == 'a' && command[1] == 'd') {
            scanf("%d", &x);
            s[x - 1] = true;
        } else if (command[0] == 'r') {
            scanf("%d", &x);
            s[x - 1] = false;
        } else if (command[0] == 'c') {
            scanf("%d", &x);
            printf("%d\n", s[x - 1]);
        } else if (command[0] == 't') {
            scanf("%d", &x);
            s[x - 1] = !s[x - 1];
        } else if (command[0] == 'a' && command[1] == 'l') {
            fill_n(s, 20, true);
        } else if (command[0] == 'e') {
            fill_n(s, 20, false);
        }
    }
    return 0;
}
