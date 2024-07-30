#include <iostream>

using namespace std;

int solve(float *cups, int k) {
    for (int i = 0; i < k; i++) {
        float c0 = cups[0];
        float c1 = cups[1];
        float c2 = cups[2];
        cups[0] -= c0;
        cups[1] += c0;

        cups[1] -= c1;
        cups[0] += c1 * 0.5f;
        cups[2] += c1 * 0.5f;

        cups[2] -= c2;
        cups[1] += c2;
    }
    int ret = 2;
    float max = cups[2];
    if (max <= cups[1]) {
        ret = 1;
        max = cups[1];
    }
    if (max <= cups[0]) ret = 0;
    return ret;
}

int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    float cups[3];
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < 3; j++) {
            char c;
            cin >> c;
            if (c == 'o') cups[j] = 1;
            else cups[j] = 0;
        }
        int k;
        cin >> k;
        int result = solve(cups, k);
        cout << '#' << t << ' ' << result << endl;
        t++;
    }
    return 0;
}
