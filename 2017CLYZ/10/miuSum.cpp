#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
#define rep(i,a) for(i=first[a];i;i=next[i])
using namespace std;
typedef long long ll;
const int maxn=5000007,mo=857777;
int i,j,k,l,t,n,m,miu[maxn],p[maxn],sum[maxn];
ll a,b,ans,chang[mo];
int next[mo],last[mo],first[mo],num;
bool bz[maxn];
void add(int x,int y,ll z){
    last[++num]=y;next[num]=first[x];first[x]=num;chang[num]=z;
}
int suan(ll x){
    int i,j=x%mo,k=1;ll l=2,r;
    if(x<=maxn)return sum[x];
    rep(i,j)if(last[i]==x)return chang[i];
    while(l<=x){
        r=x/(x/l);
        k-=(r-l+1)*suan(x/l);
        l=r+1;
    }
    add(j,x,k);
    return k;
}
int main(){
    scanf("%lld%lld",&a,&b);
    miu[1]=1;
    fo(i,2,maxn){
        if(!bz[i]){
            miu[i]=-1;
            p[++p[0]]=i;
        }
        fo(j,1,p[0]){
            t=i*p[j];if(t>maxn)break;bz[t]=1;
            if(!(i%p[j])){break;}
            miu[t]=-miu[i]; 
        }
    }
    fo(i,1,maxn)sum[i]=sum[i-1]+miu[i];
    printf("%d",suan(b)-suan(a-1));
}
