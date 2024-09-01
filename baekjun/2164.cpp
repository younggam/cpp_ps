#include <iostream>

using namespace std;

int N;
int head = 0, tail = 0;
int Card[500001];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        Card[tail] = i;
        tail = (tail + 1) % 500001;
    }
    int ans;
    while (head != tail) {
        ans = Card[head];
        head = (head + 1) % 500001;
        int temp = Card[head];
        head = (head + 1) % 500001;
        Card[tail] = temp;
        tail = (tail + 1) % 500001;
    }
    printf("%d", ans + 1);

    return 0;
}
