#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;

struct Problem {
    size_t domain;
    int id;
    int t;
    int p;

    bool operator<(const Problem &rhs) const {
        return p < rhs.p || p == rhs.p && t < rhs.t;
    }
};

struct History {
    size_t domain;
    int e;

    bool operator<(const History &rhs) const {
        return e < rhs.e || e == rhs.e && domain < rhs.domain;
    }
};

int Q, N;
map<size_t, set<int> > DomainMap;
set<Problem> pq;
map<size_t, vector<Problem> > stash;
map<size_t, int> Judgings;
size_t Judgers[50001] = {};
int min_jid = 1;
map<size_t, int> Histories;
set<History> Histories_;

bool add_domain_map(size_t domain, int id) {
    bool ret = true;
    auto m = DomainMap.find(domain);
    if (m == DomainMap.end()) DomainMap.emplace(domain, set<int>{id});
    else {
        auto s = m->second.find(id);
        if (s == m->second.end()) m->second.emplace(id);
        else ret = false;
    }
    return ret;
}

void erase_domain_map(size_t domain, int id) {
    auto m = DomainMap.find(domain);
    if (m != DomainMap.end()) {
        auto s = m->second.find(id);
        if (s != m->second.end()) m->second.erase(s);
    }
}

void judge(size_t domain, int t) {
    Judgings.emplace(domain, t);
    for (int i = min_jid; i <= N; i++) {
        if (Judgers[i] > 0) continue;
        Judgers[i] = domain;
        min_jid = i + 1;
        break;
    }
}

void put_stash(Problem problem) {
    auto v = stash.find(problem.domain);
    if (v == stash.end()) stash.emplace(problem.domain, vector<Problem>{problem});
    else v->second.emplace_back(problem);
}

void clean_histroy(int t) {
    for (auto it = Histories_.begin(); it != Histories_.end();) {
        if (it->e > t) break;
        else {
            auto stashed = stash.find(it->domain);
            if (stashed != stash.end()) {
                while (!stashed->second.empty()) {
                    pq.emplace(stashed->second.back());
                    stashed->second.pop_back();
                }
            }
            Histories.erase(it->domain);
            it = Histories_.erase(it);
        }
    }
}

void parse(char *url, int &id) {
    for (int i = 0; i < 32; i++) {
        if (url[i] == '/') {
            url[i] = '\0';
            id = atoi(&url[i + 1]);
            return;
        }
    }
}

int main() {
    scanf("%d", &Q);
    for (int iq = 0; iq < Q; iq++) {
        int cmd, a0, a1, a2;
        char u[32];
        size_t domain;
        scanf("%d", &cmd);
        switch (cmd) {
            case 100:
                scanf("%d %s", &N, &u);
                parse(u, a2);
                domain = hash<string>{}(string(u));
                add_domain_map(domain, a2);
                pq.emplace(Problem{domain, a2, 0, 1});
                break;
            case 200:
                scanf("%d %d %s", &a0, &a1, &u);
                parse(u, a2);
                domain = hash<string>{}(string(u));
                if (add_domain_map(domain, a2)) pq.emplace(Problem{domain, a2, a0, a1});
                break;
            case 300:
                scanf("%d", &a0);
                if (Judgings.size() >= N)break;
                clean_histroy(a0);
                for (auto it = pq.begin(); it != pq.end();) {
                    if (Judgings.find(it->domain) != Judgings.end()) {
                        put_stash(*it);
                        it = pq.erase(it);
                        continue;
                    }
                    auto h = Histories.find(it->domain);
                    if (h == Histories.end()) {
                        judge(it->domain, a0);
                        erase_domain_map(it->domain, it->id);
                        it = pq.erase(it);
                        break;
                    } else {
                        if (a0 > h->second) {
                            judge(it->domain, a0);
                            erase_domain_map(it->domain, it->id);
                            it = pq.erase(it);
                            break;
                        } else {
                            put_stash(*it);
                            it = pq.erase(it);
                            continue;
                        }
                    }
                }
                break;
            case 400: {
                scanf("%d %d", &a0, &a1);
                min_jid = min_jid < a1 ? min_jid : a1;
                auto j = Judgings.find(Judgers[a1]);
                if (j == Judgings.end())break;
                auto s = j->second;
                Judgings.erase(j);
                auto h = Histories.find(Judgers[a1]);
                if (h != Histories.end()) {
                    History k = {h->first, h->second};
                    Histories_.erase(Histories_.find(k));
                    Histories.erase(h);
                }
                Histories.emplace(Judgers[a1], s + 3 * (a0 - s));
                Histories_.emplace(History{Judgers[a1], s + 3 * (a0 - s)});
                Judgers[a1] = 0;
                break;
            }
            case 500:
                scanf("%d", &a0);
                int sum = 0;
                for (auto &v: stash) sum += v.second.size();
                printf("%d\n", pq.size() + sum);
                break;
        }
    }
    return 0;
}
