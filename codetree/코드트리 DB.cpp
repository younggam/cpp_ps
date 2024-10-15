#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

struct Data{
    char name[12];
    int val;
};

Data Datas[100000]={};
int dlen=0;
map<size_t,const Data&> nmap;
map<int,const Data&> vmap;
vector<int> kvec;
long long svec[400];

void init(){
    dlen=0;
    nmap.clear();
    vmap.clear();
    kvec.clear();
    fill_n(svec,400,0);
}

int insert(char name[],int nval){
    size_t key=hash<string>{}(string(name));
    if(nmap.find(key)!=nmap.end()||vmap.find(nval)!=vmap.end()) return 0;
    auto& data=Datas[dlen];
    dlen++;
    for(int i=0;i<12;i++){
        data.name[i]=name[i];
        if(name[i]=='\0') break;
    }
    data.val=nval;
    nmap.emplace(key,data);
    vmap.emplace(nval,data);

    int l=0;
    int r=kvec.size();
    int m=(l+r)/2;
    if(r>0){
        while(l!=r&&(r-l!=1||l!=m)){
            if(kvec[m]<nval){
                l=m;
            }else{
                r=m;
            }
            m=(l+r)/2;
        }
        if(kvec[m]>nval)m--;
        kvec.emplace(kvec.begin()+m+1,nval);
        int q=m/250;
        svec[q]+=nval;
        for(int i=q+1;i*250<kvec.size();i++){
            int d=kvec[i*250];
            svec[i-1]-=d;
            svec[i]+=d;
        }
    }else{
        kvec.emplace_back(nval);
        svec[0]+=nval;
    }

    return 1;
}

int del(char name[]){
    size_t key=hash<string>{}(string(name));
    auto nf=nmap.find(key);
    if(nf==nmap.end()) return 0;
    int ret=nf->second.val;
    nmap.erase(nf);
    vmap.erase(vmap.find(ret));

    int l=0;
    int r=kvec.size();
    int m=(l+r)/2;
    if(r>0) {
        while(l!=r&&(r-l!=1||l!=m)){
            if(kvec[m]<ret){
                l=m;
            }else if(kvec[m]>ret){
                r=m;
            }else break;
            m=(l+r)/2;
        }
        kvec.erase(kvec.begin()+m);
        int q=m/250;
        svec[q]-=ret;
        for(int i=q+1;i*250<kvec.size()+1;i++){
            int d=kvec[i*250-1];
            svec[i-1]+=d;
            svec[i]-=d;
        }
    }else {
        kvec.erase(kvec.begin());
        svec[0]-=ret;
    }

    return ret;
}

void rnk(int k,char name[12]){
    if(k<=kvec.size()){
        int val=kvec[k-1];
        auto& d=vmap.find(val)->second;
        for(int i=0;i<12;i++){
            name[i]=d.name[i];
            if(d.name[i]=='\0') break;
        }
    }else{
        name[0]='N';
        name[1]='o';
        name[2]='n';
        name[3]='e';
        name[4]='\0';
    }
}

long long sum(int oval){
    int l=0;
    int r=kvec.size();
    int m=(l+r)/2;
    if(r>0){
        while(l!=r&&(r-l!=1||l!=m)){
            if(kvec[m]<oval){
                l=m;
            }else if(kvec[m]>oval){
                r=m;
            }else break;
            m=(l+r)/2;
        }
        if(kvec[m]>oval)m--;
        long long ret=0;
        for(int i=0;i<m/250;i++){
            ret+=svec[i];
        }
        for(int i=m/250*250;i<=m;i++) ret+=kvec[i];
        return ret;
    }
    else return 0;
}

int main() {
    int Q;
    scanf("%d",&Q);
    for(int q=0;q<Q;q++){
        char cmd[8];
        char name[12];
        int val;
        scanf("%s",cmd);
        if(cmd[0]=='i'&&cmd[2]=='i') init();
        else if(cmd[0]=='i'){
            scanf("%s %d",name,&val);
            printf("%d\n",insert(name,val));
        }else if(cmd[0]=='d'){
            scanf("%s",name);
            printf("%d\n",del(name));
        }else if(cmd[0]=='r'){
            scanf("%d",&val);
            rnk(val,name);
            printf("%s\n",name);
        }else if(cmd[0]=='s'){
            scanf("%d",&val);
            printf("%lld\n",sum(val));
        }
    }
    return 0;
}
