#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define MAX 1000000000

struct Susi{
    int x;
    size_t hash;
    bool operator<(const Susi& rhs) const{
        return x<rhs.x||(x==rhs.x&&hash<rhs.hash);
    }
};

struct Customer{
    int x;
    size_t hash;
    bool operator<(const Customer& rhs) const{
        return hash<rhs.hash;
    }
    size_t operator()(const Customer& s) const noexcept
    {
        return hash;
    }
};

int L,Q,T=0,R;
map<Susi,int> Susis;
int susis_size=0;
unordered_map<Customer,int,Customer> Customers;

void turn(int T2){
    if(Customers.empty()){
        T=T2;
        return;
    }
    int diff=T2-T;
    Customer temp={};
    for(auto susi=Susis.begin();susi!=Susis.end();){
        int x=susi->first.x;
        temp.hash=susi->first.hash;
        auto found=Customers.find(temp);
        if(found!=Customers.end()){
            auto customer=found->first;
            int from=(x+T)%L;
            int to=(x+T2)%L;
            if(diff<L&&(from<to&&customer.x>from&&customer.x<=to||from>to&&(customer.x>from||customer.x<=to))||diff>=L){
                int decrement=min(susi->second,found->second);
                susi->second-=decrement;
                susis_size-=decrement;
                found->second-=decrement;
                if(found->second<=0) Customers.erase(found);
                if(susi->second<=0){
                    susi=Susis.erase(susi);
                    continue;
                }
            }
        }
        ++susi;
    }
    T=T2;
}

int main() {
    scanf("%d %d",&L,&Q);
    R=(MAX/L+1)*L;
    for(int iq=0;iq<Q;iq++){
        int cmd,t,x,n;
        char name[31];
        scanf("%d",&cmd);
        switch(cmd){
            case 100:{
                Susi s={};
                scanf("%d %d %s",&t,&x,name);
                turn(t-1);
                s.x=(x+R-t)%L;
                susis_size+=1;
                s.hash=hash<string>{}(string(name));
                auto found=Susis.find(s);
                if(found==Susis.end()) Susis.emplace(s,1);
                else found->second+=1;
            }
            break;
            case 200:{
                Customer customer={};
                scanf("%d %d %s %d",&t,&customer.x,name,&n);
                turn(t-1);
                customer.hash=hash<string>{}(string(name));
                Customers.emplace(customer,n);
            }
            break;
            case 300:{
                scanf("%d",&t);
                turn(t);
                printf("%d %d\n",Customers.size(),susis_size);
            }
            break;
        }
    }
    return 0;
}