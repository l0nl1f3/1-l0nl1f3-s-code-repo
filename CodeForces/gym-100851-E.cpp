#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 123
int n,m,ans,cnt,a[N][N],p[N];
int main(){
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",p+i);
		for(j=1;j<=p[i];j++)scanf("%d",a[i]+j);
	}
	for(j=1;j<=10;j++){
		for(i=1;i<=n;i++){
			if(j>p[i]){ 
				ans+=50;
				if(++cnt==m)return printf("%d\n",ans),0;
			}else
				if(a[i][j]>=ans){
					ans+=a[i][j];
					if(++cnt==m)return printf("%d\n",ans),0;
				}
		}
	}
	if(cnt<m)
		ans+=50*(m-cnt);
	cout<<ans;
	return 0;
}


