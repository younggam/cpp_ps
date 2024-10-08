#include <iostream>
#include <set>
#include <map>
using namespace std;

struct Rabbit{
    int id;
    int r;
    int c;
    int d;
    int jumped;
    bool operator<(const Rabbit& rhs) const{
        int sl=r+c;
        int sr=rhs.r+rhs.c;
        return jumped<rhs.jumped||jumped==rhs.jumped&&(sl<sr||sl==sr&&(r<rhs.r||r==rhs.r&&(c<rhs.c||c==rhs.c&&id<rhs.id)));
    }
};

struct Moved{
    int id;
    int r;
    int c;
    bool operator>(const Moved& rhs) const{
        int sl=r+c;
        int sr=rhs.r+rhs.c;
        return sl>sr||sl==sr&&(r>rhs.r||r==rhs.r&&(c>rhs.c||c==rhs.c&&id>rhs.id));
    }
};

struct Arrival{
    int r;
    int c;
    bool operator>(const Arrival& rhs) const{
        int sl=r+c;
        int sr=rhs.r+rhs.c;
        return sl>sr||sl==sr&&(r>rhs.r||r==rhs.r&&c>rhs.c);
    }
};

int Q,N,M,P,K,S,L;
long long total_score=0;
map<Rabbit,long long> pq;
map<int,const Rabbit&> rabbits;

int move(int a,int d,int N){
    N--;
    int b=abs((a+d)%(2*N));
    return b>N?2*N-b:b;
}

int main() {
    scanf("%d",&Q);
    for(int iq=0;iq<Q;iq++){
        int cmd;
        scanf("%d",&cmd);
        switch(cmd){
            case 100:
                scanf("%d %d %d",&N,&M,&P);
                for(int p=0;p<P;p++){
                    int pid,d;
                    scanf("%d %d",&pid,&d);
                    auto a=pq.emplace(Rabbit{pid,0,0,d,0},0);
                    rabbits.emplace(pid,a.first->first);
                }
                break;
            case 200:{
                scanf("%d %d",&K,&S);
                Moved moved={};
                for(int k=0;k<K;k++){
                    auto it=pq.begin();
                    auto rabbit=it->first;
                    auto score=it->second;

                    pq.erase(it);
                    rabbits.erase(rabbit.id);

                    Arrival good={0,0},temp;
                    temp.r=move(rabbit.r,rabbit.d,N);
                    temp.c=rabbit.c;
                    if(temp>good) good=temp;
                    temp.r=move(rabbit.r,-rabbit.d,N);
                    if(temp>good) good=temp;
                    temp.r=rabbit.r;
                    temp.c=move(rabbit.c,rabbit.d,M);
                    if(temp>good) good=temp;
                    temp.c=move(rabbit.c,-rabbit.d,M);
                    if(temp>good) good=temp;

                    rabbit.r=good.r;
                    rabbit.c=good.c;
                    rabbit.jumped+=1;
                    int s=good.r+good.c+2;
                    total_score+=s;
                    score-=s;

                    auto a=pq.emplace(rabbit,score).first;
                    rabbits.emplace(a->first.id,a->first);
                    Moved m={rabbit.id,rabbit.r,rabbit.c};
                    if(m>moved) moved=m;
                }
                pq.find(rabbits.find(moved.id)->second)->second+=S;
                break;
            }
            case 300:{
                int pid,L;
                scanf("%d %d",&pid,&L);
                auto it=rabbits.find(pid);
                auto ref_=it->second;
                rabbits.erase(it);

                auto it2=pq.find(ref_);
                auto rabbit=it2->first;
                auto score=it2->second;
                pq.erase(it2);
                rabbit.d*=L;

                auto a=pq.emplace(rabbit,score).first;
                rabbits.emplace(pid,a->first);
                break;
            }
            case 400:{
                long long ans=0;
                for(auto& rabbit:pq) ans=max(ans,rabbit.second);
                printf("%lld",ans+total_score);
                break;
            }
        }
    }
    return 0;
}