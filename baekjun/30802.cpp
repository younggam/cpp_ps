#include <iostream>

using namespace std;

int N, S, M, L, XL, XXL, XXXL, T, P;

int main() {
    scanf("%d", &N);
    scanf("%d %d %d %d %d %d", &S, &M, &L, &XL, &XXL, &XXXL);
    scanf("%d %d", &T, &P);
    printf("%d\n%d %d",
           S / T + (S % T == 0 ? 0 : 1) +
           M / T + (M % T == 0 ? 0 : 1) +
           L / T + (L % T == 0 ? 0 : 1) +
           XL / T + (XL % T == 0 ? 0 : 1) +
           XXL / T + (XXL % T == 0 ? 0 : 1) +
           XXXL / T + (XXXL % T == 0 ? 0 : 1), N / P,
           N % P);
    return 0;
}
