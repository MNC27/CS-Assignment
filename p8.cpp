// Problem 8: offline dynamic bipartiteness - segment tree on time + DSU with parity and rollback
#include <bits/stdc++.h>
using namespace std;
int n,q;
vector<pair<int,int>> seg[400005];
int p[100005],sz[100005];
char dpar[100005];
vector<int> stk;
char ans[100005];
void addEdge(int node,int l,int r,int a,int b,pair<int,int> e){
    if(a>r||b<l)return;
    if(a<=l&&r<=b){seg[node].push_back(e);return;}
    int m=(l+r)/2;
    addEdge(node*2,l,m,a,b,e);
    addEdge(node*2+1,m+1,r,a,b,e);
}
inline int fnd(int x,int &par){
    par=0;
    while(p[x]!=x){par^=dpar[x];x=p[x];}
    return x;
}
void rollback(size_t to){
    while(stk.size()>to){
        int rs=stk.back();stk.pop_back();
        sz[p[rs]]-=sz[rs];
        p[rs]=rs;dpar[rs]=0;
    }
}
void dfs(int node,int l,int r){
    size_t saved=stk.size();
    bool bad=false;
    for(auto&e:seg[node]){
        int pa,pb;
        int ra=fnd(e.first,pa),rb=fnd(e.second,pb);
        if(ra==rb){
            if(pa==pb){bad=true;break;}
        }else{
            if(sz[ra]<sz[rb]){swap(ra,rb);swap(pa,pb);}
            p[rb]=ra;dpar[rb]=pa^pb^1;sz[ra]+=sz[rb];
            stk.push_back(rb);
        }
    }
    if(bad){
        for(int i=l;i<=r;i++)ans[i]=0;
    }else if(l==r){
        ans[l]=1;
    }else{
        int m=(l+r)/2;
        dfs(node*2,l,m);
        dfs(node*2+1,m+1,r);
    }
    rollback(saved);
}
int main(){
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){p[i]=i;sz[i]=1;dpar[i]=0;}
    map<pair<int,int>,int> open;
    for(int i=0;i<q;i++){
        int x,y;scanf("%d %d",&x,&y);
        auto it=open.find({x,y});
        if(it==open.end())open[{x,y}]=i;
        else{
            addEdge(1,0,q-1,it->second,i-1,{x,y});
            open.erase(it);
        }
    }
    for(auto&kv:open)addEdge(1,0,q-1,kv.second,q-1,kv.first);
    dfs(1,0,q-1);
    for(int i=0;i<q;i++)puts(ans[i]?"YES":"NO");
}
