#include<bits/stdc++.h>
#define N 123456
#define M 233 
#define ll long long
using namespace std;
int n,K,s[N],q[N],h,t;
ll f[N],g[N];int trans[M][N];
ll gf(int i,int j){
	return g[j]+(ll)s[i]*s[j];
}
bool dx(int i,int j,int k){
	return (g[i]-g[j])*(s[k]-s[j])>(g[j]-g[k])*(s[j]-s[i]);
}
int main(){
	int i,j;
	scanf("%d%d",&n,&K);
	for(i=1;i<=n;i++){
		scanf("%d",&j);
		s[i]=s[i-1]+j;
	}
	for(j=1;j<=K;j++){
		g[j]=f[j]-(ll)s[j]*s[j];
		for(q[h=t=1]=i=j,i++;i<=n;q[++t]=i++){
			for(g[i]=f[i]-(ll)s[i]*s[i];h<t&&gf(i,q[h+1])>gf(i,q[h]);++h);
			for(f[i]=gf(i,trans[j][i]=q[h]);h<t&&!dx(i,q[t],q[t-1]);t--); 
		}
	}
	for(printf("%lld\n",f[n]),i=n;!K;K--){
		printf("%d ",i=trans[K][i]);
	}
}
