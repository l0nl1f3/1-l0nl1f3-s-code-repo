//20161105
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
struct edge{
	int to,next;
}e[2*1501234];
int n,q,cnt,last[1501234],mrk[1501234];
inline int read(){
	int x=0;char ch;
	while(!isdigit(ch=getchar()));
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void print(int x){
	if(!x)return;
	else {
		print(x/10);
		putchar(x%10+'0'); 
	}
}
#define gi read()
void insert(int a,int b){
	e[++cnt]=(edge){b,last[a]};last[a]=cnt;
	e[++cnt]=(edge){a,last[b]};last[b]=cnt;
}
int fa[1501234],F[1501234];
void dfs0(int v,int f=0){
	fa[v]=f;
	for(int i=last[v];i;i=e[i].next){
		if(e[i].to!=f){
			dfs0(e[i].to,v);
		}
	}
}
inline int find(int x){
	if(F[x]!=x)return F[x]=find(F[x]);
	return x;
}
inline void unite(int a,int b){
	int fu=find(a),fv=find(b);
	F[fu]=fv;
}
void dfs1(int v,int f=0){
	if(!mrk[v])unite(v,f);
	for(int i=last[v];i;i=e[i].next){
		if(e[i].to!=f){
			dfs1(e[i].to,v);
		}
	}
}
int opt[1501234],x[1501234],ans[1501234];
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<n;i++){
		int u,v;
		u=gi;v=gi;
		insert(u,v);
	}
	dfs0(1);
	mrk[1]=1;
	for(int i=1;i<=q;i++){
		opt[i]=gi,x[i]=gi;
		if(opt[i]==1)mrk[x[i]]++;
	}
	for(int i=1;i<=n;i++)F[i]=i;
	dfs1(1);
	for(int i=n;i>=1;i--){
		if(opt[i]==1){
			if(!--mrk[x[i]])
			unite(x[i],fa[x[i]]); 
		}
		else{
			ans[i]=find(x[i]);
		}
	}
	for(int i=1;i<=n;i++)if(opt[i]==2)printf("%d\n",ans[i]);
}
