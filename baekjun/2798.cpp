#include <iostream>

using namespace std;

int N, M, CARDS[100];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &CARDS[i]);
    }
    int max = 0;
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            for (int k = j + 1; k < N; k++) {
                int temp = CARDS[i] + CARDS[j] + CARDS[k];
                max = temp > M || max > temp ? max : temp;
            }
        }
    }
    printf("%d", max);
}
