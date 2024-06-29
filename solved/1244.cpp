#include<iostream>
#include<vector>

using namespace std;

int tweak(int val, int a, int b) {
    int c = val % 10, temp = val, dc = 1, dd = 1;
    for (int i = 0; i < a; i++) {
        temp /= 10;
        c = temp % 10;
        dc *= 10;
    }
    int d = val % 10;
    temp = val;
    for (int i = 0; i < b; i++) {
        temp /= 10;
        d = temp % 10;
        dd *= 10;
    }
    val += c * dd - d * dd;
    val += d * dc - c * dc;
    return val;
}

int solve(int v, const int s, const int k) {
    int c = s * (s - 1) / 2;
    int *m = new int[(k + 1) * c]();
    for (int i = 0; i < c; i++) m[i] = v;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < c; j++) {
            int d = 0;
            for (int a = 0; a < s; a++) {
                for (int b = a + 1; b < s; b++) {
                    int val = tweak(m[i * c + j], a, b);
                    if (m[(i + 1) * c + d] < val) m[(i + 1) * c + d] = val;
                    d++;
                }
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < c; i++) {
        if (m[k * c + i] > ret) ret = m[k * c + i];
    }

    delete[] m;
    return ret;
}

int main(int argc, char **argv) {
    int n, t = 1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        vector<int> inputs;
        char c;
        int k;
        cin >> noskipws;
        cin >> c;
        while (cin >> c) {
            if (isspace(c)) break;
            inputs.push_back(c - '0');
        }
        int d = 1, v = 0;
        for (auto it = inputs.rbegin(); it != inputs.rend(); ++it) {
            v += *it * d;
            d *= 10;
        }
        cin >> skipws;
        cin >> k;
        cout << '#' << t << ' ' << solve(v, inputs.size(), k) << endl;
        t++;
    }
    return 0;
}
