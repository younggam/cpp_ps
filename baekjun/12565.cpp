#include <cstdint>
#include <iostream>
#include <cstring>

using namespace std;

int64_t dp[2048][11];
int input[2048];
int P;

int64_t solve(int a, int b) {
    int64_t &d = dp[a][b];
    if (d >= 0) return d;
    if (a >= (1 << P) - 1) {
        d = b >= P - input[a] ? 0 : 0b100000000000000000000000000000000000000000000000000;
        return d;
    }
    d = min(input[a] + solve(2 * a + 1, b + 1) + solve(2 * a + 2, b + 1), solve(2 * a + 1, b) + solve(2 * a + 2, b));
    return d;
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d", &P);
        int M = (2 << P) - 1;
        for (int i = 0; i < M; i++) scanf("%d", &input[M - 1 - i]);
        memset(dp, -1, sizeof(dp));
        printf("Case #%d: %ld\n", t + 1, solve(0, 0));
    }

    return 0;
}
