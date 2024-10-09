#include <iostream>
#include <queue>
using namespace std;

struct Turret {
    short attack;
    short turn;

    void damage(int v) {
        attack = max(attack - v, 0);
    }
};

struct Pos {
    char r;
    char c;

    bool equal(int o_r, int o_c) {
        return r == o_r && c == o_c;
    }
};

char N, M;
short K;
Turret Map[10][10] = {};
bool Temp[10][10] = {};

int main() {
    scanf("%hhd %hhd %hd", &N, &M, &K);
    for (char r = 0; r < N; r++) {
        for (char c = 0; c < M; c++) scanf("%hd", &Map[r][c].attack);
    }
    for (short k = 1; k <= K; k++) {
        // 정비 포탑 초기화
        for (char r = 0; r < N; r++) {
            for (char c = 0; c < M; c++) {
                Temp[r][c] = Map[r][c].attack > 0;
            }
        }
        Turret at = {10000, 10000};
        auto a = &at;
        char a_r = 0, a_c = 0;
        auto d = &Map[0][0];
        char d_r = 0, d_c = 0;
        // 공격자, 대상 포탑 구하기
        for (char r = 0; r < N; r++) {
            for (char c = 0; c < M; c++) {
                auto &t = Map[r][c];
                if (t.attack <= 0)continue;
                if (a->attack > t.attack || a->attack == t.attack && (
                        a->turn < t.turn || a->turn == t.turn && (
                            a_r + a_c < r + c || a_r + a_c == r + c && a_c < c))) {
                    a = &t;
                    a_r = r;
                    a_c = c;
                }
                if (d->attack < t.attack || d->attack == t.attack && (
                        d->turn > t.turn || d->turn == t.turn && (
                            d_r + d_c > r + c || d_r + d_c == r + c && d_c > c))) {
                    d = &t;
                    d_r = r;
                    d_c = c;
                }
            }
        }
        // 포탑 제대로 구했을 때만 공격 ㄱㄱ
        if (a != &at && a->attack > 0 && d->attack > 0 && (a_r != d_r || a_c != d_c)) {
            Temp[a_r][a_c] = false;
            Temp[d_r][d_c] = false;
            // bfs로 레이저 경로 찾기
            Pos Parents[10][10];
            for (char r = 0; r < N; r++) {
                for (char c = 0; c < M; c++) Parents[r][c] = {r, c};
            }
            Parents[a_r][a_c] = {d_r, d_c};
            int max_len = 100;
            queue<Pos> q;
            q.emplace(Pos{a_r, a_c});
            bool good = false;
            while (!q.empty()) {
                auto cur = q.front();
                q.pop();
                Pos next = cur;
                // printf("%d %d\n",cur.r,cur.c);
                if (next.r == d_r && next.c == d_c) {
                    good = true;
                    break;
                }
                next.r = cur.r;
                next.c = (next.c + 1) % M;
                if (Parents[next.r][next.c].equal(next.r, next.c) && Map[next.r][next.c].attack > 0) {
                    Parents[next.r][next.c] = cur;
                    q.emplace(next);
                }
                next.r = (next.r + 1) % N;
                next.c = cur.c;
                if (Parents[next.r][next.c].equal(next.r, next.c) && Map[next.r][next.c].attack > 0) {
                    Parents[next.r][next.c] = cur;
                    q.emplace(next);
                }
                next.r = cur.r;
                next.c = (next.c - 1 + M) % M;
                if (Parents[next.r][next.c].equal(next.r, next.c) && Map[next.r][next.c].attack > 0) {
                    Parents[next.r][next.c] = cur;
                    q.emplace(next);
                }
                next.r = (next.r - 1 + N) % N;
                next.c = cur.c;
                if (Parents[next.r][next.c].equal(next.r, next.c) && Map[next.r][next.c].attack > 0) {
                    Parents[next.r][next.c] = cur;
                    q.emplace(next);
                }
            }
            a->attack += N + M;
            a->turn = k;
            short halved = a->attack / 2;
            d->damage(a->attack);
            if (good) {
                auto by = Parents[d_r][d_c];
                while (by.r != a_r || by.c != a_c) {
                    Map[by.r][by.c].damage(halved);
                    Temp[by.r][by.c] = false;
                    by = Parents[by.r][by.c];
                }
            } else {
                for (char r = d_r - 1; r <= d_r + 1; r++) {
                    for (char c = d_c - 1; c <= d_c + 1; c++) {
                        char tr = (r + N) % N;
                        char tc = (c + M) % M;
                        if (tr == a_r && tc == a_c || tr == d_r && tc == d_c)continue;
                        Map[tr][tc].damage(halved);
                        Temp[tr][tc] = false;
                    }
                }
            }
        } else break;
        for (char r = 0; r < N; r++) {
            for (char c = 0; c < M; c++) {
                if (Temp[r][c]) Map[r][c].attack += 1;
            }
        }
    }
    short ans = 0;
    for (char r = 0; r < N; r++) {
        for (char c = 0; c < M; c++) {
            if (ans < Map[r][c].attack)ans = Map[r][c].attack;
        }
    }
    printf("%hd", ans);
    return 0;
}
