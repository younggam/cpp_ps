#include <iostream>

using namespace std;

#define MOD 1000000009;

int main(int argc, char **argv) {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        int C, S;
        scanf("%d %d", &C, &S);

        int count = 0;
        if (C == 1) {
            count += (S + 2) * (S + 1) / 2;
        } else if (C == 2) {
            count += (S + 2) * (S + 1) / 2;
            count *= count;
        } else {
            for (int a = 0; a <= S; a++) {
                count = (count + (S - a + 1) * (S - a + 1)) % MOD;
            }
            int temp = 0;
            for (int i = 1; S / i >= C - 1; i++) {
                for (int b = i * (C - 1); b <= S; b++) {
                    temp += (S - b + 1) * (S - b + 1 + i);
                }
            }
            count = (count + temp * 2) % MOD
        }

        printf("%d\n", count);
    }

    return 0;
}
