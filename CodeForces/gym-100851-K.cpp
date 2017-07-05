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
vector<int>e[N];
int n,m,d[N],b[N],ed[N],id[N],od[N],bc;

int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d",&j,&k),e[j].push_back(k),od[j]++,id[j]++;
	for(i=1;i<=n;i++)
		for(j=0;j<e[i].size;j++){
			k=e[i][j];//6715154 6590070 
		}
	return 0;
}


