#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define inf 1001001001
#define infll 1001001001001001001LL
#define ll long long
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define Ri register int
#define gc getchar()
#define il inline
il int read(){
	bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;
}
#define gi read()
#define ig read()
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define N 201234 
#define S 20
#define mp make_pair
struct edge{
	int to,next,w;
}e[N];int cnt,last[N];
void insert(int a,int b,int c){
	e[++cnt]=(edge){b,last[a],c};last[a]=cnt;
	e[++cnt]=(edge){a,last[b],c};last[b]=cnt;
}
int in[N],out[N],C,ty[N],val[N],F[N][20],n;
pair<int,int>ec[N];
void dfs(int v,int fa=0){
	in[v]=++C;
	ty[C]=1;
	for(int i=last[v];i;i=e[i].next){
		int b=e[i].to;
		if(b!=fa){
			F[b][0]=v;
			for(int s=1;s<S;s++) F[b][s]=F[F[b][s-1]][s-1];
			dfs(b,v);
			val[in[b]]=e[i].w;
			val[out[b]]=-e[i].w;
		}
	}
	out[v]=++C;
	ty[C]=-1;
}
int L[N*2],R[N*2],mx[N*2],tag[N*2],ct[N*2];
bool al[N*2];
void build(int i,int l,int r){
	L[i]=l;R[i]=r;
	if(l==r){
		ct[i]=(ty[l]==1);
		mx[i]=ct[i]*val[l];
		return;
	}
	build(i*2,l,(l+r)/2);
	build(i*2+1,(l+r)/2+1,r);
	mx[i]=max(mx[i*2],mx[i*2+1]);
}
void pd(int k){
	//...
}
ll query(int k,int l,int r){
	if(l>R[k]||r<L[k])return 0;
	printf("-query(%d,%d)\n",L[k],R[k]);
	if(l<=L[k]&&R[k]<=r){
		printf("~%d\n",mx[k]);
		return mx[k];
	}
	pd(k);
	return max(query(k*2,l,r),query(k*2+1,l,r));
}
void cover(int k,int l,int r,int d){
	if(l>R[k]||r<L[k])return;
	printf("cover(%d,%d)\n",L[k],R[k]);
	if(l<=L[k]&&R[k]<=r){
		printf("~%d\n",mx[k]);
		al[k]=1;
		tag[k]=d;
		mx[k]=d;
		return;
	}
	pd(k);
	cover(k*2,l,r,d);
	cover(k*2+1,l,r,d);
}
void deb(){
	printf("in[]=");for(int i=1;i<=n;i++)printf("%d ",in[i]);
	printf("\nout[]=");
	for(int i=1;i<=n;i++)printf("%d ",out[i]);
	puts("");
	printf("max(%d->%d)=max(%d,%d)",2,4,query(1,in[1],in[4]),query(1,in[1],in[2]));

}
int main(){
	n=gi;
	for(int i=1,u,v,w;i<n;i++){
		u=gi;v=gi;w=gi;
		ec[i]=mp(u,v);
		insert(u,v,w);
	}
	dfs(1);
	build(1,1,n+n);
	deb();
}
