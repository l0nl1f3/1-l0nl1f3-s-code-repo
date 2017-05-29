#include<bits/stdc++.h>
using namespace std;
#define N 2333
#define ll long long
vector<int>x[N],y[N];
int n,a[200][30000],l[N],id[N],mX[N],mY[N];
int cmp(int i,int j){
	return l[i]>l[j];
}
namespace BFS{
	int b[2333][2333],n,m,ans;
	void dfs(int x,int y){
		b[x][y]=1;++ans;
		if(x+1<=n&&y<=m&&!b[x+1][y])dfs(x+1,y);
		if(x<=n&&y+1<=m&&!b[x][y+1])dfs(x,y+1);
		if(x-1>0&&y<=m&&!b[x-1][y])dfs(x-1,y);
		if(x<=n&&y>0&&!b[x][y-1])dfs(x,y-1);
	}
	int main(int p,int x,int y){
		n=x;m=y;ans=0;
		memset(b,0,sizeof(b));
		for(int i=0;i<l[p];i++)b[::x[p][i]][::y[p][i]]=1;
		for(int i=1;i<=x;i++)
			if(!b[y][i]){
				dfs(y,i);break;}
		return ans;
	}	
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	int seed=0;
	for(i=1;i<=n;i++){
		scanf("%d",l+i);
		for(j=1;j<=l[i];j++){
			int a,b;scanf("%d%d",&a,&b);	
			x[i].push_back(a);
			mX[i]=max(mX[i],a);
			y[i].push_back(b);
			mY[i]=max(mY[i],b);
		}
		mX[i]=BFS::main(i,mX[i],mY[i]);
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	int dt=0,ht=0;
	for(int ii=1;ii<=n;ii++){
		int i=id[ii];
		int xd=0,yd=0,mx=1e5,my=1e5;
		for(j=0;j<l[i];j++)mx=min(mx,x[i][j]),my=min(my,y[i][j]+dt);
		for(int dx=0;dx<mx;dx++)
			for(int dy=0;dy<my;dy++){
				int ok=1;
				for(j=0;j<l[i];j++)
					if(x[i][j]<=dx||y[i][j]+dt<=dy){
						ok=0;
						break;
					}
					else if(a[x[i][j]-dx][y[i][j]+dt-dy])ok=0;
			if(ok)xd=dx,yd=dy;
		}
		for(j=0;j<l[i];j++)x[i][j]-=xd,y[i][j]-=yd;
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
