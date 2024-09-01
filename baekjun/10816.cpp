#include <iostream>
#include <map>

using namespace std;

int N, M;
map<int, int> C;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int c;
        scanf("%d", &c);
        auto found = C.find(c);
        if (found == C.end()) C.emplace(c, 1);
        else found->second += 1;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int c;
        scanf("%d", &c);
        printf("%d ", C.find(c) == C.end() ? 0 : C[c]);
    }
    return 0;
}
