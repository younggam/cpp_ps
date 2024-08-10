#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int Primes[59] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23,
    29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
    71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
    113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
    173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
    229, 233, 239, 241, 251, 257, 263, 269, 271, 277
};

class Node {
public:
    int v;
    int parent;
    int64_t label;
    vector<int> children;

    int upwards() {
        return label == 0 ? 1 + nodes[parent].upwards() : 0;
    }

    void dfs_parent(int parent) {
        this->parent = parent;
        for (auto c: children) {
            if (c != parent) nodes[c].dfs_parent(v);
        }
    }

    void dfs_label(int64_t label) {
        this->label *= label;
        for (auto c: children) {
            if (c != parent) nodes[c].dfs_label(this->label);
        }
    }

    static Node nodes[60];
};

Node Node::nodes[60] = {};

int main(int argc, char **argv) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--;
        v--;
        Node::nodes[u].parent = 0;
        Node::nodes[u].children.emplace_back(v);
        Node::nodes[u].v = u;
        Node::nodes[u].label = 0;
        Node::nodes[v].parent = 0;
        Node::nodes[v].children.emplace_back(u);
        Node::nodes[v].v = v;
        Node::nodes[v].label = 0;
    }
    Node::nodes[0].label = 1;
    Node::nodes[0].dfs_parent(-1);
    for (auto p: Primes) {
        int i = -1;
        int longest = 0;
        for (int a = 0; a < N; a++) {
            int upwards = Node::nodes[a].upwards();
            if (upwards > longest) {
                longest = upwards;
                i = a;
            }
        }
        if (i == -1) break;
        while (Node::nodes[i].label == 0) {
            Node::nodes[i].label = p;
            i = Node::nodes[i].parent;
        }
    }
    Node::nodes[0].dfs_label(1);
    for (int i = 0; i < N; i++) printf("%lld ", Node::nodes[i].label);
    printf("\n");
    return 0;
}
