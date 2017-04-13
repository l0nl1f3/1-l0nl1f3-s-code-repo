//f[x][i]=max{f[b][j-1]+g[x][i-j]}
//f[x][i]=max{g[b][j-2]+f[x][i-j]} (j>1)
//g[x][i]=max{g[b][j-2]+g[x][i-j]} (j>1)
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 233
using namespace std; 
struct edge{int to,nxt;}e[N];
int v,n,cnt,lst[N],f[N][N],g[N][N];
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ins(a,b),ins(b,a);}
void dfs(int x,int fa){
	for(int i=0;i<=n;i++)f[x][i]=g[x][i]=1;
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt){
		if(b==fa)continue;
		dfs(b,x);
		for(int j=n;j;j--)
			for(int k=1;k<=min(j,n);k++){
				f[x][j]=max(f[x][j],f[b][k-1]+g[x][j-k]);
				if(k>1){
					f[x][j]=max(f[x][j],g[b][k-2]+f[x][j-k]);
					g[x][j]=max(g[x][j],g[b][k-2]+g[x][j-k]);
				}
			} 
	}
}
int main(){
	freopen("chessboard.in","r",stdin);
	freopen("chessboard.out","w",stdout);
	int i,j,k;
	for(scanf("%d%d",&v,&n),i=1;i<v;i++){
		scanf("%d%d",&j,&k);lnk(j,k);
	}
	dfs(0,-1);
	printf("%d",f[0][n]);
	return 0;
}
