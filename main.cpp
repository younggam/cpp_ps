#include <iostream>
// #include <fstream>

using namespace std;

struct Interval {
    int start;
    int end;
};

int solve(Interval *intervals, const int K, const int P) {
    int result = P;
    int first = 0;
    int last = 0;
    int i = 0, left = P, used;
    while (left >= 0 && i < K) {
        Interval interval = intervals[i];
        used = left;
        left -= i == K - 1 ? 1000000 - interval.end : intervals[i + 1].start - interval.end - 1;
        result += interval.end - interval.start + 1;
        i++;
    }
    last = i - 1;
    // printf("%d %d %d %d\n", first, last, used, result);
    int max = result;

    for (i = last; i < K - 1; i++) {
        Interval interval = intervals[i + 1];
        used -= interval.start - intervals[i].end - 1;
        result += interval.end - interval.start + 1;
        // printf("%d %d %d %d\n", first, i + 1, used, result);
        while (used < 0 && first < i + 1) {
            interval = intervals[first];
            result -= interval.end - interval.start + 1;
            used += intervals[first + 1].start - interval.end - 1;
            first++;
            // printf("%d %d %d %d\n", first, i + 1, used, result);
        }
        if (result > max) max = result;
    }

    return max;
}

Interval intervals[200000];

int main(int argc, char **argv) {
    // freopen("../input.txt", "r", stdin);
    // ifstream answer("../output.txt");

    int T, t = 1;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int N, P;
        scanf("%d %d", &N, &P);
        int prev = -10, k = -1;
        for (int j = 0; j < N; j++) {
            int cur;
            scanf("%d", &cur);
            if (cur - prev == 1) intervals[k].end += 1;
            else {
                k++;
                intervals[k].start = cur;
                intervals[k].end = cur;
            }
            prev = cur;
        }

        int result = solve(intervals, k + 1, P);
        printf("#%d ", t);
        printf("%d\n", result);

        // int a;
        // string b;
        // answer >> b >> a;
        // if (a == result) printf("success\n");
        // else printf("%d != %d\n", a, result);
        t++;
    }
    return 0;
}
