#include<bits/stdc++.h>
#define N 101234 
#define fi first
#define se second
using namespace std;
int n,k,m,cnt,l[N],r[N],c[N],L[N],R[N],ord[N],seg[N*4],s[N][2],qt;
void mdf(int p,int l,int r,int a,int b){
	if(r<a||l>b)return;
	if(a<=l&&r<=b){seg[p]=1;return;}
	mdf(p+p,l,(l+r)/2,a,b);
	mdf(p+p+1,(l+r)/2+1,r,a,b);
}
int qry(int p,int l,int r,int d){
	if(seg[p])return 1;
	if(l==r)return 0;
	if(d<=(l+r)/2)qry(p+p,l,(l+r)/2,d);
	else qry(p+p+1,(l+r)/2+1,r,d);
}
vector<pair<int,int> >v;
int main(){
	int i,j,k;
	for(scanf("%d%d%d",&n,&k,&m),i=1;i<=m;i++)
		scanf("%d%d%d",l+i,r+i,c+i);
	for(i=1;i<=m;i++)
		if(!c[i])mdf(1,1,n,l[i],r[i]);
	for(i=1;i<=n;i++)
		if(!qry(1,1,n,i))
			ord[L[i]=R[i]=++cnt]=i;
	if(cnt==k){
		for(i=1;i<=cnt;i++)printf("%d\n",i);
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
		while(qt&&v[i].fi>=s[qt][0]&&v[i].se>=s[qt][1])qt--;
		s[++qt][0]=v[i].fi;
		s[qt][1]=v[i].se;
	}
	
	return 0;
} 
