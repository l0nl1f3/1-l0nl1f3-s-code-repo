#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int dx[8]={1,2,2,1,-1,-2,-2,-1};
const int dy[8]={2,1,-1,-2,-2,-1,1,2};
struct dui
{
	int x,y;
}q[1000100];
int dep[1500][1500],d[1500][1500],n,m,vis[1500][1500];
void ycl()
{
	int i,j,fp=1,rp=0,nx,ny;
	dep[60][60]=0;
	q[++rp]=(dui){60,60};
	vis[60][60]=1;
	while(fp<=rp)
	{
		dui x=q[fp++];
		for(i=0;i<8;i++)
		{
			nx=x.x+dx[i];ny=x.y+dy[i];
			if((nx<10)||(ny<10)||(nx>110)||(ny>110)||(vis[nx][ny]))continue;
			dep[nx][ny]=dep[x.x][x.y]+1;
			vis[nx][ny]=1;
			q[++rp]=(dui){nx,ny};
		}
	}
	for(i=0;i<=50;i++)
	   for(j=0;j<=50;j++)d[i][j]=dep[i+60][j+60];
}
int cal(int n,int m,int x,int y)
{
	int nn=n-x,mm=m-y,ans=0,ti;
	if(nn>0)
	{
		if(mm<=0)
		{
		    ans+=(nn/4)*2;
		    n-=(nn/4)*4;nn-=(nn/4)*4;
		}
		else if(nn>mm*2)
		{
			ans+=mm;
			m-=mm;n-=mm*2;
			nn-=mm*2;
			mm=0;
			ti=nn/4;
			ans+=ti*2;
			n-=ti*4;nn-=ti*4;
		}
		else
		{
			ti=nn-mm;
			ans+=ti;
			nn-=2*ti;mm-=ti;
			n-=2*ti;m-=ti;
			ti=nn/3;
			ans+=2*ti;
			n-=ti*3;m-=ti*3;
			nn-=ti*3;mm-=ti*3;
		}
		if((nn==0)&&(mm==0))return ans;
		else return 2000000000;
	}
	else return 0;
}
int main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	int i,j,k,t,ti,ans,nn,mm;
	ycl();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		ans=2010000000;
		if(n<0)n=-n;
		if(m<0)m=-m;
		if(n<m)swap(n,m);
		for(i=0;i<=40;i++)
		   for(j=0;j<=40;j++)
		      ans=min(ans,d[i][j]+cal(n,m,i,j));
		printf("%d\n",ans);
	}
	return 0;
}
