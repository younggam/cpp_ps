#include <iostream>
#include <queue>

using namespace std;

int N, M;
int Len[100] = {};
int Graph[100][100] = {};

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--;
        v--;
        Graph[u][Len[u]] = v;
        Len[u] += 1;
        Graph[v][Len[v]] = u;
        Len[v] += 1;
    }

    queue<int> q;
    q.push(0);
    bool visited[100] = {};
    int ans = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans++;
        for (int i = 0; i < Len[v]; i++) {
            int u = Graph[v][i];
            if (!visited[u] && u) {
                visited[u] = true;
                q.push(u);
            }
        }
    }

    printf("%d", ans);
    return 0;
}
