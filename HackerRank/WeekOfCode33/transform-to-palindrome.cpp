#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmin(T &a,const T &b){
	return a>b?a=b,1:0;
}
template<typename T>
inline bool cmax(T &a,const T &b){
	return a<b?a=b,1:0;
}
#define N 1234
int n,K,m,a[N],f[N][N],fa[101234];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	int i,j,k,ans=0;
	scanf("%d%d%d",&n,&K,&m);
	for(i=1;i<=n;i++)fa[i]=i;
	for(i=1;i<=K;i++){
		scanf("%d%d",&j,&k);	
		fa[find(j)]=find(k);
	}
	for(i=1;i<=m;i++)scanf("%d",a+i);
	for(i=1;i<=m;i++)a[i]=find(a[i]);
	for(i=1;i<=m;i++)f[i][i]=1;
	for(j=1;j<=m;j++)
		for(i=j-1;i;i--){
			if(a[i]==a[j])
				cmax(f[i][j],f[i+1][j-1]+2);
			else 
				f[i][j]=max(f[i][j-1],f[i+1][j]);
			cmax(ans,f[i][j]);
		}
	cout<<ans;
	return 0;
}
