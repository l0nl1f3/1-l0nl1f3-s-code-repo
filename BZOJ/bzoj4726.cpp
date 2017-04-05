#include<bits/stdc++.h>
#define N 2000001
using namespace std;
vector<int>g[N];
int n,k,x,i,cnt,s[N];double f[N],ans;
void dfs(int x){
	s[x]=1;
	for(int i=0;i<g[x].size();i++){
		dfs(g[x][i]);s[x]+=s[g[x][i]];
	}
	f[x]=(s[x]==1);
	for(int i=0;i<g[x].size();i++)
		f[x]=max(f[x],min(f[g[x][i]],s[g[x][i]]*1.0/(s[x]-1)));
}
int main(){
	int i,j;
	for(scanf("%d%d",&n,&k),i=2;i<=n;i++)scanf("%d",&j),g[j].push_back(i);
	for(dfs(1),i=1;i<=n;i++)ans=max(ans,(s[i]>k)*f[i]);
	return printf("%.8lf",ans),0;
} 
