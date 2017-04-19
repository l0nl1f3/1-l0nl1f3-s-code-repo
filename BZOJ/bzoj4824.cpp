#include<bits/stdc++.h>
#define N 200
#define p 1000000007
#define ll long long
using namespace std;
int n,f[N][N],c[N][N],sz[N],ps[N][N],ss[N][N];char s[N];
int C(int n,int m){return (n<m||n<0||m<0)?0:c[n][m];}
int main(){
	int i,j,k,l;
	scanf("%d%s",&n,s+2);
	for(i=0;i<N;i++)
		for(c[i][0]=j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
	for(i=n;i;i--)sz[i/2]+=++sz[i];
	for(i=n;i;i--){
		if(sz[i]==1)f[i][1]=1;
		if(sz[i]==2)f[i][1+(s[2*i]=='>')]=1;
		if(sz[i]>2){
			for(j=1;j<=sz[i];j++)
				for(k=0;k<=sz[2*i]&&k<=j-1;k++){
					int g=(ll)C(j-1,k)*C(sz[i]-j,sz[2*i]-k)%p;
					if(s[2*i]=='>')g=(ll)g*ps[2*i][k]%p;
					else g=(ll)g*ss[2*i][k+1]%p;
					if(s[2*i+1]=='>')g=(ll)g*ps[2*i+1][j-k-1]%p;
					else g=(ll)g*ss[2*i+1][j-k]%p;
					f[i][j]=(f[i][j]+g)%p;				
				}
		}
		for(j=1;j<=n+1;j++)ps[i][j]=(ps[i][j-1]+f[i][j])%p;
		for(j=n+1;~j;j--)ss[i][j]=(ss[i][j+1]+f[i][j])%p;
	}
	cout<<ps[1][n];
}
