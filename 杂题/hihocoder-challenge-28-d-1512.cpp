#include <bits/stdc++.h>
#define N 52
#define nK 2502
#define ll long long
#define p 1000000007
using namespace std;
int f[nK],w[N][N],g[N][N],a[nK],b[nK],fac[nK],inv[nK],n,K; 
int exp(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int main(){
	int i,j,k,l,o;
	scanf("%d%d",&n,&K);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&w[i][j]);
	for(i=fac[0]=1;i<=n*K;i++)fac[i]=(ll)fac[i-1]*i%p;
	for(i=n*K,inv[i]=exp(fac[i],p-2);i;i--)inv[i-1]=(ll)inv[i]*i%p;
	for(int x=0;x<=n*K;x++){
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++){
				int s=0,h=(ll)w[i][j]*x%p,c=1;
				for(k=0;k<=K;k++){
					s=(s+(ll)c*inv[k]%p)%p;
					c=(ll)c*h%p;
				}
				g[i][j]=p-s;
			}
		for(i=1;i<=n;i++){
			for(g[i][i]=0,j=1;j<=n;j++)
				if(i!=j)g[i][i]=(g[i][i]-g[i][j]+p)%p;
		}
		for(l=j=1;j<n;j++){
            for(k=j;k<n;k++)
                if(g[j][k])break;
            if(k==n){l=0;break;}
            if(k>j)for(l*=-1,o=j;o<n;o++)swap(g[j][o],g[k][o]);
            l=(ll)l*g[j][j]%p;o=exp(g[j][j],p-2);
            for(k=j;k<n;k++)g[j][k]=(ll)g[j][k]*o%p;    
            for(k=j+1;k<n;k++)if(g[k][j])
                for(o=n-1;o>=j;o--)g[k][o]=(g[k][o]-(ll)g[k][j]*g[j][o])%p;
        }
        f[x]=l;
	}
	n=n*K;
	for(i=1;i<n;i++)for(j=n-1;j>=i;j--)f[j]=(f[j]-f[j-1]+p)%p;
    for(b[0]=f[0],i=k=a[0]=1;i<n;i++){
        for(j=i;j;j--)a[j]=(a[j-1]-(ll)a[j]*(i-1)%p+p)%p;
        for(f[i]=(ll)f[i]*inv[i]%p,a[0]=j++;j<=i;j++){
            b[j]=(b[j]+(ll)a[j]*f[i]%p)%p;
        } 
    }
    printf("%d",(ll)b[K]*fac[K]%p);
}
