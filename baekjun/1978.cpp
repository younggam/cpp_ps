#include <cmath>
#include <iostream>

using namespace std;

int N, M;

bool solve() {
    if (M == 1) return false;
    auto len = sqrt(M);
    for (int i = 2; i <= len; i++) {
        if (M % i == 0) return false;
    }
    return true;
}

int main() {
    scanf("%d", &N);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &M);
        if (solve()) ans += 1;
    }
    printf("%d\n", ans);
    return 0;
}
