#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmin(T &a,const T &b){
	return a>b?a=b,1:0;
}
template<typename T>
inline bool cmax(T &a,const T &b){
	return a<b?a=b,1:0;
}
int n,m,q,mp[300][300];
int main(){
	int i,j,k,x,y,x1,y1;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d%d%d%d",&x,&y,&x1,&y1);
		if(x>x1)swap(x,x1),swap(y,y1);
		int dx=x1-x;
		int dy=abs(y1-y);
		if(y1>y)j=1;else j=-1;
		int d=__gcd(dx,dy);
		while(x!=x1&&y!=y1){
			mp[x][y]=i;
			x+=dx/d;
			y+=j*dy/d;
		}
		mp[x1][y1]=i;
	}
	scanf("%d",&q);
	for(i=1;i<=q;i++){
		scanf("%d%d",&x,&y);	
		printf("%d\n",mp[x][y]);
	}
	return 0;
}


