// Problem 5: Spy Syndrome 2 - trie of reversed lowercase words + DP over ciphered text
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    static char tbuf[10005];
    scanf("%s",tbuf);
    string t=tbuf;
    int m;
    scanf("%d",&m);
    vector<string> w(m);
    size_t total=0;
    static char buf[1005];
    for(int i=0;i<m;i++){
        scanf("%s",buf);
        w[i]=buf;
        total+=w[i].size();
    }
    vector<array<int,26>> nxt;
    nxt.reserve(total+2);
    array<int,26> empty;empty.fill(-1);
    nxt.push_back(empty);
    vector<int> wid(1,-1);
    for(int i=0;i<m;i++){
        int node=0;
        for(int j=(int)w[i].size()-1;j>=0;j--){
            int c=tolower(w[i][j])-'a';
            if(nxt[node][c]<0){
                nxt[node][c]=nxt.size();
                nxt.push_back(empty);
                wid.push_back(-1);
            }
            node=nxt[node][c];
        }
        if(wid[node]<0)wid[node]=i;
    }
    vector<char> reach(n+1,0);
    vector<int> choice(n+1,-1),len(n+1,0);
    reach[n]=1;
    for(int i=n-1;i>=0;i--){
        int node=0;
        for(int j=i;j<n;j++){
            node=nxt[node][t[j]-'a'];
            if(node<0)break;
            if(wid[node]>=0&&reach[j+1]){
                reach[i]=1;choice[i]=wid[node];len[i]=j+1-i;break;
            }
        }
    }
    string out;
    int i=0;
    while(i<n){
        out+=w[choice[i]];
        i+=len[i];
        if(i<n)out+=' ';
    }
    puts(out.c_str());
}
