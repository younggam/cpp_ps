#include <iostream>

using namespace std;

int N;
int S[1000];

int main() {
    scanf("%d", &N);
    float M = 0;
    for (int i = 0; i < N; i++) {
        int s;
        scanf("%d", &s);
        S[i] = s;
        M = M < s ? s : M;
    }
    float ans = 0;
    for (int i = 0; i < N; i++) {
        ans += S[i] / M;
    }
    printf("%f\n", ans / N * 100);

    return 0;
}
