#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct Knight {
    char id;
    char r;
    char c;
    char h;
    char w;
    char k;
    char d;
};

char L, N, Q;
char Board[42][42] = {};
char Map[42][42] = {};
Knight Knights[31] = {};

int main() {
    scanf("%hhd %hhd %hhd", &L, &N, &Q);
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= L; j++) scanf("%hhd", &Map[i][j]);
    }
    for (int i = 0; i <= L + 1; i++) {
        Map[i][0] = 2;
        Map[i][L + 1] = 2;
    }
    for (int i = 0; i <= L + 1; i++) {
        Map[0][i] = 2;
        Map[L + 1][i] = 2;
    }
    for (char i = 1; i <= N; i++) {
        scanf("%hhd %hhd %hhd %hhd %hhd", &Knights[i].r, &Knights[i].c, &Knights[i].h, &Knights[i].w, &Knights[i].k);
        Knights[i].id = i;
        for (char r = Knights[i].r; r < Knights[i].r + Knights[i].h; r++) {
            for (char c = Knights[i].c; c < Knights[i].c + Knights[i].w; c++) {
                Board[r][c] = i;
            }
        }
    }
    for (int iq = 0; iq < Q; iq++) {
        int i, d;
        scanf("%d %d", &i, &d);
        auto &knight = Knights[i];
        if (knight.k <= knight.d) continue;
        bool found[31] = {};
        queue<Knight *> q = {};
        queue<Knight *> qq = {};
        q.push(&knight);
        qq.push(&knight);
        bool wall = false;
        while (!q.empty() && !wall) {
            auto &cur = *q.front();
            q.pop();
            switch (d) {
                case 0:
                    for (int c = cur.c; c < cur.c + cur.w; c++) {
                        auto b = Board[cur.r - 1][c];
                        if (Map[cur.r - 1][c] == 2) {
                            wall = true;
                            break;
                        } else if (b > 0 && !found[b]) {
                            found[b] = true;
                            q.push(&Knights[b]);
                            qq.push(&Knights[b]);
                        }
                    }
                    break;
                case 1:
                    for (int r = cur.r; r < cur.r + cur.h; r++) {
                        auto b = Board[r][cur.c + cur.w];
                        if (Map[r][cur.c + cur.w] == 2) {
                            wall = true;
                            break;
                        } else if (b > 0 && !found[b]) {
                            found[b] = true;
                            q.push(&Knights[b]);
                            qq.push(&Knights[b]);
                        }
                    }
                    break;
                case 2:
                    for (int c = cur.c; c < cur.c + cur.w; c++) {
                        auto b = Board[cur.r + cur.h][c];
                        if (Map[cur.r + cur.h][c] == 2) {
                            wall = true;
                            break;
                        } else if (b > 0 && !found[b]) {
                            found[b] = true;
                            q.push(&Knights[b]);
                            qq.push(&Knights[b]);
                        }
                    }
                    break;
                case 3:
                    for (int r = cur.r; r < cur.r + cur.h; r++) {
                        auto b = Board[r][cur.c - 1];
                        if (Map[r][cur.c - 1] == 2) {
                            wall = true;
                            break;
                        } else if (b > 0 && !found[b]) {
                            found[b] = true;
                            q.push(&Knights[b]);
                            qq.push(&Knights[b]);
                        }
                    }
                    break;
            }
        }
        if (wall) continue;
        char move_r = 0;
        char move_c = 0;
        switch (d) {
            case 0:
                move_r = -1;
                break;
            case 1:
                move_c = 1;
                break;
            case 2:
                move_r = 1;
                break;
            case 3:
                move_c = -1;
                break;
        }
        while (!qq.empty()) {
            auto &cur = *qq.front();
            qq.pop();
            cur.r += move_r;
            cur.c += move_c;
            if (cur.id != i) {
                for (char r = cur.r; r < cur.r + cur.h; r++) {
                    for (char c = cur.c; c < cur.c + cur.w; c++) {
                        if (Map[r][c] == 1) cur.d += 1;
                    }
                }
            }
        }
        memset(Board, 0, 42 * 42);
        for (int i = 1; i <= N; i++) {
            auto &cur = Knights[i];
            if (cur.k <= cur.d) continue;
            for (char r = cur.r; r < cur.r + cur.h; r++) {
                for (char c = cur.c; c < cur.c + cur.w; c++) {
                    Board[r][c] = cur.id;
                }
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        if (Knights[i].k - Knights[i].d > 0)sum += Knights[i].d;
    }
    printf("%d", sum);
    return 0;
}
