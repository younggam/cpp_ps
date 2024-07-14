#include <iostream>

using namespace std;

double solve(int *masses, int *xes, int N, int i) {
    double left_x = xes[i - 1];
    double right_x = xes[i];
    double x = (left_x + right_x) * 0.5;
    while (abs(right_x - left_x) >= 1E-12) {
        double left_f = 0;
        for (int k = 0; k < i; k++) {
            left_f += masses[k] / ((x - xes[k]) * (x - xes[k]));
        }
        double right_f = 0;
        for (int k = i; k < N; k++) {
            right_f += masses[k] / ((x - xes[k]) * (x - xes[k]));
        }
        if (left_f > right_f) {
            double temp = x;
            x = (x + right_x) * 0.5;
            left_x = temp;
        } else if (left_f < right_f) {
            double temp = x;
            x = (left_x + x) * 0.5;
            right_x = temp;
        } else break;
    }
    return x;
}

int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    cout << fixed;
    cout.precision(10);
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        int *masses = new int[N];
        int *xes = new int[N];
        for (int j = 0; j < N; j++) cin >> xes[j];
        for (int j = 0; j < N; j++) cin >> masses[j];

        cout << '#' << t;
        for (int j = 1; j < N; j++) {
            cout << ' ' <<  solve(masses, xes, N, j);
        }
        cout << endl;

        t++;
        delete[] masses;
        delete[] xes;
    }
    return 0;
}