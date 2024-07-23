#include <cstring>

using namespace std;

class Node {
public:
    int children[26];
    int stack;
};

Node pool[250000];
int k;

void init() {
    memset(pool[0].children, 0, sizeof(int) * 26);
    k = 1;
}

void insert(int buffer_size, char *buf) {
    int cur = 0;
    char i = *buf;
    while (i != '\0') {
        auto id = pool[cur].children[i - 'a'];
        if (id == 0) break;
        pool[id].stack += 1;
        cur = id;
        buf++;
        i = *buf;
    }
    while (i != '\0') {
        memset(pool[k].children, 0, sizeof(int) * 26);
        pool[k].stack = 1;
        pool[cur].children[i - 'a'] = k;
        cur = k;
        k += 1;
        buf++;
        i = *buf;
    }
}

int query(int buffer_size, char *buf) {
    int cur = 0;
    char i = *buf;
    while (i != '\0') {
        auto id = pool[cur].children[i - 'a'];
        if (id == 0) break;
        cur = id;
        buf++;
        i = *buf;
    }
    return i == '\0' ? pool[cur].stack : 0;
}