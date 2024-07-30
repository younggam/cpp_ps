#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    int T, t = 1;
    cin >> T;
    char inputs[2000][500];
    for (int i = 0; i < T; i++) {
        int V, H;
        cin >> V >> H;
        for (int r = 0; r < V; r++) {
            for (int c = 0; c < H; c++) {
                char hex;
                cin >> hex;
                if ('0' <= hex && hex <= '9') hex -= '0';
                else if ('A' <= hex && hex <= 'F') hex -= 'A' - 10;
                else hex = 0;
                inputs[r][c] = hex;
                if (hex != 0 && r > 0)inputs[r - 1][c] = 0;
            }
        }
        vector<int> codes;
        for (int r = 0; r < V; r++) {
            for (int c = H - 1; c >= 0; c--) {
                if (inputs[r][c] != 0 && (r + 1 >= V || inputs[r + 1][c] == 0) && (
                        c + 1 >= H || inputs[r][c + 1] == 0)) {
                    codes.push_back(r);
                    codes.push_back(c);
                    char *line = inputs[r];
                    int a = 0, b = c;
                    int x = 0, y = 0, z = 0, w = 0;
                    while (a < 5 && b >= 0) {
                        for (int j = 0; j < 4; j++) {
                            if ((line[b] & 1 << j) == 0) {
                                if (a == 1 || a == 3) a++;
                                if (a == 2) y++;
                                else if (a == 4) w++;
                            } else {
                                if (a == 0 || a == 2 || a == 4)a++;
                                if (a == 1) x++;
                                else if (a == 3) z++;
                            }
                        }
                        b--;
                    }
                    int step = (x + y + z + w) / 7;
                    char shift, bring = 0;
                    for (shift = 0; shift < 4; shift++) {
                        if ((line[c] & 1 << shift) > 0) break;
                        bring += 1 << shift;
                    }
                    int len = 0;
                    do {
                        len += 14;
                        if (shift == 0) c -= 14;
                        else {
                            for (int j = 0; j < 14; j++, c--) {
                                line[c] >>= shift;
                                char b = inputs[r][c - 1] & bring;
                                line[c] += b << 4 - shift;
                                line[c - 1] -= b;
                            }
                        }
                        step--;
                    } while (c >= 14 && step > 0);
                    codes.push_back(len);
                }
            }
        }
        int result = 0;
        for (auto it = codes.begin(); it < codes.end(); it += 3) {
            char *line = inputs[*it];
            int len = *(it + 2);
            int c = *(it + 1);
            int step = len / 14;
            int code[8];
            int valid = 0, accum = 0;
            for (int j = 0; j < 8; j++) {
                int a = 0;
                int x = 0, y = 0, z = 0, w = 0;
                for (int k = 0; k < 7; k++) {
                    int l = (j * 7 + k) * step;
                    if ((line[c - l / 4] & 1 << l % 4) == 0) {
                        if (a == 0 || a == 2)a++;
                        if (a == 1) z++;
                        else if (a == 3) x++;
                    } else {
                        if (a == 1) a++;
                        if (a == 0) w++;
                        else if (a == 2) y++;
                    }
                }
                if (x == 3 && y == 2 && z == 1 && w == 1)code[j] = 0;
                else if (x == 2 && y == 2 && z == 2 && w == 1)code[j] = 1;
                else if (x == 2 && y == 1 && z == 2 && w == 2)code[j] = 2;
                else if (x == 1 && y == 4 && z == 1 && w == 1)code[j] = 3;
                else if (x == 1 && y == 1 && z == 3 && w == 2)code[j] = 4;
                else if (x == 1 && y == 2 && z == 3 && w == 1)code[j] = 5;
                else if (x == 1 && y == 1 && z == 1 && w == 4)code[j] = 6;
                else if (x == 1 && y == 3 && z == 1 && w == 2)code[j] = 7;
                else if (x == 1 && y == 2 && z == 1 && w == 3)code[j] = 8;
                else if (x == 3 && y == 1 && z == 1 && w == 2)code[j] = 9;
                if (j % 2 == 1)valid += 3 * code[j];
                else valid += code[j];
                accum += code[j];
            }
            if (valid % 10 == 0) result += accum;
        }
        cout << '#' << t << ' ' << result << endl;
        t++;
    }
    return 0;
}
