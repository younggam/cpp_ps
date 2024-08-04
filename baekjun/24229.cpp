#include <algorithm>
#include <iostream>

using namespace std;

struct Plank {
    int start;
    int end;
};

bool comp(Plank &a, Plank &b) {
    return a.start < b.start;
}

int main(int argc, char **argv) {
    int N;
    scanf("%d", &N);
    Plank planks[200000];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &planks[i].start, &planks[i].end);
    }

    sort(planks, &planks[N], comp);

    int start = 0, end = 0, k = 0;
    for (int i = 0; i < N; i++) {
        if (end >= planks[i].start) end = max(end, planks[i].end);
        else {
            planks[k].start = start;
            planks[k].end = end;
            start = planks[i].start;
            end = planks[i].end;
            k++;
        }
    }
    planks[k].start = start;
    planks[k].end = end;
    k++;

    int reachable = 0;
    int plank;
    for (int i = 0; i < k; i++) {
        if (reachable >= planks[i].start) {
            plank = i;
            reachable = max(reachable, planks[i].end * 2 - planks[i].start);
        }
    }

    printf("%d\n", planks[plank].end);

    return 0;
}
