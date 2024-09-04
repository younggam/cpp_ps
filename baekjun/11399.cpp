#include <algorithm>
#include <iostream>

using namespace std;

int N;

int P[1000];
bool used[1000];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &P[i]);
    }
    sort(P, P + N);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += P[i] * (N - i);
    }
    printf("%d\n", ans);
    return 0;
}
