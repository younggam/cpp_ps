#include <iostream>
#include <climits>
#include <set>

using namespace std;

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, t = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << '#' << t << ' ';
        int N, M;
        cin >> N >> M;
        int *samples = new int[N];
        set<int> **groups = new set<int> *[N]();
        set<set<int> *> sets;
        for (int j = 0; j < N; j++) samples[j] = INT_MAX;
        for (int j = 0; j < M; j++) {
            char cmd;
            int a, b, w;
            cin >> cmd;
            if (cmd == '!') {
                cin >> a >> b >> w;
                a--;
                b--;
                if (samples[a] == INT_MAX && samples[b] == INT_MAX) {
                    samples[a] = 0;
                    samples[b] = w;
                    auto g = new set<int>{a, b};
                    groups[a] = g;
                    groups[b] = g;
                    sets.insert(g);
                } else if (samples[a] == INT_MAX) {
                    samples[a] = samples[b] - w;
                    groups[a] = groups[b];
                    groups[b]->insert(a);
                } else if (samples[b] == INT_MAX) {
                    samples[b] = w + samples[a];
                    groups[b] = groups[a];
                    groups[a]->insert(b);
                } else if (groups[a] != groups[b]) {
                    int diff = w - samples[b] + samples[a];
                    auto g = groups[b];
                    for (auto v = g->begin(); v != g->end(); ++v) {
                        samples[*v] += diff;
                        groups[*v] = groups[a];
                        groups[a]->insert(*v);
                    }
                    sets.erase(g);
                    delete g;
                }
            } else {
                cin >> a >> b;
                a--;
                b--;
                if (samples[a] == INT_MAX || samples[b] == INT_MAX || groups[a] != groups[b]) {
                    cout << "UNKNOWN" << ' ';
                } else {
                    cout << samples[b] - samples[a] << ' ';
                }
            }
        }
        cout << endl;
        delete[] samples;
        for (auto g: sets) delete g;
        delete[] groups;
        t++;
    }
    return 0;
}