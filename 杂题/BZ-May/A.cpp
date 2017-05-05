#include<bits/stdc++.h>
#define N 1001
#define M 200001
using namespace std;
int n,m,K,ed,col[N],lst[N],cs[N],cnt;
struct edge{int to,nxt;}e[M];
void getpath(int y){
	printf("%d ",y);
	if(col[y]==1)return;
	for(int i=lst[y];i;i=e[i].nxt){
		int b=e[i].to;
		if(col[b]==col[y]-1){
			getpath(b);
			break;
		}
	}
}
void dfs(int x){
	for(int i=lst[x];i;i=e[i].nxt)
		cs[col[e[i].to]]=1;
	for(int i=1;;i++)if(!cs[i]){
		col[x]=i;
		break;
	}
	for(int i=lst[x];i;i=e[i].nxt)
		cs[col[e[i].to]]=0;
	if(!ed&&col[x]==K+1){
		printf("path ");
		getpath(x);
		ed=1;
		puts("");
	}
}
int main(){
	int T,i,j,k,x,y,z;
	scanf("%d",&T);
	while(T--){
		for(i=1;i<=n;i++)lst[i]=0;
		cnt=ed=0;
		scanf("%d%d%d",&n,&m,&K);
		for(i=1;i<=m;i++){
			scanf("%d%d",&j,&k);
			e[++cnt]=(edge){k,lst[j]};lst[j]=cnt;
			e[++cnt]=(edge){j,lst[k]};lst[k]=cnt;
		}
		memset(col,0,sizeof(col));
		for(i=1;i<=n;i++)dfs(i);
		if(!ed){
			printf("color ");
			for(i=1;i<=n;i++)printf("%d ",col[i]);puts("");
		}
	}
}
