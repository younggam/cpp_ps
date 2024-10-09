#include <iostream>
#include <vector>
using namespace std;

struct Present{
    int prev;
    int next;
};

int Q,N,M;
int Heads[100001]={};
int Tails[100001]={};
int Lens[100001]={};
Present Presents[100001]={};


int main() {
    scanf("%d",&Q);
    for(int iq=0;iq<Q;iq++){
        int cmd,src,dest,num;
        scanf("%d",&cmd);
        switch(cmd){
            case 100:{
                scanf("%d %d",&N,&M);
                for(int m=1;m<=M;m++){
                    int n;
                    scanf("%d",&n);
                    if(Heads[n]==0)Heads[n]=m;
                    if(Tails[n]!=0){
                        Presents[Tails[n]].next=m;
                        Presents[m].prev=Tails[n];
                    }
                    Tails[n]=m;
                    Lens[n]+=1;
                }
                break;
            }
            case 200:{
                scanf("%d %d",&src,&dest);
                if(Lens[src]>0){
                    Presents[Heads[dest]].prev=Tails[src];
                    Presents[Tails[src]].next=Heads[dest];
                    Heads[dest]=Heads[src];
                    Heads[src]=0;
                    if(Lens[dest]==0)Tails[dest]=Tails[src];
                    Tails[src]=0;
                    Lens[dest]+=Lens[src];
                    Lens[src]=0;
                }
                printf("%d\n",Lens[dest]);
                break;
            }
            case 300:{
                scanf("%d %d",&src,&dest);
                int sh=0;
                int dh=0;
                if(Lens[src]>0){
                    sh=Heads[src];
                    Heads[src]=Presents[sh].next;
                    Presents[Heads[src]].prev=0;
                    if(Lens[src]==1){
                        Presents[Tails[src]].prev=0;
                        Tails[src]=0;
                    }
                    Lens[src]-=1;
                }
                if(Lens[dest]>0){
                    dh=Heads[dest];
                    Heads[dest]=Presents[dh].next;
                    Presents[Heads[dest]].prev=0;
                    if(Lens[dest]==1){
                        Presents[Tails[dest]].prev=0;
                        Tails[dest]=0;
                    }
                    Lens[dest]-=1;
                }
                if(sh>0){
                    Presents[Heads[dest]].prev=sh;
                    Presents[sh].next=Heads[dest];
                    Heads[dest]=sh;
                    if(Lens[dest]==0)Tails[dest]=sh;
                    Lens[dest]+=1;
                }
                if(dh>0){
                    Presents[Heads[src]].prev=dh;
                    Presents[dh].next=Heads[src];
                    Heads[src]=dh;
                    if(Lens[src]==0)Tails[src]=dh;
                    Lens[src]+=1;
                }
                printf("%d\n",Lens[dest]);
                break;
            }
            case 400:{
                scanf("%d %d",&src,&dest);
                int amount=Lens[src]/2;
                int end=Heads[src];
                for(int i=0;i<amount-1;i++){
                    end=Presents[end].next;
                }
                if(amount>0){
                    Presents[Heads[dest]].prev=end;
                    int temp=Presents[end].next;
                    Presents[end].next=Heads[dest];
                    Heads[dest]=Heads[src];
                    Heads[src]=temp;
                    Presents[Heads[src]].prev=0;
                    if(Lens[dest]==0)Tails[dest]=end;
                    Lens[dest]+=amount;
                    Lens[src]-=amount;
                }
                printf("%d\n",Lens[dest]);
                break;
            }
            case 500:{
                scanf("%d",&num);
                auto& p=Presents[num];
                int a=p.prev>0?p.prev:-1;
                int b=p.next>0?p.next:-1;
                printf("%d\n",a+2*b);
                break;
            }
            case 600:{
                scanf("%d",&num);
                int c=Lens[num];
                int a=c>0?Heads[num]:-1;
                int b=c>0?Tails[num]:-1;
                printf("%d\n",a+2*b+3*c);
                break;
            }
        }
        Presents[0]={};
    }
    return 0;
}