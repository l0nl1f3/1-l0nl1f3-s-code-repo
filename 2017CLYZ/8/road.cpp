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
#define min(a,b)  ((a)<(b)?(a):(b))
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 12345
#define M 21234
#define K (1<<8)+3
int n,m,d,D,ans=inf;
struct edge{int to,nxt,v;}e[M];
int cnt,lst[N],inq[N],f[N][300],g[300];queue<int>q;
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,c);}
void spfa(int S){
	while(!q.empty()){
		int c=q.front();q.pop();inq[c]=0;
		for(int i=lst[c],b;i;i=e[i].nxt){
			if(f[b=e[i].to][S]>f[c][S]+e[i].v){
				f[b][S]=f[c][S]+e[i].v;
				if(!inq[b])q.push(b),inq[b]=1; 
			}
		}
	}
}
bool chk(int S){for(int i=1;i<=d;i++)if((S>>(i-1)&1)^(S>>(D-i)&1))return 0;return 1;}
int main(){
	FO(road);
	n=gi;m=gi;d=gi;D=d+d;
	for(int i=1,x,y,z;i<=m;i++)x=gi,y=gi,z=gi,lnk(x,y,z);
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	for(int i=1;i<=d;i++)f[i][1<<i-1]=f[n-i+1][1<<D-i]=0;
	for(int S=0;S<(1<<D);S++){
		for(int x=1;x<=n;x++){
			for(int sub=S;sub;sub=((sub-1)&S))gmin(f[x][S],f[x][sub]+f[x][S^sub]);
			if(f[x][S]<=0x3f3f3f3f)q.push(x);
		}
		spfa(S);	
	}
	for(int S=0;S<(1<<D);S++)if(chk(S))for(int i=1;i<=n;i++)gmin(g[S],f[i][S]);
	for(int S=0;S<(1<<D);S++)for(int sub=S;sub;sub=(sub-1)&S)gmin(g[S],g[sub]+g[S^sub]);
	if(g[(1<<D)-1]>=f[0][0])puts("-1");
	else 	cout<<g[(1<<D)-1];
	return 0;
}

