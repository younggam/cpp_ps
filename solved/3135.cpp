#include <cstring>

using namespace std;

class Node {
public:
    int children[26];
    int stack;
};

Node pool[500000];
int k;

void init() {
    memset(pool[0].children, 0, sizeof(int) * 26);
    k = 1;
}

void insert(int buffer_size, char *buf) {
    Node *cur = &pool[0];
    char i = *buf;
    while (i != '\0') {
        auto id = cur->children[i - 'a'];
        if (id == 0) break;
        auto child = &pool[id];
        child->stack += 1;
        cur = child;
        buf++;
        i = *buf;
    }
    while (i != '\0') {
        auto node = &pool[k];
        memset(node->children, 0, sizeof(int) * 26);
        node->stack = 1;
        cur->children[i - 'a'] = k;
        cur = node;
        k += 1;
        buf++;
        i = *buf;
    }
}

int query(int buffer_size, char *buf) {
    Node *cur = &pool[0];
    char i = *buf;
    while (i != '\0') {
        auto id = cur->children[i - 'a'];
        if (id == 0) break;
        auto child = &pool[id];
        cur = child;
        buf++;
        i = *buf;
    }
    return i == '\0' ? cur->stack : 0;
}