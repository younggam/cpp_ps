#include <iostream>
#include <cstring>
using namespace std;

char N, M, K;

char Maze[10][10] = {};
char TM[10][10] = {};
short Board[10][10] = {};
short TB[10][10] = {};
char Players[10][2] = {};
bool Exited[10];
char End = 0;
short Moves[10] = {};
char exit_r, exit_c;

int main() {
    scanf("%hhd %hhd %hhd", &N, &M, &K);
    for (char r = 0; r < N; r++) {
        for (char c = 0; c < N; c++) {
            scanf("%hhd", &Maze[r][c]);
        }
    }
    for (char m = 0; m < M; m++) {
        scanf("%hhd %hhd", &Players[m][0], &Players[m][1]);
        Players[m][0] -= 1;
        Players[m][1] -= 1;
        Board[Players[m][0]][Players[m][1]] |= 1 << m;
    }
    scanf("%hhd %hhd", &exit_r, &exit_c);
    exit_r--;
    exit_c--;
    for (char k = 1; k <= K; k++) {
        memset(Board, 0, 200);
        for (char m = 0; m < M; m++) {
            if (Exited[m]) continue;
            auto &p = Players[m];
            char move_r = exit_r < p[0] ? -1 : exit_r > p[0] ? 1 : 0;
            char move_c = exit_c < p[1] ? -1 : exit_c > p[1] ? 1 : 0;
            if (move_r != 0 && Maze[p[0] + move_r][p[1]] == 0)move_c = 0;
            else if (move_c != 0 && Maze[p[0]][p[1] + move_c] == 0)move_r = 0;
            else {
                move_r = 0;
                move_c = 0;
            }
            p[0] += move_r;
            p[1] += move_c;
            if (p[0] == exit_r && p[1] == exit_c) {
                Exited[m] = true;
                End += 1;
            } else Board[p[0]][p[1]] |= 1 << m;
            Moves[m] += abs(move_r) + abs(move_c);
        }
        if (End == M)break;

        char len = N;
        char rr = N, rc = N;
        char m_p;
        for (char m = 0; m < M; m++) {
            if (Exited[m]) continue;
            auto &t_p = Players[m];
            char t_r = t_p[0] - exit_r;
            char t_c = t_p[1] - exit_c;
            char t_l = max(abs(t_r), abs(t_c)) + 1;
            char t_rr, t_rc;
            if (t_r <= 0) t_rr = max(exit_r - t_l + 1, 0);
            else t_rr = max(t_p[0] - t_l + 1, 0);
            if (t_c <= 0) t_rc = max(exit_c - t_l + 1, 0);
            else t_rc = max(t_p[1] - t_l + 1, 0);
            if (t_l < len || len == t_l && (t_rr < rr || t_rr == rr && t_rc < rc)) {
                len = t_l;
                rr = t_rr;
                rc = t_rc;
                m_p = m;
            }
        }
        memcpy(TM, Maze, 100);
        for (int r = 0; r < len; r++) {
            for (int c = 0; c < len; c++) {
                auto w = TM[rr + r][rc + c] - 1;
                Maze[rr + c][rc + len - r - 1] = max(w, 0);
            }
        }
        char tr = exit_r - rr;
        char tc = exit_c - rc;
        exit_r = rr + tc;
        exit_c = rc + len - tr - 1;
        memcpy(TB, Board, 200);
        for (int r = 0; r < len; r++) {
            for (int c = 0; c < len; c++) {
                auto p = TB[rr + r][rc + c];
                for (char m = 0; m < M; m++) {
                    if (Exited[m] || (p & 1 << m) == 0) continue;
                    Players[m][0] = rr + c;
                    Players[m][1] = rc + len - r - 1;
                }
                Board[rr + c][rc + len - r - 1] = p;
            }
        }
    }
    short sum = 0;
    for (int m = 0; m < M; m++)sum += Moves[m];
    printf("%hd\n", sum);
    printf("%hhd %hhd\n", exit_r + 1, exit_c + 1);
    return 0;
}
