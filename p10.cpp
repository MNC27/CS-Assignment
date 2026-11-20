// Problem 10: find c, r with f^c(r) = c using <= ~900 queries (baby-step giant-step on the cycle)
#include <bits/stdc++.h>
using namespace std;
int n;
int ask(int c,int r){
    printf("? %d %d\n",c,r);fflush(stdout);
    int h;
    if(scanf("%d",&h)!=1||h<0)exit(0);
    return h;
}
int main(){
    scanf("%d",&n);
    int v=ask(n,1); // f^n(1) lies on a cycle
    int B=1;
    while((long long)B*B<n)B++;
    // baby steps b_i = f^i(v), i = 0..B-1
    unordered_map<int,int> baby;
    baby[v]=0;
    long long L=-1;
    for(int i=1;i<B;i++){
        int w=ask(i,v);
        if(w==v){L=i;break;}
        baby[w]=i;
    }
    if(L<0){
        int g=v;
        for(int kk=1;;kk++){
            g=ask(B,g); // f^{B*kk}(v)
            auto it=baby.find(g);
            if(it!=baby.end()){
                L=(long long)B*kk-it->second;
                break;
            }
        }
    }
    long long j=((L-v%L)%L);
    int r=v;
    if(j>0)r=ask((int)j,v);
    printf("! %d %d\n",v,r);fflush(stdout);
}
