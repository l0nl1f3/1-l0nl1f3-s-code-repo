#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 1001234
int n,q,dl[N],dr[N];ll rs,ls,rc,lc;
int main(){
	int i;
	FO(adjustment);scanf("%d%d",&n,&q);
	while(q--){
		char op[6];scanf("%s%d",op,&i);
		if(op[0]=='R'){
			if(dr[i])puts("0");
			else{
				printf("%I64d\n",(ll)i*(n-lc)+(ll)n*(n+1)/2-ls);
				rc++;rs+=i;dr[i]=1;
			}
		}else{
			if(dl[i])puts("0");
			else{
				printf("%I64d\n",(ll)i*(n-rc)+(ll)n*(n+1)/2-rs);
				lc++;ls+=i;dl[i]=1;
			}
		}
	} 
	return 0;
}


