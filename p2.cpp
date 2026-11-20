// Problem 2: guess b (interactive)
// Query x (random, ~half bits set). Reply o.
//  * o != x  -> operation type is determined, and one bit of v is known exactly:
//      o subset of x  => '&' : v_j = o_j for j in x
//      x subset of o  => '|' : v_j = o_j for j not in x
//    send m0=0, m1=1<<j : r_j = v_j ^ b.
//  * o == x  -> either (& and v ⊇ x) or (| and v ⊆ x). Send m0=0, m1=d with d mixing
//    bits inside/outside x; then r^m0 and r^m1 are the candidates for v and only the
//    true one is (almost surely) of the form "⊇x or ⊆x".
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()^0x9e3779b97f4a7c15ULL);
    const unsigned FULL=(1u<<30)-1;
    int t;
    scanf("%d",&t);
    while(t--){
        unsigned x;
        while(true){
            x=rng()&FULL;
            int pc=__builtin_popcount(x);
            if(pc>=11&&pc<=19)break;
        }
        printf("%u\n",x);fflush(stdout);
        long long o;
        if(scanf("%lld",&o)!=1||o<0)return 0;
        unsigned ou=(unsigned)o;
        unsigned m0=0,m1;
        if(ou!=x){
            int j;
            if((ou&~x)==0){ // '&' world
                j=__builtin_ctz(x);
            }else{          // '|' world
                j=__builtin_ctz(~x&FULL);
            }
            m1=1u<<j;
            printf("%u %u\n",m0,m1);fflush(stdout);
            long long r;
            if(scanf("%lld",&r)!=1||r<0)return 0;
            int b=((r>>j)&1)^((ou>>j)&1);
            printf("%d\n",b);fflush(stdout);
        }else{
            unsigned nx=~x&FULL;
            unsigned d;
            while(true){
                d=rng()&FULL;
                unsigned dx=d&x,dn=d&nx;
                if(dx==0||dx==x||dn==0||dn==nx)continue;
                break;
            }
            m1=d;
            printf("%u %u\n",m0,m1);fflush(stdout);
            long long r;
            if(scanf("%lld",&r)!=1||r<0)return 0;
            unsigned c0=(unsigned)r^m0,c1=(unsigned)r^m1;
            auto ok=[&](unsigned c){return (c&x)==x||(c&nx)==0;};
            bool k0=ok(c0),k1=ok(c1);
            int b;
            if(k0&&!k1)b=0;
            else if(k1&&!k0)b=1;
            else b=rng()&1;
            printf("%d\n",b);fflush(stdout);
        }
    }
}
