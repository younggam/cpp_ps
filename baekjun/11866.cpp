#include <iostream>
#include <vector>

using namespace std;

int N, K;

int main() {
    scanf("%d %d", &N, &K);
    vector<int> v;
    for (int i = 1; i <= N; i++) v.emplace_back(i);
    printf("<");
    int k = K - 1;
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", v[k]);
        v.erase(v.begin() + k);
        k = (k - 1 + K) % v.size();
    }
    printf("%d>", v[0]);
    return 0;
}
