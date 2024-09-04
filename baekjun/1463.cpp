#include <iostream>

using namespace std;

int N;
int DP[1000001] = {};

int solve(int n) {
    if (n == 1) return 0;
    int &v = DP[n];
    if (v != 0) return v;
    v = 1;
    int a = 10000000;
    if (n % 3 == 0) a = min(a, solve(n / 3));
    if (n % 2 == 0) a = min(a, solve(n / 2));
    a = min(a, solve(n - 1));
    return v += a;
}

int main() {
    scanf("%d", &N);
    printf("%d\n", solve(N));
    return 0;
}
