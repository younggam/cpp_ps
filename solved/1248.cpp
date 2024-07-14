#include <iostream>

using namespace std;

class Node {
public:
    int key = 0;
    int depth = 0;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;

    int preorder() {
        int ret = 1;
        if (left != nullptr) {
            left->depth = depth + 1;
            ret += left->preorder();
        }
        if (right != nullptr) {
            right->depth = depth + 1;
            ret += right->preorder();
        }
        return ret;
    }
};

Node *solve(Node *nodes, int k0, int k1) {
    Node *n0 = &nodes[k0], *n1 = &nodes[k1];
    while (n0 != n1) {
        int diff = n0->depth - n1->depth;
        if (diff >= 0) n0 = n0->parent;
        if (diff <= 0) n1 = n1->parent;
    }
    return n0;
}

int main(int argc, char **argv) {
    Node nodes[10000];
    for (int i = 0; i < 10000; i++) nodes[i].key = i;

    int T, t = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int V, E, k0, k1;
        cin >> V >> E >> k0 >> k1;
        for (int j = 0; j < V; j++) {
            nodes[j].left = nullptr;
            nodes[j].right = nullptr;
            nodes[j].parent = nullptr;
        }
        for (int j = 0; j < E; j++) {
            int v0, v1;
            cin >> v0 >> v1;
            v0--;
            v1--;
            nodes[v1].parent = &nodes[v0];
            if (nodes[v0].left == nullptr) nodes[v0].left = &nodes[v1];
            else nodes[v0].right = &nodes[v1];
        }
        nodes[0].preorder();
        Node *result = solve(nodes, k0 - 1, k1 - 1);
        cout << '#' << t << ' ' << result->key + 1 << ' ' << result->preorder() << endl;
        t++;
    }
    return 0;
}
