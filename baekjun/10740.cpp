#include <iostream>

using namespace std;

int d[150000][3];

int recursive(int dp[][3], const int K, const int N, int step, int map[]) {
    if (K == N) return step == 3 ? 0 : 750000;
    if (step == 3) return 750000;
    int cur = map[step];
    int &v = dp[K][cur];
    if (v != 0) return v;
    v = d[K][cur];
    v += min(recursive(dp, K + 1, N, step, map), recursive(dp, K + 1, N, step + 1, map));
    return v;
}

int solve(const int N, int left, int middle, int right) {
    int dp[150000][3] = {};
    int map[3] = {left, middle, right};
    return recursive(dp, 0, N, 0, map);
}

int main(int argc, char **argv) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &d[j][i]);
        }
    }
    int sum = min(solve(N, 0, 1, 2),
                  min(solve(N, 0, 2, 1),
                      min(solve(N, 1, 0, 2),
                          min(solve(N, 1, 2, 0),
                              min(solve(N, 2, 0, 1), solve(N, 2, 1, 0))))));

    printf("%d", sum);

    return 0;
}