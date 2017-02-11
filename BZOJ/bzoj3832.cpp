#include<map>
#include<stack>
#include<set>
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
int n,m;
struct edge{
	int to,next;
}e[1234567],e2[1234567];
int cnt2,last2[512345];
int cnt,last[512345],d[512345];
int f[512345],g[512345],tp[512345],C;
multiset<int>ms;
int main(){
	FO(trip);
	n=gi;m=gi;
	for(int i=1,u,v;i<=m;i++){
		u=gi;v=gi;
		e[++cnt]=(edge){v,last[u]};last[u]=cnt;
		d[v]++;
		e2[++cnt2]=(edge){u,last2[v]};last2[v]=cnt2;
	}
	queue<int>q;
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	while(!q.empty()){
		int c=q.front();q.pop();
		tp[++C]=c;
		for(int i=last[c];i;i=e[i].next){
			int b=e[i].to;
			if(!--d[b])q.push(b);
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=last[tp[i]];j;j=e[j].next)
			gmax(f[e[j].to],f[tp[i]]+1);
	for(int i=n;i>=1;i--)
		for(int j=last2[tp[i]];j;j=e2[j].next)
			gmax(g[e2[j].to],g[tp[i]]+1);
	
	for(int i=1;i<=n;i++)ms.insert(g[i]);
	int ans=n+1,sna=n+1;			
	for(int i=1;i<=n;i++){
		int c=tp[i];
		for(int u=last2[c];u;u=e2[u].next)ms.erase(ms.find(1+f[e2[u].to]+g[c]));
		ms.erase(ms.find(g[c]));
		int h=*--ms.end();
		if(h<=ans){
			ans=h;
			sna=min(sna,c);
		} 
		for(int u=last[c];u;u=e[u].next)ms.insert(1+f[c]+g[e[u].to]);
		ms.insert(f[c]);
	} 
	cout<<sna<<' '<<ans;
}
