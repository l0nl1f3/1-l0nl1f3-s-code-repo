#include<bits/stdc++.h>
using namespace std;
vector<int>g[2333];
int v[2333],j,n;char ch[2333];
void bfs(int i){
	queue<int>q;
	memset(v,0,sizeof(v));
	q.push(i);v[i]=1;
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=0;i<g[c].size();i++)
			if(!v[g[c][i]])v[g[c][i]]=1,q.push(g[c][i]);
	}
	for(i=1;i<=n;i++)j+=v[i]; 
} 
int main(){
	int i;
	for(scanf("%d",&n),i=1;i<=n;i++){
		scanf("%s",ch+1);
		for(j=1;j<=n;j++)if(ch[j]=='1')g[i].push_back(j);
	}
	for(i=1,j=0;i<=n;i++)bfs(i);
	return printf("%d",j),0;
} 
