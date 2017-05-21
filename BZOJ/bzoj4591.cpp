#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define p 2333
int f[p],inv[p],s[p][p];
int c(ll n,ll m){
    if(!m)return 1;
    if(n<m)return 0;
    if(n<p&&m<p)return f[n]*inv[m]%p*inv[n-m]%p;
    return c(n/p,m/p)*c(n%p,m%p)%p;
}
int exp(int a,int n){
    int res=1;
    for(;n;n>>=1,a*=a%=p)
        if(n&1)res*=a%=p;
    return res;
}
int cnp(ll n,ll k){
    if(k<0)return 0;
    return (cnp(n/p,k/p-1)*s[n%p][p-1]%p+c(n/p,k/p)*s[n%p][k%p]%p)%p;
}
int main(){
    int i,j;
    for(i=f[1]=s[0][0]=1,i++;i<p;i++)f[i]=f[i-1]*i%p;
    for(inv[i=p-1]=exp(f[p-1],p-2);i;i--)inv[i-1]=inv[i]*i%p;
    for(i=0;i<p;i++)for(j=s[i][0]=1;j<p;j++)s[i][j]=(s[i][j-1]+c(i,j))%p;
    scanf("%d",&j);
    while(j--){
        ll n,k;
        scanf("%lld%lld",&n,&k);
        printf("%d\n",cnp(n,k));
    } 
    return 0;
} 
