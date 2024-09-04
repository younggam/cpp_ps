#include <iostream>

using namespace std;

int N;
pair<int, int> DP[82] = {};

pair<int, int> solve(int n) {
    auto &v = DP[n];
    if (v.first != 0 || v.second != 0) return v;
    if (n == 0) {
        v.first = 1;
        return v;
    }
    if (n == 1) {
        v.second = 1;
        return v;
    }
    auto a = solve(n - 1);
    auto b = solve(n - 2);
    return v = make_pair(a.first + b.first, a.second + b.second);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d", &N);
        auto ans = solve(N);
        printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}
