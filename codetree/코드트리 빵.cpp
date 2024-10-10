#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct Node {
    char depth;
    char r;
    char c;

    bool operator<(const Node &rhs) const {
        return depth < rhs.depth || depth == rhs.depth && (r < rhs.r || r == rhs.r && c < rhs.c);
    }
};

struct Pos {
    char r;
    char c;

    bool equal(const Pos &rhs) const {
        return r == rhs.r && c == rhs.c;
    }

    bool equal(const Node &rhs) const {
        return r == rhs.r && c == rhs.c;
    }
};

struct Person {
    char m;
    Pos pos;
};

char N, M;
char Grid[15][15];
Pos Temp[15][15] = {};
Pos Stores[30];
vector<Pos> Camps;
vector<Person> People;

Pos bfs(char m, Pos src) {
    for (char i = 0; i < N; i++) {
        for (char j = 0; j < N; j++) {
            if (Grid[i][j] < 0)Temp[i][j] = Stores[m];
            else Temp[i][j] = Pos{i, j};
        }
    }
    Temp[src.r][src.c] = Stores[m];
    queue<Pos> q;
    q.emplace(src);
    Pos next;
    while (q.size() > 0) {
        auto cur = q.front();
        q.pop();
        if (cur.equal(Stores[m])) {
            next = cur;
            break;
        }
        next.r = cur.r - 1;
        next.c = cur.c;
        if (next.r >= 0 && Temp[next.r][next.c].equal(next)) {
            q.emplace(Pos{next.r, next.c});
            Temp[next.r][next.c] = cur;
        }
        next.r = cur.r;
        next.c = cur.c - 1;
        if (next.c >= 0 && Temp[next.r][next.c].equal(next)) {
            q.emplace(Pos{next.r, next.c});
            Temp[next.r][next.c] = cur;
        }
        next.r = cur.r;
        next.c = cur.c + 1;
        if (next.c < N && Temp[next.r][next.c].equal(next)) {
            q.emplace(Pos{next.r, next.c});
            Temp[next.r][next.c] = cur;
        }
        next.r = cur.r + 1;
        next.c = cur.c;
        if (next.r < N && Temp[next.r][next.c].equal(next)) {
            q.emplace(Pos{next.r, next.c});
            Temp[next.r][next.c] = cur;
        }
    }
    while (!Temp[next.r][next.c].equal(src)) next = Temp[next.r][next.c];
    return next;
}

Pos bfs2(int m, Pos src) {
    for (char i = 0; i < N; i++) {
        for (char j = 0; j < N; j++) {
            if (Grid[i][j] < 0)Temp[i][j] = {N, N};
            else Temp[i][j] = Pos{i, j};
        }
    }
    Temp[src.r][src.c] = {N, N};
    set<Node> q;
    q.emplace(Node{0, src.r, src.c});
    Node next;
    while (q.size() > 0) {
        auto cur = *q.begin();
        q.erase(q.begin());
        if (Grid[cur.r][cur.c] == 1) {
            next = cur;
            break;
        }
        next.depth = cur.depth + 1;
        next.r = cur.r - 1;
        next.c = cur.c;
        if (next.r >= 0 && Temp[next.r][next.c].equal(next)) {
            q.emplace(next);
            Temp[next.r][next.c] = Pos{cur.r, cur.c};
        }
        next.r = cur.r;
        next.c = cur.c - 1;
        if (next.c >= 0 && Temp[next.r][next.c].equal(next)) {
            q.emplace(next);
            Temp[next.r][next.c] = Pos{cur.r, cur.c};
        }
        next.r = cur.r;
        next.c = cur.c + 1;
        if (next.c < N && Temp[next.r][next.c].equal(next)) {
            q.emplace(next);
            Temp[next.r][next.c] = Pos{cur.r, cur.c};
        }
        next.r = cur.r + 1;
        next.c = cur.c;
        if (next.r < N && Temp[next.r][next.c].equal(next)) {
            q.emplace(next);
            Temp[next.r][next.c] = Pos{cur.r, cur.c};
        }
    }
    return Pos{next.r, next.c};
}


int main() {
    scanf("%hhd %hhd", &N, &M);
    for (char n = 0; n < N; n++) {
        for (char c = 0; c < N; c++) {
            scanf("%hhd", &Grid[n][c]);
            if (Grid[n][c] > 0) Camps.emplace_back(Pos{n, c});
        }
    }
    for (char m = 0; m < M; m++) {
        char r, c;
        scanf("%hhd %hhd", &r, &c);
        r--;
        c--;
        Grid[r][c] = 2;
        Stores[m] = {r, c};
    }
    int ans = 0;
    int done = 0;
    while (done < M) {
        vector<Pos> arrivals;
        for (auto it = People.begin(); it != People.end();) {
            auto arrival = bfs(it->m, it->pos);
            it->pos = arrival;
            if (Stores[it->m].equal(arrival)) {
                arrivals.emplace_back(arrival);
                it = People.erase(it);
            } else ++it;
        }
        //
        for (auto &arrival: arrivals) {
            Grid[arrival.r][arrival.c] = -1;
            done++;
        }
        //
        if (ans < M) {
            auto good = bfs2(ans, Stores[ans]);
            Grid[good.r][good.c] = -1;
            People.emplace_back(Person{(char) ans, good});
            for (auto it = Camps.begin(); it != Camps.end(); ++it) {
                if (good.r == it->r && good.c == it->c) {
                    Camps.erase(it);
                    break;
                }
            }
        }
        ans++;
    }
    printf("%d", ans);
    return 0;
}
