#include <algorithm>
#include <iostream>

using namespace std;

int N;
int M[1000000];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &M[i]);
    }

    sort(M, M + N);

    for (int i = 0; i < N; i++)  printf("%d\n", M[i]);
    return 0;
}
