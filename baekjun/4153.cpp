#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    for (;;) {
        scanf("%d %d %d", &a, &b, &c);
        if (a == 0 && b == 0 && c == 0) break;
        a *= a;
        b *= b;
        c *= c;
        printf(a + b == c || a + c == b || b + c == a ? "right\n" : "wrong\n");
    }
    return 0;
}
