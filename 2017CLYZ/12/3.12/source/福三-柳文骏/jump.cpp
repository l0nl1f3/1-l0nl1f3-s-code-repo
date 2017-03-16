#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<ctime>
#define open(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
using namespace std;
template<class T>
inline void read(T& x)
{
    bool f=false;char ch=getchar();x=0;
    while (ch<48)f=(ch=='-'),ch=getchar();
    while (ch>=48)x=(x<<3)+(x<<1)+ch-48,ch=getchar();
    if(f)x*=-1;
}
struct node{int x,y;};
int t,way[101][101],ans;
int dx[9]={0,-2,-1,1,2,2,1,-1,-2},dy[9]={0,-1,-2,-2,-1,1,2,2,1};
int main()
{
	for(int i=0;i<=100;i++)
		for(int j=0;j<=100;j++)
			way[i][j]=1<<30;
	queue <node> que;
	node k={0,0};
	way[0][0]=0;
	que.push(k);
	while(!que.empty())
	{
		k = que.front();que.pop();
		for(int i=1;i<=8;i++)
		{
			int x=k.x+dx[i],y=k.y+dy[i];
			if(x>=0 && x<=100 && y>=0 && y<=100 && way[x][y]>way[k.x][k.y]+1)
			{
				way[x][y]=way[k.x][k.y]+1;
				node c={x,y};
				que.push(c);
			}
		}
	}	
	
/*	for(int i=0;i<=20;i++,cout<<endl)
		for(int j=0;j<=20;j++)
			cout<<way[i][j]<<"   ";*/
			
	open(jump);		
	read(t);
	while(t--)
	{
		ans=0;
		int x,y;
		read(x),read(y);
		x=abs(x),y=abs(y);
		if(x<y)swap(x,y);
		
		int c=x-y;
		
		if(x>100 && y>100)
		{
			int xx=x-100,yy=y-100;
			int bs=min(min(c,xx/2+xx%2),yy);
			ans+=bs;
			x-=2*bs,y-=bs;
		}
		
		if(x>100 && y>100)
		{
			int xx=x-100,yy=y-100;
			int bs=min(xx/3+(xx%3>0),yy/3+(yy%3>0));
			ans+=2*bs;
			x-=3*bs,y-=3*bs;
		}
		
		if(x>100)
		{
			int xx=x-100;
			int bs=min(xx/2+xx%2,y);
			ans+=bs;
			x-=2*bs,y-=bs;
		}
		if(x>100)
		{
			int xx=x-100;
			int bs=xx/4+(xx%4>0);
			x-=bs*4;
			ans+=bs*2;
		}
		printf("%d\n",ans+way[x][y]);
	}
}
