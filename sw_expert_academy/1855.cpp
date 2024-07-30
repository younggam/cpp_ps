#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
public:
    Node() {
        parent = nullptr;
        key = 0;
        depth = 0;
        children = {};
    }

    Node *parent;
    vector<Node *> children;
    int key, depth;

    long bfs(Node **d, const int dn) {
        queue<Node *> q;
        q.push(this);
        long ret = 0;
        Node *prev = nullptr;
        while (!q.empty()) {
            auto cur = q.front();

            if (prev != nullptr) {
                Node *a = prev, *b = cur, *from = prev, *to = cur;
                if (a->depth != b->depth) {
                    if (a->depth > b->depth) {
                        Node *temp = b;
                        b = a;
                        a = temp;
                        to = from;
                        from = temp;
                    }
                    for (int i = dn - 1; i >= 0; i--) {
                        Node *ancestor = d[b->key * dn + i];
                        if (a->depth <= ancestor->depth) {
                            b = d[b->key * dn + i];
                        }
                    }
                }

                Node *lca = a;
                if (a != b) {
                    for (int i = dn - 1; i >= 0; i--) {
                        Node *temp0 = d[a->key * dn + i], *temp1 = d[b->key * dn + i];
                        if (temp0 != temp1) {
                            a = temp0;
                            b = temp1;
                        } else lca = temp0;
                    }
                }
                ret += from->depth - lca->depth + to->depth - lca->depth;
            }

            for (auto child: cur->children) q.push(child);
            prev = cur;
            q.pop();
        }
        return ret;
    }
};


int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int n;
        cin >> n;
        int dn = static_cast<int>(floor(log2l(n))) + 1;
        Node **d = new Node *[n * dn];
        Node *nodes = new Node[n];
        for (int j = 0; j < dn; j++)d[j] = &nodes[0];
        for (int j = 1; j < n; j++) {
            int p;
            cin >> p;
            p -= 1;
            nodes[j].parent = &nodes[p];
            nodes[j].key = j;
            nodes[j].depth = nodes[p].depth + 1;
            nodes[p].children.push_back(&nodes[j]);
            d[j * dn] = &nodes[p];
            for (int k = 1; k < dn; k++) {
                d[j * dn + k] = d[d[j * dn + k - 1]->key * dn + k - 1];
            }
        }
        cout << '#' << t << ' ' << nodes[0].bfs(d, dn) << endl;

        t++;
        delete[] d;
        delete[] nodes;
    }
    return 0;
}
