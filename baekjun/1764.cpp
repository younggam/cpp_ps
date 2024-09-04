#include <algorithm>
#include <iostream>

using namespace std;

int N, M;

string names[500000];
string both[500000];

int main() {
    scanf("%d %d", &N, &M);
    char name[20];
    for (int i = 0; i < N; i++) {
        scanf("%s", name);
        names[i] = name;
    }
    sort(names, names + N);
    int n = 0;
    for (int i = 0; i < M; i++) {
        scanf("%s", name);
        if (binary_search(names, names + N, name)) {
            both[n++] = name;
        }
    }
    sort(both, both + n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%s\n", both[i].c_str());
    }
    return 0;
}
