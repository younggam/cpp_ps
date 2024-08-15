#include <iostream>
#include <climits>
#include <cstring>

using namespace std;

int cost[500];
int sums[501] = {};
int dp[500][500] = {};
int K;

int solve(int left, int right) {
    int &v = dp[left][right];
    if (v > 0) return v;
    if (left == right) return v = cost[left];
    v = INT_MAX;
    for (int i = left; i < right; i++) {
        v = min(v, solve(left, i) + solve(i + 1, right));
    }
    v += sums[right + 1] - sums[left];
    return v;
}

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            scanf("%d", &cost[i]);
            sums[i + 1] = sums[i] + cost[i];
        }
        memset(dp, 0, sizeof(dp));
        int answer = INT_MAX;
        for (int i = 0; i < K - 1; i++) {
            answer = min(answer, solve(0, i) + solve(i + 1, K - 1));
        }
        printf("%d\n", answer);
    }

    return 0;
}
