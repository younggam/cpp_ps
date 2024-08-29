#include <iostream>

using namespace std;

int A, B;

int main() {
    scanf("%d %d", &A, &B);

    int a = A, b = B;
    for (;;) {
        int r = a % b;
        if (r == 0) break;
        a = b;
        b = r;
    }

    printf("%d\n%d", b, A * B / b);
    return 0;
}
