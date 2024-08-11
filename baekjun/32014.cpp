#include <algorithm>
#include <cstdint>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Mural {
    int64_t start;
    int64_t end;

    bool operator<(const Mural &b) {
        return start < b.start || (b.start >= start && end < b.end);
    }
};

int N;
vector<Mural> murals;
int64_t dp[200001] = {};

int64_t solve(int i) {
    int64_t &v = dp[i];
    if (v != -1) return v;
    if (i >= N) return v = 0;
    v = 0;
    int o = lower_bound(murals.begin(), murals.end(), Mural{murals[i].end, 0}) - murals.begin();
    v = murals[i].end - murals[i].start + solve(o);
    v = max(v, solve(i + 1));
    return v;
}

int main(int argc, char **argv) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int64_t start, end;
        scanf("%lld %lld", &start, &end);
        murals.emplace_back(Mural{start, end});
    }
    sort(murals.begin(), murals.end());
    memset(dp, -1, sizeof(dp));
    printf("%lld", solve(0));

    return 0;
}
