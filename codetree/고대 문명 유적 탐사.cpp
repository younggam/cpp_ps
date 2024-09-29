#include <iostream>
#include <set>
#include <queue>
using namespace std;

int K, M;
char Site[25];
char Temp[25];
char Cur[25];
char Symbols[300];
int s = 0;

struct Coord {
    bool operator()(const int &lhs, const int &rhs) {
        int lm = lhs % 5, rm = rhs % 5;
        return lm < rm || (lm == rm && lhs / 5 > rhs / 5);
    }
};

set<int, Coord> all;
set<int> temp_all;
set<int> temp;
queue<int> q;

int gain() {
    temp_all.clear();
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            int i = r * 5 + c;
            if (temp_all.find(i) != temp_all.end()) continue;
            temp.clear();
            q = {};
            q.emplace(i);
            char t = Temp[i];
            while (!q.empty()) {
                i = q.front();
                int a = i / 5, b = i % 5;
                q.pop();
                temp.emplace(i);
                if (a > 0 && temp.find(i - 5) == temp.end() && Temp[i - 5] == t) q.emplace(i - 5);
                if (b > 0 && temp.find(i - 1) == temp.end() && Temp[i - 1] == t) q.emplace(i - 1);
                if (a < 4 && temp.find(i + 5) == temp.end() && Temp[i + 5] == t) q.emplace(i + 5);
                if (b < 4 && temp.find(i + 1) == temp.end() && Temp[i + 1] == t) q.emplace(i + 1);
            }
            if (temp.size() >= 3) temp_all.insert(temp.begin(), temp.end());
        }
    }
    return temp_all.size();
}

int main() {
    scanf("%d %d", &K, &M);
    scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &Site[0], &Site[1], &Site[2],
          &Site[3], &Site[4], &Site[5], &Site[6], &Site[7], &Site[8], &Site[9], &Site[10], &Site[11], &Site[12],
          &Site[13], &Site[14], &Site[15], &Site[16], &Site[17], &Site[18], &Site[19], &Site[20], &Site[21], &Site[22],
          &Site[23], &Site[24]);
    for (int i = 0; i < M; i++) scanf("%d", &Symbols[i]);
    int ans = 0, a;
    for (int ik = 0; ik < K; ik++) {
        for (int c = 1; c <= 3; c++) {
            for (int r = 1; r <= 3; r++) {
                copy(Site, Site + 25, Temp);
                Temp[(r - 1) * 5 + c + 1] = Site[(r - 1) * 5 + c - 1];
                Temp[r * 5 + c + 1] = Site[(r - 1) * 5 + c];
                Temp[(r + 1) * 5 + c + 1] = Site[(r - 1) * 5 + c + 1];
                Temp[(r + 1) * 5 + c] = Site[r * 5 + c + 1];
                Temp[(r + 1) * 5 + c - 1] = Site[(r + 1) * 5 + c + 1];
                Temp[r * 5 + c - 1] = Site[(r + 1) * 5 + c];
                Temp[(r - 1) * 5 + c - 1] = Site[(r + 1) * 5 + c - 1];
                Temp[(r - 1) * 5 + c] = Site[r * 5 + c - 1];
                a = gain();
                if (ans < a) {
                    copy(Temp, Temp + 25, Cur);
                    ans = a;
                    all.clear();
                    all.insert(temp_all.begin(), temp_all.end());
                }
            }
        }

        for (int c = 1; c <= 3; c++) {
            for (int r = 1; r <= 3; r++) {
                copy(Site, Site + 25, Temp);
                Temp[(r + 1) * 5 + c + 1] = Site[(r - 1) * 5 + c - 1];
                Temp[(r + 1) * 5 + c] = Site[(r - 1) * 5 + c];
                Temp[(r + 1) * 5 + c - 1] = Site[(r - 1) * 5 + c + 1];
                Temp[r * 5 + c - 1] = Site[r * 5 + c + 1];
                Temp[(r - 1) * 5 + c - 1] = Site[(r + 1) * 5 + c + 1];
                Temp[(r - 1) * 5 + c] = Site[(r + 1) * 5 + c];
                Temp[(r - 1) * 5 + c + 1] = Site[(r + 1) * 5 + c - 1];
                Temp[r * 5 + c + 1] = Site[r * 5 + c - 1];
                a = gain();
                if (ans < a) {
                    copy(Temp, Temp + 25, Cur);
                    ans = a;
                    all.clear();
                    all.insert(temp_all.begin(), temp_all.end());
                }
            }
        }

        for (int c = 1; c <= 3; c++) {
            for (int r = 1; r <= 3; r++) {
                copy(Site, Site + 25, Temp);
                Temp[(r + 1) * 5 + c - 1] = Site[(r - 1) * 5 + c - 1];
                Temp[r * 5 + c - 1] = Site[(r - 1) * 5 + c];
                Temp[(r - 1) * 5 + c - 1] = Site[(r - 1) * 5 + c + 1];
                Temp[(r - 1) * 5 + c] = Site[r * 5 + c + 1];
                Temp[(r - 1) * 5 + c + 1] = Site[(r + 1) * 5 + c + 1];
                Temp[r * 5 + c + 1] = Site[(r + 1) * 5 + c];
                Temp[(r + 1) * 5 + c + 1] = Site[(r + 1) * 5 + c - 1];
                Temp[(r + 1) * 5 + c]= Site[r * 5 + c - 1];
                a = gain();
                if (ans < a) {
                    copy(Temp, Temp + 25, Cur);
                    ans = a;
                    all.clear();
                    all.insert(temp_all.begin(), temp_all.end());
                }
            }
        }
        if (ans <= 0) break;
        copy(Cur, Cur + 25, Temp);
        while (true) {
            for (auto &v: all) {
                if (s >= M) break;
                Temp[v] = Symbols[s++];
            }
            if ((a = gain()) <= 0)break;
            ans += a;
            all.clear();
            all.insert(temp_all.begin(), temp_all.end());
        }
        copy(Temp, Temp + 25, Site);
        copy(Temp, Temp + 25, Cur);
        printf("%d ", ans);
        ans = 0;
    }
    return 0;
}
