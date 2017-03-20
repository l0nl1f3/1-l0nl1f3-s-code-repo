#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 6000
#define M 100000
struct edge{int to,nxt,cap;}e[M];char st[N];queue<int>q;
int n,s,t,B,id,cnt=1,sum,lst[N],h[N],a[N],b[N],w[200][200];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,0);}
bool bfs(){
	memset(h,-1,sizeof(h));
	q.push(s);h[s]=0;
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=lst[c],b;b=e[i].to,i;i=e[i].nxt){
			if(e[i].cap>0&&!~h[b]){
				h[b]=h[c]+1;q.push(b);
			}
		}
	}
	return h[t]!=-1;
}
int dfs(int v,int f){
	if(v==t)return f;
	int w,used=0;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(h[b]==h[v]+1&&e[i].cap>0){
			w=dfs(b,min(e[i].cap,f-used));
			used+=w;
			e[i].cap-=w;e[i^1].cap+=w;
			if(used==f)return used;
		}
	}
	if(!used)h[v]=-1;
	return used;	
}
int dinic(){int s=0;while(bfs())s+=dfs(::s,inf);return s;}
int main(){
	for(int T=gi;T--;memset(lst,0,sizeof(lst)),cnt=1){
		n=gi;scanf("%s",st+1);
		for(int i=0;i<10;i++)a[i]=gi,b[i]=gi; 
		B=n*(n-1)/2;t=B+n+11;sum=id=0;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum+=(i!=j)*(w[i][j]=gi);
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)
			lnk(s,++id,w[i][j]+w[j][i]),lnk(id,B+i,inf),lnk(id,B+j,inf);
		for(int i=1;i<=n;i++){
			lnk(B+i,B+n+st[i]-'0'+1,inf);
			lnk(B+i,t,a[st[i]-'0']); 
		}
		for(int i=0;i<10;i++)lnk(B+n+i+1,t,(b[i]-a[i]));
		printf("%d\n",sum-dinic());
	}
}

