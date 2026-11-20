// Problem 1: Password (flip segments) - BFS on difference array + bitmask DP
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k,l;
    scanf("%d %d %d",&n,&k,&l);
    vector<int> s(n+2,0);
    for(int i=0;i<k;i++){int x;scanf("%d",&x);s[x]=1;}
    vector<int> a(l);
    for(auto&v:a)scanf("%d",&v);
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    // d[i] = s[i]^s[i-1], i in 1..n+1 ; flipping [p,p+a-1] toggles d[p], d[p+a]
    vector<int> pos;
    for(int i=1;i<=n+1;i++) if((s[i]^s[i-1])) pos.push_back(i);
    int c=pos.size();
    const int INF=1e9;
    vector<vector<int>> cost(c,vector<int>(c,INF));
    vector<int> dist(n+2);
    for(int i=0;i<c;i++){
        fill(dist.begin(),dist.end(),-1);
        queue<int> q;
        dist[pos[i]]=0;q.push(pos[i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int x:a){
                if(u+x<=n+1&&dist[u+x]<0){dist[u+x]=dist[u]+1;q.push(u+x);}
                if(u-x>=1&&dist[u-x]<0){dist[u-x]=dist[u]+1;q.push(u-x);}
            }
        }
        for(int j=0;j<c;j++) if(dist[pos[j]]>=0) cost[i][j]=dist[pos[j]];
    }
    vector<int> dp(1<<c,INF);
    dp[0]=0;
    for(int m=0;m<(1<<c);m++){
        if(dp[m]>=INF)continue;
        int i=0;
        while(i<c&&(m>>i&1))i++;
        if(i==c)continue;
        for(int j=i+1;j<c;j++){
            if(m>>j&1)continue;
            if(cost[i][j]>=INF)continue;
            int nm=m|(1<<i)|(1<<j);
            dp[nm]=min(dp[nm],dp[m]+cost[i][j]);
        }
    }
    int ans=dp[(1<<c)-1];
    printf("%d\n",ans>=INF?-1:ans);
}
