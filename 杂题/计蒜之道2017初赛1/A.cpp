#include<bits/stdc++.h>
using namespace std;
#define N 233
int n,m,mp[N][N];
map<int,int>a,b;int c;
int Put(int x,int y){
	if(-3<=x&&x<=3&&-3<=y&&y<=3)mp[x+3][y+3]=1;
	if(y)a[y]++;
	if(x)b[x]++;
}
int main(){
	int i,j,x,y,p=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		Put(x,y);
	}
	for(i=-3;i<=3;i++)
		if(i&&a[i]>=3)++p;
	for(i=-3;i<=3;i++)
		if(i&&b[i]>=3)++p;
	if(mp[3][1+3]&&mp[3][2+3]&&mp[3][3+3]){
		p++;
	}
	if(mp[1+3][3]&&mp[2+3][3]&&mp[3+3][3])p++;
	if(mp[3][-1+3]&&mp[3][-2+3]&&mp[3][-3+3])p++;
	if(mp[-1+3][3]&&mp[-2+3][3]&&mp[-3+3][3])p++;
	cout<<p;
	return 0;
}
