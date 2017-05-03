#include<bits/stdc++.h>
#define N 101234 
#define fi first
#define se second
using namespace std;
int n,K,m,cnt,f[N],g[N],l[N],r[N],c[N],L[N],R[N],ord[N],seg[N*4],s[N][2],qt;
void mdf(int p,int l,int r,int a,int b){
	if(r<a||l>b)return;
	if(a<=l&&r<=b){seg[p]=1;return;}
	mdf(p+p,l,(l+r)/2,a,b);
	mdf(p+p+1,(l+r)/2+1,r,a,b);
}
int qry(int p,int l,int r,int d){
	if(seg[p])return 1;
	if(l==r)return 0;
	if(d<=(l+r)/2)return qry(p+p,l,(l+r)/2,d);
	else return qry(p+p+1,(l+r)/2+1,r,d);
}
vector<pair<int,int> >v;
int main(){
	int i,j,k;
	for(scanf("%d%d%d",&n,&K,&m),i=1;i<=m;i++)
		scanf("%d%d%d",l+i,r+i,c+i);
	for(i=1;i<=m;i++)
		if(!c[i])mdf(1,1,n,l[i],r[i]);
	for(i=1;i<=n;i++)
		if(!qry(1,1,n,i))
			ord[L[i]=R[i]=++cnt]=i;
	if(cnt==K){
		for(i=1;i<=cnt;i++)printf("%d\n",ord[i]);
		return 0;
	}
	for(i=1;i<=n;i++)if(!R[i])R[i]=R[i-1];
	for(L[n+1]=1e9,i=n;i;i--)if(!L[i])L[i]=L[i+1];
	for(i=1;i<=m;i++)
		if(c[i]){
			j=L[l[i]],k=R[r[i]];
			if(j>k)swap(j,k);
			v.push_back(make_pair(j,k));
		}
	for(sort(v.begin(),v.end()),i=0;i<v.size();i++){
		while(qt&&v[i].fi>=s[qt][0]&&v[i].se<=s[qt][1])qt--;
		s[++qt][0]=v[i].fi;
		s[qt][1]=v[i].se;
	}
	for(i=1,j=0;i<=qt;i++){
		f[i]=f[i-1];
		if(s[i][0]>j)
			j=s[i][1],
			f[i]++;
	}
	for(i=qt,j=1e9;i;i--){
		g[i]=g[i+1];
		if(s[i][1]<j)
			j=s[i][0],
			g[i]++;
	}
	int h=0;
	for(i=1;i<=qt;i++){
		if(f[i]!=f[i-1]+1)continue;
		if(s[i][0]==s[i][1])printf("%d\n",h=ord[s[i][0]]);
		else{
			int x=s[i][1]-1,a=0,b=qt+1,o;
			for(int l=1,r=i-1;l<=r;s[o=(l+r)/2][1]<x?a=o,l=o+1:r=o-1);
			for(int l=i+1,r=qt;l<=r;s[o=(l+r)/2][0]>x?b=o,r=o-1:l=o+1);
			if(f[a]+g[b]+1>K)
				printf("%d\n",h=ord[s[i][1]]);
		}
	}
	if(!h)puts("-1");
	return 0;
} 
