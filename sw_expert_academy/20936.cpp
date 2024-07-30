#include<iostream>
#include<vector>

using namespace std;

int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int n;
        cin >> n;
        auto *boxes = new int[n + 1];
        auto *cells = new int[n + 1];
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            a -= 1;
            boxes[j] = a;
            cells[a] = j;
        }

        int max, b;
        bool nothing = true;
        vector<int> sequence;
        while (true) {
            max = -1, b = -1;
            for (int j = 0; j < n; j++) {
                if (j != boxes[j] && max < j) {
                    max = j;
                    b = cells[j];
                }
            }
            if (max < 0) break;
            nothing = false;
            int c = boxes[b];
            int pc = n;
            while (cells[c] != max) {
                sequence.push_back(cells[c]);
                cells[pc] = pc;
                boxes[pc] = pc;
                pc = c;
                c = cells[c];
            }
            sequence.push_back(max);
            boxes[pc] = pc;
            cells[pc] = pc;
            sequence.push_back(n);
            boxes[c] = c;
            cells[c] = c;
        }

        if (nothing) cout << 0 << endl << endl;
        else {
            cout << sequence.size() << endl;
            for (auto v: sequence) cout << v + 1 << ' ';
            cout << endl;
        }

        t++;
        delete[] boxes;
        delete[] cells;
    }
    return 0;
}
