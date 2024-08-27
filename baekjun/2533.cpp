#include <iostream>
#include <vector>

using namespace std;

struct Node {
    vector<int> edges;
};

int N;
Node nodes[1000000];
int dp[2000000];

int solve(int p, int i, bool not_early_streak) {
    int v0 = dp[i * 2];
    int v1 = dp[i * 2 + 1];
    if (v0 >= 0 || v1 >= 0) {
        if (not_early_streak) return v0;
        v0 = v0 < 0 ? 1000000 : v0;
        v1 = v1 < 0 ? 1000000 : v1;
        return min(v0, v1);
    }
    Node node = nodes[i];
    int a = 1;
    for (auto edge: node.edges) {
        if (edge != p) a += solve(i, edge, false);
    }
    dp[i * 2] = a;
    if (!not_early_streak) {
        int b = 0;
        for (auto edge: node.edges) {
            if (edge != p) b += solve(i, edge, true);
        }
        dp[i * 2 + 1] = b;
        if (b < a) a = b;
    }
    return a;
}

int main() {
    fill_n(dp, 2000000, -1);
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        nodes[u - 1].edges.push_back(v - 1);
        nodes[v - 1].edges.push_back(u - 1);
    }

    printf("%d\n", solve(-1, 0, false));
    return 0;
}
