// Problem 6: number of strings with same length and letter-sum, minus one
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1000000007LL;
static ll dp[101][2601];
int main(){
    dp[0][0]=1;
    for(int l=1;l<=100;l++){
        for(int s=0;s<=25*l;s++){
            ll v=0;
            for(int c=0;c<=25&&c<=s;c++)v+=dp[l-1][s-c];
            dp[l][s]=v%MOD;
        }
    }
    int t;
    scanf("%d",&t);
    char buf[128];
    while(t--){
        scanf("%s",buf);
        int L=strlen(buf),S=0;
        for(int i=0;i<L;i++)S+=buf[i]-'a';
        printf("%lld\n",(dp[L][S]-1+MOD)%MOD);
    }
}
