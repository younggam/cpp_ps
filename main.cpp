#include <iostream>
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

int main(void) {
    freopen("../sample_input.txt", "r", stdin);
    int TestCase;
    for (scanf("%d", &TestCase); TestCase--;) {
        int Query_N;
        scanf("%d", &Query_N);

        init();

        static int tc = 0;
        printf("#%d", ++tc);

        for (int i = 1; i <= Query_N; i++) {
            int type;
            scanf("%d", &type);

            if (type == 1) {
                char buf[15] = {};
                scanf("%s", buf);

                int buffer_size = 0;
                while (buf[buffer_size]) buffer_size++;

                insert(buffer_size, buf);
            } else {
                char buf[15] = {};
                scanf("%s", buf);

                int buffer_size = 0;
                while (buf[buffer_size]) buffer_size++;

                printf(" %d", query(buffer_size, buf));
            }
        }
        printf("\n");
        fflush(stdout);
    }
}
