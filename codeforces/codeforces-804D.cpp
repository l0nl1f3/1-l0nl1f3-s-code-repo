#include<bits/stdc++.h>
using namespace std;
#define N 201234
map<pair<int,int>,double>mp;
vector<double>vec[N]; 
struct edge{int to,nxt;}e[N];
int n,m,q,lst[N],cnt,fir[N],sec[N],dia[N],f[N];
int find(int x){return !f[x]?x:f[x]=find(f[x]);}
void ins(int a,int b){
	e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;
}
void lnk(int a,int b){ins(a,b);ins(b,a);}
void mdf(int x,int y){
	if(y>fir[x])sec[x]=fir[x],fir[x]=y; 
	else if(y>sec[x])sec[x]=y;
}
void dfs0(int x,int fa){
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt)
		if(b!=fa){
			dfs0(b,x);
			mdf(x,fir[b]+1);
		}
	dia[find(x)]=max(dia[find(x)],fir[x]+sec[x]);
} 
void dfs1(int x,int fa){
	vec[find(x)].push_back(fir[x]);	
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt){
		if(b==fa)continue;
		mdf(b,fir[b]+1==fir[x]?sec[x]+1:fir[x]+1);
		dfs1(b,x);
	}
}
int main(){
	int i,j,k,x,y;
	for(scanf("%d%d%d",&n,&m,&q);m--;){
		scanf("%d%d",&i,&j);
		lnk(i,j);f[find(i)]=find(j);
	}
	for(i=1;i<=n;i++)
		if(find(i)==i){
			dfs0(i,i);
			dfs1(i,i);
			vec[i].push_back(0);
			sort(vec[i].begin(),vec[i].end());
			for(int j=1;j<vec[i].size();j++)vec[i][j]+=vec[i][j-1];
		}
	for(;q--;){
		scanf("%d%d",&x,&y);
		x=find(x);y=find(y);
		if(x==y){puts("-1");continue;}
		if(x>y)swap(x,y);
		if(mp[make_pair(x,y)]){
			printf("%.10lf\n",mp[make_pair(x,y)]);
			continue; 
		}
		if(vec[x].size()>vec[y].size())
			swap(x,y);
		double ans=0;
		for(i=1;i<vec[x].size();i++){
			for(int l=(k=0)+1,r=vec[y].size()-1,o;l<=r;o=(l+r)/2,
			vec[x][i]-vec[x][i-1]+vec[y][o]-vec[y][o-1]+1<=max(dia[x],dia[y])?k=o,l=o+1:r=o-1);
			ans=ans+(double)k*max(dia[x],dia[y])+(vec[y].size()-k-1)*(vec[x][i]-vec[x][i-1]+1)+vec[y][vec[y].size()-1]-vec[y][k];
		}
		if(x>y)swap(x,y);
		printf("%.10lf\n",mp[make_pair(x,y)]=ans/(vec[x].size()-1)/(vec[y].size()-1));
	}
}

