#include<cstdio>
#include<iostream>
#include<algorithm>
#define B 2000 
#define N 4000005
#define p 1000000007
#define ll long long
using namespace std;
int n,m,pn,pr[N/10],phi[N],s[N],f[N];
int ls[N],rs[N],bg[N],ps[N],bt[N],cnt;
bool np[N];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
void edt(int r,int d){
	for(int i=r;i<=rs[bg[r]];i++)ps[i]=(ps[i]+d)%p;
	for(int i=bg[r]+1;i<=cnt;++i)bt[i]=(bt[i]+d)%p;
}
int psum(int r){return (ps[r]+bt[bg[r]])%p;}
int query(int n){
	int ans=0;
	for(int i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		ans=(ans+(ll)phi[n/i]*(psum(j)-psum(i-1)+p))%p;
	}
	return ans%p;
}
int main(){
	int i,j,k;
	scanf("%d%d",&m,&n);
	for(phi[1]=1,i=2;i<=n;i++){
		if(!np[i])pr[++pn]=i,phi[i]=i-1;
		for(j=1;j<=pn&&i*pr[j]<=n;j++){
			np[i*pr[j]]=1;
			if(i%pr[j]==0){
				phi[i*pr[j]]=phi[i]*pr[j];
				break;
			}else phi[i*pr[j]]=phi[i]*phi[pr[j]];
		}
	}
	for(cnt=(n+B-1)/B,i=1;i<=cnt;++i)rs[i]=i*B,ls[i]=rs[i]-B+1;
	for(rs[cnt]=n,i=1;i<=n;i++){
		f[i]=(ll)i*i%p;
		ps[i]=(ps[i-1]+f[i])%p;
		phi[i]=((ll)i*i%p*phi[i]+phi[i-1])%p;
		bg[i]=(i-1)/B+1;
	}
	for(i=1;i<=m;i++){
		ll a,b,x,l,g;scanf("%lld%lld%lld%lld",&a,&b,&x,&l);
		g=gcd(a,b);x=x/(a/g)/(b/g);x%=p;
		edt(g,(x-f[g]+p)%p);f[g]=x;
		printf("%d\n",query(l));
	}
}
 
