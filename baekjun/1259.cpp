#include <iostream>
#include <cstring>

using namespace std;

char input[6];

int main() {
    for (;;) {
        scanf("%s", &input);
        if (input[0] == '0') break;
        int len = strlen(input);
        int half = len / 2;
        bool all = true;
        for (int i = 0; i < half; i++) {
            all &= input[i] == input[len - i - 1];
        }
        printf(all ? "yes\n" : "no\n");
    }

    return 0;
}
