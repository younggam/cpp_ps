#include <cmath>
#include <iostream>
#include <set>
#include <climits>

using namespace std;

class Node {
public:
    Node() {
        x = y = 0;
    }

    int x, y;

    int distance(Node *other) {
        return abs(x - other->x) + abs(y - other->y);
    }
};

int solve(Node *nodes, const int n, set<Node *> &unused, Node *cur, Node *last, int d, int &min_d) {
    int ret = INT_MAX;
    set<Node *> u{unused};
    u.erase(cur);
    if (u.empty()) {
        ret = d + cur->distance(last);
        min_d = min(min_d, ret);
    } else {
        for (auto node: u) {
            int a = d + cur->distance(node);
            if (min_d > a) ret = min(ret, solve(nodes, n, u, node, last, a, min_d));
        }
    }
    return ret;
}


int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int n;
        cin >> n;
        n += 2;
        Node *nodes = new Node[n];
        for (int j = 0; j < n; j++) {
            int x, y;
            cin >> x >> y;
            int a = j == 0 ? 0 : j == 1 ? n - 1 : j - 1;
            nodes[a].x = x;
            nodes[a].y = y;
        }
        set<Node *> unused;
        for (int j = 0; j < n - 1; j++) unused.insert(&nodes[j]);
        int min_d = INT_MAX;
        cout << '#' << t << ' ' << solve(nodes, n, unused, &nodes[0], &nodes[n - 1], 0, min_d) << endl;

        t++;
        delete[] nodes;
    }
    return 0;
}
