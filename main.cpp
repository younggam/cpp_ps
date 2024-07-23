#include <iostream>
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
