#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 101234
int T,n,a[N];
int main(){
	int i;
	scanf("%d",&T);
	for(int _=1;_<=T;_++){
		scanf("%d",&n);
		for(i=1;i<=n;i++)scanf("%d",a+i);
		sort(a+1,a+n+1);
		int ans=0;
		for(i=n;i>2;i-=3)
			ans+=a[i]+a[i-1];
		while(i)ans+=a[i--]; 
		cout<<"Case #"<<_<<": "<<ans<<endl;
	}
	return 0;
}


