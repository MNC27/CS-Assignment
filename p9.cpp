// Problem 9: contacts in last k days - offline, segment tree on type-2 queries + rollback DSU
#include <bits/stdc++.h>
using namespace std;
int n,q,k,m;
vector<pair<int,int>> seg[1<<20];
int p[100005],sz[100005];
vector<int> stk;
vector<int> qz,res;
int SZ;
void addEdge(int node,int l,int r,int a,int b,pair<int,int> e){
    if(a>r||b<l)return;
    if(a<=l&&r<=b){seg[node].push_back(e);return;}
    int mid=(l+r)/2;
    addEdge(node*2,l,mid,a,b,e);
    addEdge(node*2+1,mid+1,r,a,b,e);
}
inline int fnd(int x){while(p[x]!=x)x=p[x];return x;}
void dfs(int node,int l,int r){
    size_t saved=stk.size();
    for(auto&e:seg[node]){
        int a=fnd(e.first),b=fnd(e.second);
        if(a==b)continue;
        if(sz[a]<sz[b])swap(a,b);
        p[b]=a;sz[a]+=sz[b];stk.push_back(b);
    }
    if(l==r){
        res[l]=sz[fnd(qz[l])];
    }else{
        int mid=(l+r)/2;
        dfs(node*2,l,mid);
        dfs(node*2+1,mid+1,r);
    }
    while(stk.size()>saved){
        int b=stk.back();stk.pop_back();
        sz[p[b]]-=sz[b];p[b]=b;
    }
}
int main(){
    scanf("%d %d %d",&n,&q,&k);
    struct E{int x,y,start,day;};
    vector<E> edges;
    vector<int> cnt2AtType3(1,0); // 1-indexed
    int day=0;
    for(int i=0;i<q;i++){
        int t;scanf("%d",&t);
        if(t==1){
            int x,y;scanf("%d %d",&x,&y);
            edges.push_back({x,y,(int)qz.size(),day});
        }else if(t==2){
            int z;scanf("%d",&z);qz.push_back(z);
        }else{
            day++;
            cnt2AtType3.push_back((int)qz.size());
        }
    }
    m=qz.size();
    if(m==0)return 0;
    res.assign(m,0);
    for(int i=1;i<=n;i++){p[i]=i;sz[i]=1;}
    for(auto&e:edges){
        long long expDay=(long long)e.day+k;
        int end=(expDay<(long long)cnt2AtType3.size())?cnt2AtType3[expDay]:m;
        if(e.start<end)addEdge(1,0,m-1,e.start,end-1,{e.x,e.y});
    }
    dfs(1,0,m-1);
    string out;
    for(int i=0;i<m;i++){out+=to_string(res[i]);out+='\n';}
    fputs(out.c_str(),stdout);
}
