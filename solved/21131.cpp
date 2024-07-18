#include <iostream>

using namespace std;

int solve(int matrix[][64], int N) {
    int ret = 0;
    int *top = matrix[0];
    for (int i = N - 1; i > 0; i--) {
        if (ret % 2 == 0 && top[i] != i + 1 || ret % 2 == 1 && top[i] == i + 1) ret++;
    }
    return ret;
}

int main(int argc, char **argv) {
    int T, t = 1;
    scanf("%d",&T);
    int matrix[64][64];
    for (int i = 0; i < T; i++) {
        int N;
        scanf("%d",&N);
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) scanf("%d", &matrix[j][k]);
        }
        printf("%d\n", solve(matrix, N));
        t++;
    }
    return 0;
}