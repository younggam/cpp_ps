#include <iostream>

using namespace std;

class MeetInfo {
public:
    char a = 0, b = 0;
    float time = 0;
};

int prepare(char inputs[], MeetInfo meetInfos[], const int N) {
    int k = 0;
    for (char i = 0; i < N; i++) {
        for (char j = i + 1; j < N; j++) {
            if (inputs[i] > inputs[j]) {
                meetInfos[k] = {i, j, static_cast<float>(j - i) / static_cast<float>(inputs[i] - inputs[j])};
                k++;
            }
        }
    }
    for (int i = 1; i < k; i++) {
        const MeetInfo temp = meetInfos[i];
        int j = i;
        for (; j > 0 && meetInfos[j - 1].time > temp.time; j--) {
            meetInfos[j] = meetInfos[j - 1];
        }
        meetInfos[j] = temp;
    }
    return k;
}

void solve(MeetInfo meetInfos[], char meetCounts[], bool meets[], const int K, const int i, const int j, const int l) {
    for (int k = i; k < K; k++) {
        char a = meetInfos[k].a, b = meetInfos[k].b;
        if (a == l || b == l) {
            if (!meets[a]) {
                meetCounts[j] += 1;
                meets[a] = true;
            }
            if (!meets[b]) {
                meetCounts[j] += 1;
                meets[b] = true;
            }
            solve(meetInfos, meetCounts, meets, K, k + 1, j, a == l ? b : a);
        }
    }
}

int main(int argc, char **argv) {
    int T, t = 1;
    scanf("%d", &T);
    char inputs[5], meetCounts[5];
    MeetInfo meetInfos[10];
    for (int i = 0; i < T; i++) {
        int N;
        scanf("%d", &N);
        for (int j = 0; j < N; j++) {
            scanf("%hhd", &inputs[j]);
            meetCounts[j] = 0;
        }
        int k = prepare(inputs, meetInfos, N);
        for (int j = 0; j < N; j++) {
            bool meets[5] = {false};
            solve(meetInfos, meetCounts, meets, k, 0, j, j);
        }
        int min = 10, max = 0;
        for (int j = 0; j < N; j++) {
            if (min > meetCounts[j]) min = meetCounts[j];
            if (max < meetCounts[j]) max = meetCounts[j];
        }
        if (min == 0) min++;
        if (max == 0) max++;

        printf("%d %d\n", min, max);
    }
    return 0;
}
