#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000010;
void solve(long long);
bool turnleft(int,int,int);
bool judge(int,int,long long);
long long x[maxn],f[maxn],y[maxn];
int n,m,q[maxn],g[maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,v;i<=n;i++){
		scanf("%d",&v);
		x[i]=x[i-1]+v;
	}
	long long L=1,R=x[n]*x[n];
	while(L<=R){
		long long M=(L+R)>>1;
		solve(M);
		if(g[n]>=m)L=M+1;
		else R=M-1;
	}
	solve(R);
	printf("%lld\n",m*(f[n]-m*R)-x[n]*x[n]);
	return 0;
}
void solve(long long w){
	f[0]=y[0]=0;
	int head=0,tail=0;
	q[tail]=0;
	for(int i=1;i<=n;i++){
		while(head<tail&&judge(q[head],q[head+1],x[i]*2))head++;
		int j=q[head];
		f[i]=f[j]+(x[i]-x[j])*(x[i]-x[j])+w;
		y[i]=f[i]+x[i]*x[i];
		g[i]=g[j]+1;
		while(head<tail&&!turnleft(q[tail-1],q[tail],i))tail--;
		q[++tail]=i;
	}
}
bool turnleft(int a,int b,int c){
	return (long double)(x[b]-x[a])*(y[c]-y[a])-(long double)(x[c]-x[a])*(y[b]-y[a])>1e-15;
}
bool judge(int a,int b,long long k){
	return (y[b]-y[a])<=k*(x[b]-x[a]);
}
