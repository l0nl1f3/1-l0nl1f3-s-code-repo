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
#define ll long long
#define p 1000000007
#define N 20
int n,K,a[N],b[1<<N],gt[N][N],gd[1<<N],f[1<<N][N];
int main(){
	int i,j,k,x;
	scanf("%d%d",&n,&K);
	for(i=0;i<n;i++)
		scanf("%d",a+i),b[1<<i]=a[i];
	int up=(1<<n)-1;
	for(i=0;i<=up;i++){
		j=i-(i&-i);
		if(!j)gd[i]=b[i];
		else gd[i]=__gcd(gd[j],b[i&-i]);		
	}
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
			x=0;
			for(k=i;k<=j;k++)
				x^=1<<k;
			gt[i][j]=x;
		}
	}
	int cnt=0;
	f[0][0]=1;
	for(i=0;i<=up;i++){
		for(j=0;j<n;j++)
			for(k=j;k<n;k++){
				if((i&(1<<j))||(i&(1<<k)))continue;
				if(gd[(~i)&gt[j][k]]>=K){
					int to=i|gt[j][k];
					for(x=1;x<=n;x++){
						f[to][x]+=f[i][x-1];
						f[to][x]>=p?f[to][x]-=p:0;
					}
				}
			}
	}
	int ans=0;
	for(i=1;i<=n;i++){
		ans=(ans+(ll)f[up][i]*i)%p;
	}
	cout<<ans;
	return 0;
}


