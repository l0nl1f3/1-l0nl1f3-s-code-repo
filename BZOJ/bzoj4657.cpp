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
#define inf 1000000000 
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define M 55
#define N 101234
#define E 1001234
int a[M][M],sr,T,sum;
struct edge{int to,nxt,cap;}e[E];int lst[N],cnt=1;
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,0);}
int h[N];
int bfs(int s,int t){
	queue<int>q;
	memset(h,-1,sizeof(h));
	q.push(s);h[s]=0;
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=lst[c],b;i;i=e[i].nxt){
			if(h[b=e[i].to]==-1&&e[i].cap>0){
				h[b]=h[c]+1;
				q.push(b);
			}
		}
	}
	return h[t]!=-1;
}
int dfs(int v,int t,int f){
	if(v==t)return f;
	int used=0,w=0;
	for(int i=lst[v],b;i;i=e[i].nxt){
		if(e[i].cap>0&&h[b=e[i].to]==h[v]+1){
			w=dfs(b,t,min(e[i].cap,f-used));
			used+=w;
			e[i^1].cap+=w;
			e[i].cap-=w;
			if(f==used)return f;
		}
	}
	if(!used)h[v]=-1;
	return used;
} 
int max_flow(int s,int t){
	while(bfs(s,t))sum-=dfs(s,t,inf);
	return sum;
}
int n,m;
int main(){
	n=gi;m=gi;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=gi;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]==-1){
				lnk(0,(i-1)*m+j,inf);
				int l=0;
				for(int k=i-1;k;k--)gmax(l,a[k][j]);
				a[i][j]=0;
				for(int k=i;k>1;k--)lnk((k-1)*m+j,(k-2)*m+j,l-a[k][j]);
				sum+=l; 
			}else
			if(a[i][j]==-2){
				lnk(0,(i-1)*m+j,inf);
				int l=0;
				for(int k=i+1;k<=n;k++)gmax(l,a[k][j]);
				a[i][j]=0;
				for(int k=i;k<n;k++)lnk((k-1)*m+j,k*m+j,l-a[k][j]);
				sum+=l; 
			}else
			if(a[i][j]==-3){
				lnk((i-1)*m+j+n*m,2*n*m+1,inf);
				int l=0;
				for(int k=j-1;k;k--)gmax(l,a[i][k]);
				a[i][j]=0;
				for(int k=j;k>1;k--)lnk((i-1)*m+k-1+n*m,(i-1)*m+k+n*m,l-a[i][k]);
				sum+=l; 
			}else
			
			if(a[i][j]==-4){
				lnk((i-1)*m+j+n*m,2*n*m+1,inf);
				int l=0;
				for(int k=j+1;k<=m;k++)gmax(l,a[i][k]);
				a[i][j]=0;
				for(int k=j;k<m;k++)lnk((i-1)*m+k+1+n*m,(i-1)*m+k+n*m,l-a[i][k]);
				sum+=l; 
			}else lnk((i-1)*m+j,(i-1)*m+j+n*m,inf);
		}
	max_flow(0,2*n*m+1);
	printf("%d\n",sum);
	return 0;
}

