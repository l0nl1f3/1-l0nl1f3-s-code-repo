#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 11
#define S (1<<N)
int n,m,c[N],d[N],e[101],a[N][N],b[N][N],f[N][S],g[N][S]; 	
int main(){
	int T,i,j,k,o,p;
	scanf("%d",&T);
	for(int _=1;_<=T;_++){
		scanf("%d%d",&n,&m);
		int ans=0,up=(1<<m);
		for(i=1;i<=n;i++) for(scanf("%d",c+i),j=1;j<=c[i];j++)scanf("%d",a[i]+j);
		for(i=0;i<m;i++) for(scanf("%d",d+i),j=1;j<=d[i];j++)scanf("%d",b[i]+j);
		for(i=1;i<=n;i++) for(j=1;j<up;j++){
			memset(e,0,sizeof(e));
			for(k=0;k<m;k++) if(j>>k&1)
				for(o=1;o<=d[k];o++)e[b[k][o]]=1;
			for(o=p=1;o<=c[i];o++)if(!e[a[i][o]])p=0;g[i][j]=p;
		}
		for(i=1;i<=n;i++)
			for(j=0;j<up;j++){
				for(f[i][k=j]=f[i-1][j];k;k=(k-1)&j)
					if(g[i][k])
						cmax(f[i][j],f[i-1][j^k]+1);
				cmax(ans,f[i][j]);
			}
		printf("Case #%d: %d\n",_,ans);
	}
	return 0;
}


