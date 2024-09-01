#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

struct Coord {
    int x;
    int y;

    bool operator<(const Coord &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

int N;
Coord M[100001];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &M[i].x, &M[i].y);
    }

    sort(M, M + N);

    for (int i = 0; i < N; i++) printf("%d %d\n", M[i].x, M[i].y);
    return 0;
}
