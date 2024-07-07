#include <iostream>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    short key;
    short dist;
};

void bfs(vector<short> *graph, short N, short start, int &min) {
    int ret = 0;
    bool *unused = new bool[N]();
    unused[start] = true;
    queue<Node> q;
    q.push(Node{start, 0});
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        ret += cur.dist;
        if (ret >= min) break;
        for (auto n: graph[cur.key]) {
            if (!unused[n]) {
                unused[n] = true;
                q.push(Node{n, static_cast<short>(cur.dist + 1)});
            }
        }
    }
    if (ret < min) {
        min = ret;
    }
    delete[] unused;
}


int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        short N;
        cin >> N;
        vector<short> *graph = new vector<short>[N];
        char e;
        for (short r = 0; r < N; r++) {
            for (short c = 0; c < N; c++) {
                cin >> e;
                if (e != '0') {
                    graph[r].push_back(c);
                }
            }
        }

        int min = INT_MAX;
        for (short j = 0; j < N; j++) {
            bfs(graph, N, j, min);
        }

        cout << '#' << t << ' ' << min << endl;
        t++;
        delete[] graph;
    }
    return 0;
}
