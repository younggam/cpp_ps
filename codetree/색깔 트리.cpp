#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int p_id;
    int id;
    short color;
    short max_depth;
    vector<int> children;
};

Node nodes[100001] = {};
int roots[100000] = {};
int root_len = 0;

int traverse(const Node &node, char &r, char &o, char &y, char &g, char &b) {
    int ret = 0;
    for (auto &c: node.children) {
        char cr = 0, co = 0, cy = 0, cg = 0, cb = 0;
        ret += traverse(nodes[c], cr, co, cy, cg, cb);
        r |= cr, o |= co, y |= cy, g |= cg, b |= cb;
    }
    switch (node.color) {
        case 1:
            r = 1;
            break;
        case 2:
            o = 1;
            break;
        case 3:
            y = 1;
            break;
        case 4:
            g = 1;
            break;
        case 5:
            b = 1;
            break;
    }
    int temp = r + o + y + g + b;
    ret += temp * temp;
    return ret;
}

void set_color(Node &node, short color) {
    node.color = color;
    for (auto &c: node.children)set_color(nodes[c], color);
}

int main() {
    int Q;
    scanf("%d", &Q);
    for (int iq = 0; iq < Q; iq++) {
        int cmd;
        scanf("%d", &cmd);
        int m_id, p_id;
        short color, max_depth;
        switch (cmd) {
            case 100: {
                scanf("%d %d %hd %hd", &m_id, &p_id, &color, &max_depth);
                bool add = false;
                if (p_id > 0) {
                    int id = p_id;
                    int depth = 1;
                    for (;;) {
                        auto &n = nodes[id];
                        if (n.p_id == 0) {
                            nodes[p_id].children.emplace_back(m_id);
                            add = true;
                            break;
                        } else if (n.max_depth <= depth) {
                            break;
                        }
                        id = n.p_id;
                        depth++;
                    }
                } else {
                    add = true;
                    roots[root_len++] = m_id;
                }
                if (add) {
                    nodes[m_id] = {p_id, m_id, color, max_depth};
                }
            }
            break;
            case 200:
                scanf("%d %hd", &m_id, &color);
                set_color(nodes[m_id], color);
                break;
            case 300:
                scanf("%d", &m_id);
                printf("%hd\n", nodes[m_id].color);
                break;
            case 400:
                int ans = 0;
                for (int i = 0; i < root_len; i++) {
                    char r = 0, o = 0, y = 0, g = 0, b = 0;
                    ans += traverse(nodes[roots[i]], r, o, y, g, b);
                }
                printf("%d\n", ans);
                break;
        }
    }
    return 0;
}
