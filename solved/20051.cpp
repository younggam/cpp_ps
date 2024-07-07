#include <iostream>
#include <random>
#include <vector>

using namespace std;

std::mt19937 rng(123);
int temp[3000];

void operate(int *array, int N) {
    int RN = (N + 1) / 2;
    int LN = N / 2;
    for (int i = 0; i < LN; i++) {
        temp[i * 2 + 1] = array[i];
    }
    for (int i = 0; i < RN; i++) {
        temp[i * 2] = array[i + LN];
    }
    copy(temp, temp + N, array);
}

void solve(int *input, int *array, int N, vector<int> &ops) {
    for (int i = N - 1; i >= 0; i--) {
        while (true) {
            int j = 0;
            for (; j < N; j++) {
                if (array[j] == input[i]) {
                    break;
                }
            }
            if (j == i) break;
            int range = min(j + 1, i - j);
            ops.push_back(j - range + 1);
            ops.push_back(j + range);
            operate(&array[j - range + 1], 2 * range);
        }
    }
}


int main(int argc, char **argv) {
    int T, t = 1;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int N;
        scanf("%d", &N);
        int *input = new int[N];
        int *array = new int[N];
        vector<int> ops;
        for (int j = 0; j < N; j++) {
            array[j] = j;
            int a;
            scanf("%d", &a);
            a--;
            input[j] = a;
        }
        for (int rep = 0; rep < 100; rep++) {
            int l = std::uniform_int_distribution<>(0, N - 1)(rng);
            int r = std::uniform_int_distribution<>(0, N - 1)(rng);
            if (l >= r) std::swap(l, r);
            ops.push_back(l);
            ops.push_back(r);
            operate(&array[l], r - l + 1);
        }
        solve(input, array, N, ops);
        int len = ops.size();
        printf("%d\n", len / 2);
        for (int j = len - 2; j >= 0; j -= 2) {
            printf("%d %d\n", ops[j] + 1, ops[j + 1] + 1);
        }

        t++;
        delete[] input;
        delete[] array;
    }
    return 0;
}