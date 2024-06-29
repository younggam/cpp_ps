#include<iostream>
#include<fstream>

using namespace std;

int solve(const int *inputs, int n) {
    int ret = 0;
    for (int i = 2; i < n - 2; i++) {
        int max = 0;
        if (inputs[i - 2] > max) max = inputs[i - 2];
        if (inputs[i - 1] > max) max = inputs[i - 1];
        if (inputs[i + 1] > max) max = inputs[i + 1];
        if (inputs[i + 2] > max) max = inputs[i + 2];
        ret += std::max(0, inputs[i] - max);
    }
    return ret;
}

int main(int argc, char **argv) {
    ifstream cin("../sample_input.txt");
    // ifstream answer("../sample_output.txt");

    int n, t = 1;
    while (cin >> n) {
        int *inputs = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> inputs[i];
        }
        cout << '#' << t << ' ' << solve(inputs, n) << endl;

        // int result = solve(inputs, n);
        // int a;
        // string skip;
        // answer >> skip >> a;
        // if (result == a) cout << "success" << endl;
        // else cout << a << " != " << result << endl;
        delete[] inputs;
        t++;
    }
    return 0;
}
