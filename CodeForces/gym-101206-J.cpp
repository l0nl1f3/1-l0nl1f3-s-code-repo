#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
int G,asg[30];
string rk[6][30],ec[30],sc;
set<string>m;
int main(){
	int T,i,j,ans;
	scanf("%d",&T);
	for(int _=1;_<=T;_++){
		scanf("%d",&G);ans=-1;
		cin>>sc;
		for(i=0;i<=4;i++)
			for(j=0;j<20;j++)
				cin>>rk[i][j];
		for(i=0;i<20;i++)
			cin>>ec[i];
		for(int y=0;y<=G&&!~ans;y++){
			int x=G-y;
			for(m.clear(),memset(asg,0,sizeof(asg)),i=0;m.size()!=x;asg[i]++,i=(i+1)%5) m.insert(rk[i][asg[i]]);
			for(i=0;i<20;i++)
				if(m.size()==G)break;
				else m.insert(ec[i]);	
			if(m.find(sc)==m.end()) ans=y;
		}
		printf("Case #%d: ",_);
		if(~ans)printf("%d\n",ans);
		else puts("ADVANCED!");
	} 
	return 0;
}


