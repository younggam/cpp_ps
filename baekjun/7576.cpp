#include <iostream>
#include <vector>

using namespace std;

int M, N;
char boxes[1000000];
bool visited[1000000] = {};
int len = 0;
vector<int> ripe[2];

int main(int argc, char **argv) {
    scanf("%d %d", &M, &N);
    int LEN = N * M;
    for (int i = 0; i < LEN; i++) {
        int a;
        scanf("%d", &a);
        boxes[i] = a;
        if (a != 0) {
            visited[i] = true;
            len++;
            if (a == 1)ripe[0].emplace_back(i);
        }
    }
    int day = 0;
    int k = 1;
    int n = 0;
    while (k > 0 && len < LEN && !ripe[day % 2].empty()) {
        k = 0;
        vector<int> &r0 = ripe[day % 2];
        day = day + 1;
        vector<int> &r1 = ripe[day % 2];
        r1.clear();
        for (auto it = r0.begin(); it != r0.end(); ++it) {
            int box = *it;
            if (box + 1 < LEN && box % M != M - 1 && boxes[box + 1] == 0) {
                boxes[box + 1] = 1;
                if (!visited[box + 1]) {
                    k++;
                    len++;
                    r1.emplace_back(box + 1);
                    visited[box + 1] = true;
                }
            }
            if (box - 1 >= 0 && box % M != 0 && boxes[box - 1] == 0) {
                boxes[box - 1] = 1;
                if (!visited[box - 1]) {
                    k++;
                    len++;
                    r1.emplace_back(box - 1);
                    visited[box - 1] = true;
                }
            }
            if (box + M < LEN && boxes[box + M] == 0) {
                boxes[box + M] = 1;
                if (!visited[box + M]) {
                    k++;
                    len++;
                    r1.emplace_back(box + M);
                    visited[box + M] = true;
                }
            }
            if (box - M >= 0 && boxes[box - M] == 0) {
                boxes[box - M] = 1;
                if (!visited[box - M]) {
                    k++;
                    len++;
                    r1.emplace_back(box - M);
                    visited[box - M] = true;
                }
            }
        }
        n++;
    }
    printf("%d", len != LEN ? -1 : n);
    return 0;
}
