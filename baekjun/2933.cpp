#include <iostream>
#include <set>
#include <queue>

using namespace std;

void bfs(char *graph, const int H, const int W, const int start, set<int> &visited) {
    queue<int> q;
    q.push(start);
    visited.insert(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (cur % 101 + 1 < W && graph[cur + 1] == 'x' && visited.find(cur + 1) == visited.end()) {
            q.push(cur + 1);
            visited.insert(cur + 1);
        }
        if (cur % 101 - 1 >= 0 && graph[cur - 1] == 'x' && visited.find(cur - 1) == visited.end()) {
            q.push(cur - 1);
            visited.insert(cur - 1);
        }
        if (cur + 101 < H * 101 && graph[cur + 101] == 'x' && visited.find(cur + 101) == visited.end()) {
            q.push(cur + 101);
            visited.insert(cur + 101);
        }
        if (cur - 101 >= 0 && graph[cur - 101] == 'x' && visited.find(cur - 101) == visited.end()) {
            q.push(cur - 101);
            visited.insert(cur - 101);
        }
    }
}

int main(int argc, char **argv) {
    int H, W;
    scanf("%d %d", &H, &W);
    char cave[10100] = {};
    for (int h = H - 1; h >= 0; h--) {
        scanf("%s", &cave[h * 101]);
    }
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int stick;
        scanf("%d", &stick);

        int h = (stick - 1) * 101;
        int w;
        if (i % 2 == 0) {
            for (w = 0; w < W; w++) {
                if (cave[h + w] == 'x') break;
            }
        } else {
            for (w = W - 1; w >= 0; w--) {
                if (cave[h + w] == 'x') break;
            }
        }
        if (w >= W || w < 0) continue;
        int broken = h + w;
        cave[broken] = '.';

        set<int> cluster, cluster1;
        if (broken % 101 + 1 < W && cave[broken + 1] == 'x') {
            bfs(cave, H, W, broken + 1, cluster);
        } else if (broken % 101 - 1 >= 0 && cave[broken - 1] == 'x') {
            bfs(cave, H, W, broken - 1, cluster);
        } else if (broken + 101 < H * 101 && cave[broken + 101] == 'x') {
            bfs(cave, H, W, broken + 101, cluster);
        } else if (broken - 101 >= 0 && cave[broken - 101] == 'x') {
            bfs(cave, H, W, broken - 101, cluster);
        }

        bool grounded = false;
        for (auto a: cluster) grounded |= a / 101 == 0;

        if (grounded) {
            if (broken - 101 >= 0 && cave[broken - 101] == 'x' && cluster.find(broken - 101) == cluster.end()) {
                cluster.clear();
                bfs(cave, H, W, broken - 101, cluster);
            } else if (broken + 101 < H * 101 && cave[broken + 101] == 'x' && cluster.find(broken + 101) == cluster.
                       end()) {
                cluster.clear();
                bfs(cave, H, W, broken + 101, cluster);
            } else if (broken % 101 - 1 >= 0 && cave[broken - 1] == 'x' && cluster.find(broken - 1) == cluster.
                       end()) {
                cluster.clear();
                bfs(cave, H, W, broken - 1, cluster);
            } else if (broken % 101 + 1 < W && cave[broken + 1] == 'x' && cluster.find(broken + 1) == cluster.end()) {
                cluster.clear();
                bfs(cave, H, W, broken + 1, cluster);
            }
        }

        grounded = false;
        for (auto a: cluster) grounded |= a / 101 == 0;

        if (!grounded && !cluster.empty()) {
            int min_d = 101;
            for (auto a: cluster) {
                int aw = a % 101;
                int ah = a / 101;
                for (int top = ah - 1; top >= 0; top--) {
                    if (cave[top * 101 + aw] == 'x' && cluster.find(top * 101 + aw) == cluster.end()) {
                        int d = ah - top - 1;
                        if (min_d > d) min_d = d;
                        break;
                    }
                }
                if (min_d > ah) min_d = ah;
            }

            for (auto a: cluster) {
                cave[a] = '.';
                cave[a - 101 * min_d] = 'x';
            }
        }
    }

    for (int h = H - 1; h >= 0; h--) {
        printf("%s\n", &cave[h * 101]);
    }

    return 0;
}
