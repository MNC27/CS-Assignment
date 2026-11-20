// Problem 3: restore password from 3-letter substrings = Eulerian path in directed graph of 2-letter nodes
#include <bits/stdc++.h>
using namespace std;
int id(char c){
    if(c>='a'&&c<='z')return c-'a';
    if(c>='A'&&c<='Z')return 26+c-'A';
    return 52+c-'0';
}
char ch(int i){
    if(i<26)return 'a'+i;
    if(i<52)return 'A'+i-26;
    return '0'+i-52;
}
int main(){
    int n;
    scanf("%d",&n);
    const int V=62*62;
    vector<vector<int>> adj(V);
    vector<int> indeg(V,0),outdeg(V,0);
    char buf[8];
    int startNode=-1;
    for(int i=0;i<n;i++){
        scanf("%s",buf);
        int u=id(buf[0])*62+id(buf[1]);
        int v=id(buf[1])*62+id(buf[2]);
        adj[u].push_back(v);
        outdeg[u]++;indeg[v]++;
        if(startNode<0)startNode=u;
    }
    int s1=-1,e1=-1;
    for(int v=0;v<V;v++){
        int df=outdeg[v]-indeg[v];
        if(df==0)continue;
        if(df==1){ if(s1!=-1){puts("NO");return 0;} s1=v; }
        else if(df==-1){ if(e1!=-1){puts("NO");return 0;} e1=v; }
        else {puts("NO");return 0;}
    }
    if((s1==-1)!=(e1==-1)){puts("NO");return 0;}
    int st=(s1!=-1)?s1:startNode;
    vector<int> ptr(V,0),stk,path;
    stk.push_back(st);
    while(!stk.empty()){
        int u=stk.back();
        if(ptr[u]<(int)adj[u].size()){
            stk.push_back(adj[u][ptr[u]++]);
        }else{
            path.push_back(u);
            stk.pop_back();
        }
    }
    if((int)path.size()!=n+1){puts("NO");return 0;}
    reverse(path.begin(),path.end());
    string res;
    res+=ch(path[0]/62);
    res+=ch(path[0]%62);
    for(int i=1;i<=n;i++)res+=ch(path[i]%62);
    puts("YES");
    puts(res.c_str());
}
