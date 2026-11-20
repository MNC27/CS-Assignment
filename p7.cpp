// Problem 7: max sum of mex over all pairs in a tree
// dp[u][v] = sub_v(u)*sub_u(v) + max(dp[par_v(u)][v], dp[u][par_u(v)])
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
vector<vector<int>> g;
vector<vector<short>> par,sub;
vector<vector<ll>> dp;
ll solve(int u,int v){
    if(u==v)return 0;
    ll &r=dp[u][v];
    if(r>=0)return r;
    ll best=max(solve(par[v][u],v),solve(u,par[u][v]));
    return r=best+(ll)sub[v][u]*sub[u][v];
}
int main(){
    scanf("%d",&n);
    g.assign(n,{});
    for(int i=0;i<n-1;i++){
        int a,b;scanf("%d %d",&a,&b);a--;b--;
        g[a].push_back(b);g[b].push_back(a);
    }
    par.assign(n,vector<short>(n,-1));
    sub.assign(n,vector<short>(n,1));
    vector<int> order;
    for(int r=0;r<n;r++){
        order.clear();
        order.push_back(r);
        par[r][r]=-1;
        for(size_t i=0;i<order.size();i++){
            int u=order[i];
            for(int v:g[u])if(v!=par[r][u]){par[r][v]=u;order.push_back(v);}
        }
        for(int i=n-1;i>0;i--){
            int u=order[i];
            sub[r][par[r][u]]+=sub[r][u];
        }
    }
    dp.assign(n,vector<ll>(n,-1));
    ll ans=0;
    for(int u=0;u<n;u++)for(int v=u+1;v<n;v++)ans=max(ans,solve(u,v));
    printf("%lld\n",ans);
}
