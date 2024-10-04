#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Santa {
    short r;
    short c;
    short p;
    short stunned;
    int score;
};

short N, M, P, C, D;
Santa santas[31] = {};
short Board[51][51] = {};
vector<Santa *> alives;
short rudolf_r;
short rudolf_c;

void knockback(Santa *santa, short move_r, short move_c, int &i) {
    auto bumper = santa;
    short tr = santa->r, tc = santa->c;
    stack<Santa *> s;
    while (1) {
        int p = Board[tr][tc];
        if (p == 0) break;
        else {
            santa = &santas[p];
            s.emplace(santa);
            tr += move_r;
            tc += move_c;
        }
    }
    while (!s.empty()) {
        santa = s.top();
        s.pop();
        Board[santa->r][santa->c] = 0;
        santa->r += move_r;
        santa->c += move_c;
        if (santa->r < 1 || santa->c < 1 || santa->r > N || santa->c > N) {
            for (int j = 0; j < alives.size(); j++) {
                if (alives[j]->p == santa->p) {
                    alives.erase(alives.begin() + j);
                    j--;
                    if (j < i)i--;
                }
            }
        } else Board[santa->r][santa->c] = santa->p;
    }
    Board[bumper->r][bumper->c] = bumper->p;
}

short dist(short ar, short ac, short br, short bc) {
    short diff_r = ar - br;
    short diff_c = ac - bc;
    return diff_r * diff_r + diff_c * diff_c;
}

int main() {
    scanf("%hd %hd %hd %hd %hd", &N, &M, &P, &C, &D);
    scanf("%hd %hd", &rudolf_r, &rudolf_c);
    for (int i = 0; i < P; i++) {
        short p, r, c;
        scanf("%hd %hd %hd", &p, &r, &c);
        santas[p].p = p;
        santas[p].r = r;
        santas[p].c = c;
        Board[r][c] = p;
    }
    for (int p = 1; p <= P; p++) alives.emplace_back(&santas[p]);
    for (int m = 0; m < M; m++) {
        int min = 1000000;
        vector<Santa *>::iterator min_santa;
        for (auto alive = alives.begin(); alive != alives.end(); ++alive) {
            short d = dist(rudolf_r, rudolf_c, (*alive)->r, (*alive)->c);
            if (d < min || d == min && ((*alive)->r > (*min_santa)->r || (*alive)->r == (*min_santa)->r && (*alive)->c >
                                        (*min_santa)->c)) {
                min = d;
                min_santa = alive;
            }
        }
        short move_r = rudolf_r < (*min_santa)->r ? 1 : rudolf_r > (*min_santa)->r ? -1 : 0;
        short move_c = rudolf_c < (*min_santa)->c ? 1 : rudolf_c > (*min_santa)->c ? -1 : 0;
        rudolf_r += move_r;
        rudolf_c += move_c;
        if (rudolf_r == (*min_santa)->r && rudolf_c == (*min_santa)->c) {
            (*min_santa)->score += C;
            Board[(*min_santa)->r][(*min_santa)->c] = 0;
            (*min_santa)->r += move_r * C;
            (*min_santa)->c += move_c * C;
            if ((*min_santa)->r < 1 || (*min_santa)->c < 1 || (*min_santa)->r > N || (*min_santa)->c > N) alives.
                    erase(min_santa);
            else {
                auto temp = *min_santa;
                int asdf = 0;
                knockback(temp, move_r, move_c, asdf);
                temp->stunned = 2;
            }
        }

        for (int i = 0; i < alives.size(); i++) {
            auto alive = alives[i];
            if (alive->stunned > 0) {
                alive->stunned -= 1;
                continue;
            }
            move_r = rudolf_r < alive->r ? -1 : rudolf_r > alive->r ? 1 : 0;
            move_c = rudolf_c < alive->c ? -1 : rudolf_c > alive->c ? 1 : 0;
            short d0 = dist(rudolf_r, rudolf_c, alive->r + move_r, alive->c);
            short d1 = dist(rudolf_r, rudolf_c, alive->r, alive->c + move_c);
            if (d0 == d1) {
                if (move_r < 0 && !Board[alive->r - 1][alive->c]) move_c = 0;
                else if (move_c > 0 && !Board[alive->r][alive->c + 1]) move_r = 0;
                else if (move_r > 0 && !Board[alive->r + 1][alive->c]) move_c = 0;
                else if (move_c < 0 && !Board[alive->r][alive->c - 1]) move_r = 0;
                else continue;
            } else if (d0 > d1) {
                if (move_c != 0 && !Board[alive->r][alive->c + move_c]) move_r = 0;
                else if (move_r != 0 && !Board[alive->r + move_r][alive->c]) move_c = 0;
                else continue;
            } else if (d0 < d1) {
                if (move_r != 0 && !Board[alive->r + move_r][alive->c]) move_c = 0;
                else if (move_c != 0 && !Board[alive->r][alive->c + move_c]) move_r = 0;
                else continue;
            } else continue;
            Board[alive->r][alive->c] = 0;
            alive->r += move_r;
            alive->c += move_c;
            Board[alive->r][alive->c] = alive->p;
            if (rudolf_r == alive->r && rudolf_c == alive->c) {
                alive->score += D;
                Board[alive->r][alive->c] = 0;
                alive->r -= move_r * D;
                alive->c -= move_c * D;
                if (alive->r < 1 || alive->c < 1 || alive->r > N || alive->c > N) {
                    alives.erase(alives.begin() + i);
                    i--;
                } else {
                    knockback(alive, -move_r, -move_c, i);
                    alive->stunned = 1;
                }
            }
        }
        if (alives.empty())break;
        for (auto alive: alives) {
            alive->score += 1;
        }
    }
    for (int p = 1; p <= P; p++) printf("%d ", santas[p].score);
    return 0;
}
