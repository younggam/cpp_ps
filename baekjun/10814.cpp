#include <cstdint>
#include <iostream>
#include <set>

using namespace std;

struct Member {
    uint8_t age;
    char name[100];

    bool operator ()(const Member &a, const Member &b) const {
        return a.age >= b.age;
    }
};

int N;
set<Member, Member> M;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        Member member;
        scanf("%d %s", &member.age, &member.name);
        M.emplace(member);
    }

    for (auto it = M.rbegin(); it != M.rend(); ++it) printf("%d %s\n", it->age, it->name);
    return 0;
}
