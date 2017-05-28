#include<bits/stdc++.h>
using namespace std;
#define N 2333
vector<int>x[N],y[N];
int n,a[4000][4000],l[N];
int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",l+i);
		for(j=1;j<=l[i];j++){
			int a,b;scanf("%d%d",&a,&b);	
			x[i].push_back(a);
			y[i].push_back(b);
		}
	}
	int dt=0,ht=0;
	for(i=1;i<=n;i++){
		int da=0;
		for(int dv=1;dv<=5;dv++){
			int ok=1;
			for(j=0;j<l[i];j++){
				if(a[x[i][j]][y[i][j]-dv]){
					ok=0;break;
				}
				if(y[i][j]<=dv){
					ok=0;break;
				}
			}
			if(ok)da=dv;
		} 
		for(j=0;j<l[i];j++)y[i][j]-=da;
		for(j=k=0;j<l[i];j++){
			a[x[i][j]][y[i][j]+dt]=i;
			k=max(k,y[i][j]);ht=max(ht,x[i][j]);
		}
		dt+=k;
	}
	printf("%d %d\n",ht,dt);
	for(i=1;i<=ht;i++,puts(""))
		for(j=1;j<=dt;j++)printf("%d ",a[i][j]);
	return 0;
}
