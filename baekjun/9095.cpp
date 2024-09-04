#include <iostream>

using namespace std;

int T, N;

int solve(int i, int streak) {
    if (i == N) return 1;
    if (streak >= 2) return solve(i + 1, 0);
    return solve(i + 1, 0) + solve(i + 1, streak + 1);
}

int main() {
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d", &N);
        printf("%d\n", solve(1, 0));
    }
    return 0;
}
