#include <iostream>
using namespace std;

struct Gun {
    int a;
    int next;
};

int N, M, K;
Gun Guns[401] = {};
int Board[20][20] = {};

struct Player {
    int m;
    int r;
    int c;
    int d;
    int a;
    int g;
    int s;

    void move() {
        switch (d) {
            case 0:
                r -= 1;
                if (r < 0) {
                    r = 1;
                    d = 2;
                }
                break;
            case 1:
                c += 1;
                if (c >= N) {
                    c = N - 2;
                    d = 3;
                }
                break;
            case 2:
                r += 1;
                if (r >= N) {
                    r = N - 2;
                    d = 0;
                }
                break;
            case 3:
                c -= 1;
                if (c < 0) {
                    c = 1;
                    d = 1;
                }
                break;
        }
    }

    int attack(Player &rhs) {
        int sum = a + (g >= 0 ? Guns[g].a : 0);
        int rhs_sum = rhs.a + (rhs.g >= 0 ? Guns[rhs.g].a : 0);
        return sum - rhs_sum;
    }
};

Player Players[30] = {};

int collide(int from, int r, int c) {
    for (int m = 0; m < M; m++) {
        if (m != from && r == Players[m].r && c == Players[m].c) return m;
    }
    return -1;
}

void try_move(Player &p) {
    int r;
    int c;
    for (;;) {
        switch (p.d) {
            case 0:
                r = p.r - 1;
                c = p.c;
                break;
            case 1:
                r = p.r;
                c = p.c + 1;
                break;
            case 2:
                r = p.r + 1;
                c = p.c;
                break;
            case 3:
                r = p.r;
                c = p.c - 1;
                break;
        }
        if (r < 0 || r >= N || c < 0 || c >= N || collide(p.m, r, c) >= 0) p.d = (p.d + 1) % 4;
        else break;
    }
    p.r = r;
    p.c = c;
}

void put_gun(int g, int r, int c) {
    if (g <= 0) return;
    int cur = Board[r][c];
    Board[r][c] = g;
    Guns[g].next = cur;
}

void get_gun(Player &p) {
    int g = Board[p.r][p.c];
    int good = g, prev_good = 0;
    if (g > 0) {
        while (Guns[g].next > 0) {
            int prev = g;
            g = Guns[g].next;
            if (Guns[g].a > Guns[good].a) {
                prev_good = prev;
                good = g;
            }
        }
    }
    if (good > 0 && (p.g == 0 || Guns[good].a > Guns[p.g].a)) {
        int p_g = p.g;
        p.g = good;
        if (prev_good > 0) Guns[prev_good].next = Guns[good].next;
        else Board[p.r][p.c] = Guns[good].next;
        Guns[good].next = 0;
        put_gun(p_g, p.r, p.c);
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int a;
            scanf("%d", &a);
            if (a > 0) {
                Guns[r * N + c + 1].a = a;
                Board[r][c] = r * N + c + 1;
            }
        }
    }
    for (int m = 0; m < M; m++) {
        int x, y, d, a;
        scanf("%d %d %d %d", &x, &y, &d, &a);
        x--;
        y--;
        Players[m] = {m, x, y, d, a, 0, 0};
    }
    for (int k = 0; k < K; k++) {
        for (int m = 0; m < M; m++) {
            auto &p = Players[m];
            // 1-1.
            p.move();
            int o_m = collide(m, p.r, p.c);
            if (o_m >= 0) {
                // 2-2-1.
                auto &o_p = Players[o_m];
                int diff = p.attack(o_p);
                int win = o_m;
                int lost = m;
                if (diff > 0 || diff == 0 && p.a > o_p.a) {
                    win = p.m;
                    lost = o_p.m;
                }
                Players[win].s += abs(diff);
                // 2-2-2.
                put_gun(Players[lost].g, Players[lost].r, Players[lost].c);
                Players[lost].g = 0;
                try_move(Players[lost]);
                get_gun(Players[lost]);
                // 2-2-3.
                get_gun(Players[win]);
                // 2-1.
            } else get_gun(p);
        }
    }
    for (int m = 0; m < M; m++) printf("%d ", Players[m].s);
    return 0;
}
