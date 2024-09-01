#include <cstdint>
#include <iostream>

using namespace std;

int N, M;
char Table[50][51];

int solve(int flip) {
    int b = flip;
    int w = (flip + 1) % 2;
    int Cache[50][43] = {};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == b && Table[i][j] == 'B' || (i + j) % 2 == w && Table[i][j] == 'W') Cache[i][0]++;
        }
        for (int j = 8; j < M; j++) {
            auto &c = Cache[i][j - 7];
            c = Cache[i][j - 8];
            if ((i + j - 8) % 2 == b && Table[i][j - 8] == 'B' || (i + j - 8) % 2 == w && Table[i][j - 8] == 'W')
                c -= 1;
            if ((i + j) % 2 == b && Table[i][j] == 'B' || (i + j) % 2 == w && Table[i][j] == 'W') c += 1;
        }
    }

    int min = 2500;
    for (int j = 0; j <= M - 8; j++) {
        int base = 0;
        for (int i = 0; i < 8; i++) base += Cache[i][j];
        if (min > base) min = base;
        for (int i = 8; i < N; i++) {
            base -= Cache[i - 8][j];
            base += Cache[i][j];
            if (min > base) min = base;
        }
    }
    return min;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", &Table[i]);
    }

    printf("%d", min(solve(0), solve(1)));
    return 0;
}
