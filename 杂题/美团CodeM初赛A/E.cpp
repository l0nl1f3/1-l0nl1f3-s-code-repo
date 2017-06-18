#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){	return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){	return a<b?a=b,1:0;}
#define N 51234
struct query{
	int l,r,k,i;
}qr[N];
int n,q,a[N],f[N],g[N],ans[N];
int gcd(int a,int b){return !b?a:gcd(b,a%b); }
int main(){
	int i,j,k,l,r;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<=q;i++)scanf("%d%d%d",&qr[i].l,&qr[i].r,&qr[i].k),qr[i].i=i;
	for(i=1;i<=q;i++){
		int L=qr[i].l,R=qr[i].r,K=qr[i].k,up=0;
		for(j=L;j<=R;j++)g[a[j]]++,cmax(up,a[j]);
		for(j=1;j<=up;j++)if(g[j])if(gcd(g[j],K)==1)++ans[i];
		for(j=L;j<=R;j++)g[a[j]]=0;
	} 
	for(i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}



