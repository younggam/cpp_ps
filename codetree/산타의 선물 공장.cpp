#include <iostream>
#include <map>
using namespace std;

struct Box {
    int id;
    int w;
    int next;
    int prev;
    int m;
};

int Q, N, M;
Box Boxes[100001] = {};
map<int, int> Ids;
int Broken[11];
int Heads[11] = {};
int Tails[11] = {};

void pop_front(int m) {
    if (m <= 0) return;
    int h = Heads[m];
    if (h <= 0) return;
    if (h == Tails[m]) Tails[m] = 0;
    Heads[m] = Boxes[h].next;
    Boxes[Boxes[h].next].prev = 0;
    Boxes[h].prev = 0;
    Boxes[h].next = 0;
}

void push_back(int m, int i) {
    if (m <= 0) return;
    int t = Tails[m];
    Tails[m] = i;
    if (t < 0) return;
    else if (t == 0) Heads[m] = i;
    else Boxes[t].next = i;
    Boxes[i].prev = t;
    Boxes[i].next = 0;
}

int main() {
    scanf("%d", &Q);
    for (int q = 0; q < Q; q++) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
            case 100: {
                scanf("%d %d", &N, &M);
                int K = N / M;
                for (int n = 1; n <= N; n++) {
                    int id;
                    scanf("%d", &id);
                    Ids.emplace(id, n);
                    Boxes[n].id = id;
                    int m = (n - 1) / K + 1;
                    int r = (n - 1) % K;
                    Boxes[n].m = m;
                    if (r == 0) Heads[m] = n;
                    else if (r > 0) {
                        Boxes[n - 1].next = n;
                        Boxes[n].prev = n - 1;
                    }
                    if (r == K - 1) Tails[m] = n;
                }
                for (int n = 1; n <= N; n++) scanf("%d", &Boxes[n].w);
                for (int m = 1; m <= M; m++) Broken[m] = m;
                break;
            }
            case 200: {
                int w;
                long long sum = 0;
                scanf("%d", &w);
                for (int m = 1; m <= M; m++) {
                    int h = Heads[m];
                    if (h <= 0) continue;
                    if (Boxes[h].w <= w) {
                        sum += Boxes[h].w;
                        Ids.find(Boxes[h].id)->second = 0;
                        Boxes[h].id = 0;
                        pop_front(m);
                    } else {
                        pop_front(m);
                        push_back(m, h);
                    }
                }
                printf("%lld\n", sum);
                break;
            }
            case 300: {
                int rid;
                scanf("%d", &rid);
                auto b = Ids.find(rid);
                if (b == Ids.end() || b->second <= 0) printf("-1\n");
                else {
                    auto &box = Boxes[b->second];
                    int next = box.next;
                    int prev = box.prev;
                    if (next > 0) {
                        Boxes[next].prev = prev;
                        box.next = 0;
                    } else {
                        for (int m = 1; m <= M; m++) {
                            if (Tails[m] >= 0 && Boxes[Tails[m]].id == box.id) {
                                Tails[m] = prev;
                                break;
                            }
                        }
                    }
                    if (prev > 0) {
                        Boxes[prev].next = next;
                        box.prev = 0;
                    } else {
                        for (int m = 1; m <= M; m++) {
                            if (Heads[m] >= 0 && Boxes[Heads[m]].id == box.id) {
                                Heads[m] = next;
                                break;
                            }
                        }
                    }

                    Ids.find(box.id)->second = 0;
                    box.id = 0;
                    printf("%d\n", rid);
                }
                break;
            }
            case 400: {
                int fid;
                scanf("%d", &fid);
                auto f = Ids.find(fid);
                if (f == Ids.end() || f->second <= 0) printf("-1\n");
                else {
                    int b = f->second;
                    int m = Broken[Boxes[b].m];
                    while (m != Broken[m]) m = Broken[m];
                    int front = Heads[m];
                    int back = Tails[m];
                    int next = Boxes[b].next;
                    int prev = Boxes[b].prev;
                    if (prev > 0) {
                        Boxes[prev].next = 0;
                        Boxes[b].prev = 0;
                        Boxes[back].next = front;
                        Boxes[front].prev = back;
                        Tails[m] = prev;
                    }
                    Heads[m] = b;
                    printf("%d\n", m);
                }
                break;
            }
            case 500: {
                int bnum;
                scanf("%d", &bnum);
                if (Heads[bnum] < 0) printf("-1\n");
                else {
                    for (int _m = 0; _m < M - 1; _m++) {
                        int m = (bnum + _m) % M + 1;
                        if (Heads[m] >= 0) {
                            Broken[bnum] = m;
                            Boxes[Tails[m]].next = Heads[bnum];
                            Boxes[Heads[bnum]].prev = Tails[m];
                            Tails[m] = Tails[bnum];
                            break;
                        }
                    }
                    Heads[bnum] = -1;
                    Tails[bnum] = -1;
                    printf("%d\n", bnum);
                }
                break;
            }
        }
    }
    return 0;
}
