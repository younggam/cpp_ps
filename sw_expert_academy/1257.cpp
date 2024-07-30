#include <iostream>

using namespace std;

class Node {
public:
    int stack = 1;
    int children[26] = {};

    bool put(char *str) {
        char toAdd = *str;
        if (toAdd == '\0') return false;
        toAdd -= 'a';

        int child = children[toAdd];
        bool created = false;
        if (child == 0) {
            child = index++;
            children[toAdd] = child;
            pool[child].stack = 1;
            fill_n(pool[child].children, 26, 0);
            created = true;
        }

        created |= pool[child].put(str + 1);
        if (created) stack += 1;
        return created;
    }

    void find_kth(int k, char *output) {
        if (k == 0) {
            *output = '\0';
            return;
        }
        for (char i = 0; i < 26; i++) {
            int child = children[i];
            if (child == 0) continue;
            if (k > pool[child].stack) k -= pool[child].stack;
            else {
                *output = i + 'a';
                pool[child].find_kth(k - 1, output + 1);
                break;
            }
        }
    }

    static Node pool[80201];
    static int index;
};

Node Node::pool[80201] = {};
int Node::index = 0;

void solve(char *str) {
    while (*str != '\0') {
        auto substr = str;
        while (*substr != '\0') {
            substr++;
            char c = *substr;
            *substr = '\0';
            Node::pool[0].put(str);
            *substr = c;
        }
        str++;
    }
}

int main(int argc, char **argv) {
    int T, t = 1;
    scanf("%d", &T);
    char str[401], output[401];
    for (int i = 0; i < T; i++) {
        int K;
        scanf("%d", &K);
        scanf("%s", &str);
        Node::index = 0;
        Node::pool[0].stack = 0;
        fill_n(Node::pool[0].children, 26, 0);
        solve(str);
        if (K > Node::pool[0].stack) {
            output[0] = 'n';
            output[1] = 'o';
            output[2] = 'n';
            output[3] = 'e';
            output[4] = '\0';
        } else Node::pool[0].find_kth(K, output);

        printf("#%d ", t);
        printf("%s\n", output);
        t++;
    }
    return 0;
}