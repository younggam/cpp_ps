#include <iostream>

using namespace std;

void dynamic(char matrix[][100], int d[][100], const int N, const int i, const int j) {
    int temp;
    if (d[i][j] > d[N - 1][N - 1]) return;
    if (i + 1 < N) {
        temp = matrix[i + 1][j] + d[i][j];
        bool down = temp < d[i + 1][j];
        if (down) {
            d[i + 1][j] = temp;
            dynamic(matrix, d, N, i + 1, j);
        }
    }
    if (j + 1 < N) {
        temp = matrix[i][j + 1] + d[i][j];
        bool right = temp < d[i][j + 1];
        if (right) {
            d[i][j + 1] = temp;
            dynamic(matrix, d, N, i, j + 1);
        }
    }
    if (i - 1 >= 0) {
        temp = matrix[i - 1][j] + d[i][j];
        bool up = temp < d[i - 1][j];
        if (up) {
            d[i - 1][j] = temp;
            dynamic(matrix, d, N, i - 1, j);
        }
    }
    if (j - 1 >= 0) {
        temp = matrix[i][j - 1] + d[i][j];
        bool left = temp < d[i][j - 1];
        if (left) {
            d[i][j - 1] = temp;
            dynamic(matrix, d, N, i, j - 1);
        }
    }
}

int main(int argc, char **argv) {
    int T, t = 1;
    scanf("%d", &T);
    char matrix[100][100];
    int d[100][100];
    for (int i = 0; i < T; i++) {
        int N;
        scanf("%d", &N);
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                scanf(" %c", &matrix[j][k]);
                matrix[j][k] -= '0';
                d[j][k] = 1000000;
            }
        }

        d[0][0] = 0;
        dynamic(matrix, d, N, 0, 0);
        printf("#%d %d\n", t, d[N - 1][N - 1]);
        t++;
    }
    return 0;
}
