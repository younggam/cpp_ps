#include <iostream>

using namespace std;

class Node {
public:
    int stack = 1;
    Node *children[26] = {nullptr};

    bool put(char *str) {
        char toAdd = *str;
        if (toAdd == '\0') return false;
        toAdd -= 'a';

        Node *child;
        bool created = false;
        if (children[toAdd] == nullptr) {
            child = new Node;
            children[toAdd] = child;
            created = true;
        } else child = children[toAdd];

        created |= child->put(str + 1);
        if (created) stack += 1;
        return created;
    }

    void find_kth(int k, char *output) {
        if (k == 0) {
            *output = '\0';
            return;
        }
        for (char i = 0; i < 26; i++) {
            auto child = children[i];
            if (child == nullptr) continue;
            if (k > child->stack) k -= child->stack;
            else {
                *output = i + 'a';
                child->find_kth(k - 1, output + 1);
                break;
            }
        }
    }

    void free() {
        for (char i = 0; i < 26; i++) {
            auto child = children[i];
            if (child == nullptr) continue;
            child->free();
            children[i] = nullptr;
            delete child;
        }
    }
};

void solve(Node *root, char *str) {
    while (*str != '\0') {
        auto substr = str;
        while (*substr != '\0') {
            substr++;
            char c = *substr;
            *substr = '\0';
            root->put(str);
            *substr = c;
        }
        str++;
    }
}

int main(int argc, char **argv) {
    int T, t = 1;
    scanf("%d", &T);
    char str[401], output[401];
    Node root{0};
    for (int i = 0; i < T; i++) {
        int K;
        scanf("%d", &K);
        scanf("%s", &str);
        solve(&root, str);
        if (K > root.stack) {
            output[0] = 'n';
            output[1] = 'o';
            output[2] = 'n';
            output[3] = 'e';
            output[4] = '\0';
        } else root.find_kth(K, output);

        printf("#%d ", t);
        printf("%s\n", output);
        t++;
        root.free();
    }
    return 0;
}
