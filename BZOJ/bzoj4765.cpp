#include<bits/stdc++.h>
using namespace std; 
#define ll unsigned long long
#define N 101234
int n,q,rot,d,bn,bel[N],l[N],r[N],v[N],f[N][320];
ll bit[N],bs[320],siz[N];
struct edge{int to,nxt;}e[N*2];int cnt,lst[N];
ll sum(int r){
	ll res=0;
	for(;r;r-=r&-r)
		res+=bit[r];
	return res;
}
ll add(int r,int d){
	for(;r<=n;r+=r&-r)bit[r]+=d;
}
void dfs(int x,int fa){
	l[x]=++d;siz[bel[x]]++;
	add(l[x],v[x]);
	for(int i=1;i<=bn;i++)f[x][i]=siz[i];
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt){
		if(b!=fa)dfs(b,x);
	}
	r[x]=d;siz[bel[x]]--;
}
int main(){
	int i,j,k,p;
	scanf("%d%d",&n,&q);
	j=sqrt(n);
	for(i=1;i<=n;i++)scanf("%d",v+i),bel[i]=(i-1)/j+1;
	for(bn=(n-1)/j+1,p=1;p<=n;p++){
		scanf("%d%d",&i,&k);
		if(!i)rot=k;
		else{
			e[++cnt]=(edge){k,lst[i]};lst[i]=cnt;
			e[++cnt]=(edge){i,lst[k]};lst[k]=cnt;
		}
	}
	dfs(rot,0);
	for(i=1;i<=n;i++)bs[bel[i]]+=sum(r[i])-sum(l[i]-1);
	for(i=1;i<=q;i++){
		scanf("%d%d%d",&j,&k,&p);
		if(j==1){
			add(l[k],p-v[k]);
			for(int o=1;o<=bn;o++)bs[o]+=(ll)f[k][o]*(p-v[k]);
			v[k]=p; 
		}else{
			ll ans=0;
			if(bel[k]!=bel[p]){
				for(int o=bel[k]+1;o<bel[p];o++)ans+=bs[o];
				for(int o=k;bel[o]==bel[k]&&o<=n;o++)ans+=sum(r[o])-sum(l[o]-1);
				for(int o=p;bel[o]==bel[p]&&o;o--)ans+=sum(r[o])-sum(l[o]-1);
			}else for(int o=k;o<=p;o++)ans+=sum(r[o])-sum(l[o]-1);
			printf("%llu\n",ans);
		}
	} 
}
