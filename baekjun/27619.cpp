#include <iostream>
#include <set>

using namespace std;

class Node {
public:
    int parent;
    int depart;
    int depth;
    set<int> children;

    void add_child(int child) {
        children.insert(child);
    }

    bool find_child(int child) {
        return children.find(child) != children.end();
    }
};

int str_decimal(const char *str, int n) {
    int place = 1;
    int ret = 0;
    for (int i = n - 1; i >= 0; i--) {
        ret += place * (str[i] - '0');
        place *= 10;
    }
    return ret;
}

Node chart[100001] = {};
int used = 1;
int map[1000001] = {};

int main(int argc, char **argv) {
    char c, prev_c = '\0';
    char number[7];
    int ni = 0; {
        int parent = -1;
        do {
            prev_c = c;
            c = getchar();
            int depart;
            switch (c) {
                case '(':
                    if (ni > 0) {
                        depart = str_decimal(number, ni);
                        ni = 0;
                        Node &newNode = chart[used];
                        map[depart] = used;
                        newNode.depart = depart;
                        if (parent >= 0) {
                            newNode.parent = parent;
                            chart[parent].add_child(depart);
                        } else newNode.parent = -1;
                        parent = used++;
                    }
                    break;
                case ')':
                    if (ni > 0) {
                        depart = str_decimal(number, ni);
                        ni = 0;
                        Node &newNode = chart[used];
                        map[depart] = used;
                        newNode.depart = depart;
                        if (parent >= 0) {
                            newNode.parent = parent;
                            chart[parent].add_child(depart);
                        } else newNode.parent = -1;
                        used++;
                    } else {
                        if (parent >= 0) parent = chart[parent].parent;
                    }
                    break;
                case ' ':
                    break;
                default:
                    if ((prev_c == ' ' || c == '\0' || c == '\n') && ni > 0) {
                        depart = str_decimal(number, ni);
                        ni = 0;
                        Node &newNode = chart[used];
                        map[depart] = used;
                        newNode.depart = depart;
                        if (parent >= 0) {
                            newNode.parent = parent;
                            chart[parent].add_child(depart);
                        } else newNode.parent = -1;
                        used++;
                    }
                    number[ni++] = c;
                    break;
            }
        } while (c != '\0' && c != '\n');
    }
    int count = 1;
    ni = 0; {
        prev_c = '\0';
        int parent = -1;
        do {
            prev_c = c;
            c = getchar();
            int depart;
            switch (c) {
                case '(':
                    if (ni > 0) {
                        depart = str_decimal(number, ni);
                        ni = 0;
                        count++;
                        Node &node = chart[map[depart]];
                        if (node.depart != depart || parent >= 0 && !chart[parent].find_child(depart)) goto no;
                        parent = map[depart];
                    }
                    break;
                case ')':
                    if (ni > 0) {
                        depart = str_decimal(number, ni);
                        ni = 0;
                        count++;
                        Node &node = chart[map[depart]];
                        if (node.depart != depart || parent >= 0 && !chart[parent].find_child(depart)) goto no;
                        parent = node.parent;
                    } else {
                        if (parent >= 0) parent = chart[parent].parent;
                    }
                    break;
                case ' ':
                    break;
                default:
                    if ((prev_c == ' ' || c == '\0' || c == '\n') && ni > 0) {
                        depart = str_decimal(number, ni);
                        ni = 0;
                        count++;
                        Node &node = chart[map[depart]];
                        if (node.depart != depart || parent >= 0 && !chart[parent].find_child(depart)) goto no;
                    }
                    number[ni++] = c;
                    break;
            }
        } while (c != '\0' && c != '\n');
    }
    if (count == used) {
        printf("Yes\n");
        return 0;
    }
no:
    printf("No\n");
    return 0;
}
