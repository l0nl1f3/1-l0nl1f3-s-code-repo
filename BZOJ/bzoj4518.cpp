#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 3001
int n,m,h,t,d[N],q[N];ll f[N][N],s[N];
double slope(int i,int x,int y){
	return 1.0*(f[i][x]+s[x]*s[x]-f[i][y]-s[y]*s[y])/(s[x]-s[y]);
} 
int main(){
	n=gi;m=gi;
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(d[i]=gi);
	memset(f,0x3f,sizeof(f));f[0][0]=0;
	for(int i=1;i<=m;i++,h=t=0){
		for(int j=1;j<=n;j++){
			for(;h<t&&slope(i-1,q[h],q[h+1])<2*s[j];h++);
			f[i][j]=f[i-1][q[h]]+(s[j]-s[q[h]])*(s[j]-s[q[h]]);
			for(;h<t&&slope(i-1,q[t],q[t-1])>slope(i-1,q[t],j);t--);
			q[++t]=j;
		} 
	}
	printf("%d\n",m*f[m][n]-s[n]*s[n]);
	return 0;
}

