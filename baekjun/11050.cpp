#include <iostream>

using namespace std;

int N, K;

int main() {
    scanf("%d %d", &N, &K);

    int a = 1;
    K = min(K, N - K);
    for (int i = 0; i < K; i++) a *= N - i;
    for (int i = 1; i <= K; i++) a /= i;

    printf("%d\n", a);
    return 0;
}
