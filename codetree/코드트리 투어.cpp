#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct Vertex {
    short v;
    vector<short> edges;
};

struct Edge {
    short u;
    short v;
    short weight;
};

struct Product {
    short id;
    short revenue;
    short dest;

    bool operator<(const Product &rhs) const {
        return id < rhs.id;
    }
};

struct Visit {
    short v;
    short cost;

    bool operator<(const Visit &rhs) const {
        return cost > rhs.cost;
    }
};

struct Result {
    short id;
    short cost;

    bool operator<(const Result &rhs) const {
        return cost < rhs.cost||(cost==rhs.cost&&id>rhs.id);
    }
};

int N, M;
short O;
Vertex Vertices[2000];
Edge Edges[10000];
set<Product> Products;
short visited[2000];
priority_queue<Result> results;

void dijkstra() {
    fill_n(visited, N, 32767);
    visited[O] = 0;
    priority_queue<Visit> q;
    q.push({O, 0});
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        if (cur.cost > visited[cur.v]) continue;
        for (auto eid: Vertices[cur.v].edges) {
            auto e = Edges[eid];
            short v = e.v == cur.v ? e.u : e.v;
            if (visited[v] > e.weight + cur.cost) {
                q.push({v, (short) (e.weight + cur.cost)});
                visited[v] = e.weight + cur.cost;
            }
        }
    }
}

void solve() {
    results = priority_queue<Result>();
    for (auto &p: Products) {
        if (p.id == 0 || p.revenue < visited[p.dest])continue;
        results.push({p.id, (short) (p.revenue - visited[p.dest])});
    }
}

int main() {
    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
            case 100:
                scanf("%d %d", &N, &M);
                for (int j = 0; j < M; j++) {
                    short u, v, w;
                    scanf("%hd %hd %hd", &v, &u, &w);
                    Edges[j] = {v, u, w};
                    Vertices[v].v = v;
                    Vertices[v].edges.emplace_back(j);
                    Vertices[u].v = u;
                    Vertices[u].edges.emplace_back(j);
                }
                O = 0;
                dijkstra();
                break;
            case 200:{
                short id, revenue, dest;
                scanf("%hd %hd %hd", &id, &revenue, &dest);
                Product p={id, revenue, dest};
                Products.insert(p);
                if (p.revenue >= visited[p.dest])results.push({p.id, (short) (p.revenue - visited[p.dest])});
                }
                break;
            case 300:
                short d;
                scanf("%hd", &d);
                Products.erase({d});
                break;
            case 400: {
                short best = -1;
                while (!results.empty()) {
                    auto pick = results.top();
                    results.pop();
                    if (Products.find({pick.id}) == Products.end())continue;
                    Products.erase({pick.id});
                    best = pick.id;
                    break;
                }
                printf("%hd\n", best);
            }
            break;
            case 500:
                scanf("%hd", &O);
                dijkstra();
                solve();
                break;
        }
    }
    return 0;
}
