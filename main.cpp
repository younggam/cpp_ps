#include <iostream>
// #include <fstream>

using namespace std;

int solve(int matrix[][64], int N) {
    int ret = 0;
    int *top = matrix[0];
    for (int i = N - 1; i > 0; i--) {
        if (ret % 2 == 0 && top[i] != i + 1 || ret % 2 == 1 && top[i] == i + 1) ret++;
    }
    return ret;
}

int main(int argc, char **argv) {
    // ifstream cin("../1_sample_input.txt");
    // ifstream answer("../1_sample_output.txt");

    int T, t = 1;
    cin >> T;
    int matrix[64][64];
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) cin >> matrix[j][k];
        }

        int result = solve(matrix, N);

        cout << '#' << t << ' ' << result << endl;

        // int a;
        // answer >> a;
        // cout << '#' << t << ' ';
        // if (result == a) cout << "success" << endl;
        // else cout << a << " != " << result << endl;
        t++;
    }
    return 0;
}

// int a;
// string skip;
// answer >> skip >> a;
// cout << '#' << t << ' ';
// if (result == a) cout << "success" << endl;
// else cout << a << " != " << result << endl;
