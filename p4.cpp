// Problem 4: Network safety. Group edges by c_u^c_v; for each such x the free servers/components count gives 2^(components).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD=1000000007LL;
int par_[500005];
int fnd(int x){
    while(par_[x]!=x){par_[x]=par_[par_[x]];x=par_[x];}
    return x;
}
int main(){
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    vector<ull> c(n+1);
    for(int i=1;i<=n;i++)scanf("%llu",&c[i]);
    vector<ull> key(m);
    vector<int> U(m),V(m);
    for(int i=0;i<m;i++){
        scanf("%d %d",&U[i],&V[i]);
        key[i]=c[U[i]]^c[V[i]];
    }
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){return key[a]<key[b];});
    vector<ll> p2(n+1);
    p2[0]=1;
    for(int i=1;i<=n;i++)p2[i]=p2[i-1]*2%MOD;
    for(int i=1;i<=n;i++)par_[i]=i;
    ll ans=0;
    ll groups=0;
    for(int i=0;i<m;){
        int j=i;
        int merges=0;
        while(j<m&&key[ord[j]]==key[ord[i]]){
            int a=fnd(U[ord[j]]),b=fnd(V[ord[j]]);
            if(a!=b){par_[a]=b;merges++;}
            j++;
        }
        ans=(ans+p2[n-merges])%MOD;
        groups++;
        for(int t=i;t<j;t++){par_[U[ord[t]]]=U[ord[t]];par_[V[ord[t]]]=V[ord[t]];}
        i=j;
    }
    ll pk=1;
    for(int i=0;i<k;i++)pk=pk*2%MOD;
    ll rest=((pk-groups%MOD)%MOD+MOD)%MOD;
    ans=(ans+rest*p2[n])%MOD;
    printf("%lld\n",ans);
}
