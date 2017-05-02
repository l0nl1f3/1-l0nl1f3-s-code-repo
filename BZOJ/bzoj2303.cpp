#include<bits/stdc++.h>
#define N 101234
#define p 1000000000
using namespace std; 
int n,m,K,f[N],cl[N],nxt[N],fst[N],tag[N];vector<int>r[N],c[N];
int find(int x){
	return x==f[x]?x:f[x]=find(f[x]);
}
int query(int x){
	if(x==nxt[x])return x;
	int t=query(nxt[x]);
	cl[x]^=cl[nxt[x]];
	return nxt[x]=t;
}
bool modify(int x,int y,int f){
	int fx=query(x),fy=query(y);
	if(fx==fy)return (cl[x]^cl[y])==f;
	else {
		nxt[fx]=fy;
		cl[fx]=cl[x]^cl[y]^f;
		return 1;
	}
}
int main(){
	int i,j,k,l;
	scanf("%d%d%d",&n,&m,&K);
	for(i=1;i<=m;i++)f[i]=nxt[i]=i;
	for(i=1;i<=K;i++){
		scanf("%d%d%d",&j,&k,&l);
		if(j==1)fst[k]=1;tag[j]=1;
		r[j].push_back(k);
		c[j].push_back(l);
	} 	
	for(i=1;i<=n;i++){
		for(j=1;j<r[i].size();j++){
			int x=r[i][j],y=r[i][j-1],cx=c[i][j],cy=c[i][j-1];
			int fx=find(x),fy=find(y);
			f[fx]=fy;
			if(fst[fx])fst[fy]=1;
			int t=cx^cy;
			if((x&1)^(y&1))t=(t^(i-1))&1;
			if(!modify(x,y,t)){puts("0");return 0;}
		}
	}
	for(i=1,j=1;i<=m;i++)
		if(f[i]==i&&!fst[i])j=j*2%p;
	for(i=2;i<=n;i++)
		if(!tag[i])j=j*2%p;
	cout<<j;
	return 0;
}
