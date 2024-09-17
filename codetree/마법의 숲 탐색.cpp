#include <iostream>
#include <queue>
using namespace std;

int R, C, K;
char F[70][70] = {};

int main() {
    scanf("%d %d %d", &R, &C, &K);
    int ans = 0;
    for (int i = 0; i < K; i++) {
        int r = -2, c, d;
        scanf("%d %d", &c, &d);
        c--;
        for (;;) {
            if (r < R - 2 && F[r + 2][c] == 0 && (r < -1 || F[r + 1][c - 1] == 0 && F[r + 1][c + 1] == 0)) {
                r += 1;
            } else if (r < R - 2 && c > 1 && (r < 1 || F[r - 1][c - 1] == 0) && (r < 0 || F[r][c - 2] == 0) && (
                           r < -1 || F[r + 1][c - 1] == 0) && F[r + 2][c - 1] == 0 && (
                           r < -1 || F[r + 1][c - 2] == 0)) {
                r += 1;
                d = (d + 3) % 4;
                c -= 1;
            } else if (r < R - 2 && c < C - 2 && (r < 1 || F[r - 1][c + 1] == 0) && (r < 0 || F[r][c + 2] == 0) && (
                           r < -1 || F[r + 1][c + 1] == 0) && F[r + 2][c + 1] == 0 && (
                           r < -1 || F[r + 1][c + 2] == 0)) {
                r += 1;
                d = (d + 1) % 4;
                c += 1;
            } else {
                if (r < 1) {
                    for (int a = 0; a < R; a++) {
                        fill_n(F[a], C, 0);
                    }
                } else {
                    F[r][c] = 1;
                    F[r - 1][c] = d == 0 ? 3 : 2;
                    F[r][c + 1] = d == 1 ? 3 : 2;
                    F[r + 1][c] = d == 2 ? 3 : 2;
                    F[r][c - 1] = d == 3 ? 3 : 2;
                    bool visited[70][70] = {};
                    visited[r][c] = true;
                    queue<pair<int, int> > q;
                    q.push(make_pair(r, c));
                    while (!q.empty()) {
                        auto cur = q.front();
                        if (r < cur.first)r = cur.first;
                        q.pop();
                        switch (F[cur.first][cur.second]) {
                            case 2:
                                if (cur.first > 0 && F[cur.first - 1][cur.second] == 1 && !visited[cur.first - 1][cur.
                                        second]) {
                                    q.push(make_pair(cur.first - 1, cur.second));
                                    visited[cur.first - 1][cur.second] = true;
                                }
                                if (cur.second < C - 1 && F[cur.first][cur.second + 1] == 1 && !visited[cur.first][
                                        cur.second + 1]) {
                                    q.push(make_pair(cur.first, cur.second + 1));
                                    visited[cur.first][cur.second + 1] = true;
                                }
                                if (cur.first < R - 1 && F[cur.first + 1][cur.second] == 1 && !visited[cur.first + 1][
                                        cur
                                        .second]) {
                                    q.push(make_pair(cur.first + 1, cur.second));
                                    visited[cur.first + 1][cur.second] = true;
                                }
                                if (cur.second > 0 && F[cur.first][cur.second - 1] == 1 && !visited[cur.first][
                                        cur.second - 1]) {
                                    q.push(make_pair(cur.first, cur.second - 1));
                                    visited[cur.first][cur.second - 1] = true;
                                }
                                break;
                            case 1:
                            case 3:
                                if (cur.first > 0 && F[cur.first - 1][cur.second] > 0 && !visited[cur.first - 1][cur.
                                        second]) {
                                    q.push(make_pair(cur.first - 1, cur.second));
                                    visited[cur.first - 1][cur.second] = true;
                                }
                                if (cur.second < C - 1 && F[cur.first][cur.second + 1] > 0 && !visited[cur.first][
                                        cur.second + 1]) {
                                    q.push(make_pair(cur.first, cur.second + 1));
                                    visited[cur.first][cur.second + 1] = true;
                                }
                                if (cur.first < R - 1 && F[cur.first + 1][cur.second] > 0 && !visited[cur.first + 1][
                                        cur
                                        .second]) {
                                    q.push(make_pair(cur.first + 1, cur.second));
                                    visited[cur.first + 1][cur.second] = true;
                                }
                                if (cur.second > 0 && F[cur.first][cur.second - 1] > 0 && !visited[cur.first][
                                        cur.second - 1]) {
                                    q.push(make_pair(cur.first, cur.second - 1));
                                    visited[cur.first][cur.second - 1] = true;
                                }
                                break;
                        }
                    }
                    ans += r + 1;
                }
                break;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
