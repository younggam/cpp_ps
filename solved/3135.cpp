#include <cstring>

using namespace std;

class Node {
public:
    int stack;
    Node *children[26] = {nullptr};
};

Node root;
Node pool[1000000];
int k;

void init() {
    memset(pool, 0, sizeof(Node) * k);
    memset(root.children, 0, sizeof root.children);
    k = 0;
}

void insert(int buffer_size, char *buf) {
    Node *cur = &root;
    int i = 0;
    while (i < buffer_size) {
        auto child = cur->children[buf[i] - 'a'];
        if (child == nullptr) break;
        child->stack += 1;
        i++;
        cur = child;
    }
    for (; i < buffer_size; i++) {
        auto node = &pool[k];
        node->stack = 1;
        cur->children[buf[i] - 'a'] = node;
        cur = node;
        k += 1;
    }
}

int query(int buffer_size, char *buf) {
    Node *cur = &root;
    int i = 0;
    while (i < buffer_size) {
        auto child = cur->children[buf[i] - 'a'];
        if (child == nullptr) break;
        i++;
        cur = child;
    }
    return i == buffer_size ? cur->stack : 0;
}