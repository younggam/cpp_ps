#include <iostream>
#include <set>

using namespace std;

int N, M;
set<int> A;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int a;
        scanf("%d", &a);
        A.emplace(a);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int m;
        scanf("%d", &m);
        printf("%d\n", A.find(m) != A.end());
    }

    return 0;
}
