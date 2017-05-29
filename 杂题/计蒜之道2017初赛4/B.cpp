#include<bits/stdc++.h>
#define N 101234
using namespace std;
int x[N],y[N],x2[N],y2[N],dx[N],dy[N];
map<pair<int,int>,int> mp;
int main(){
	int n,i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d%d%d%d",x+i,y+i,x2+i,y2+i);
		dx[i]=x2[i]-x[i];
		dy[i]=y2[i]-y[i];
		mp[make_pair(dx[i],dy[i])]++;
		if(mp[make_pair(dx[i],dy[i])]>=n/2){
			printf("%d %d",dx[i],dy[i]);return 0;
		}
	}
	
}
