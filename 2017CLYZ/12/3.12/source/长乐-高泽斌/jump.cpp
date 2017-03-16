#include<algorithm>
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int dx[]={1,2,2,1,-1,-2,-2,-1};
const int dy[]={2,1,-1,-2,-2,-1,1,2};
int f[1100][1100],h[1000050][2];
bool vis[1100][1100];
int n,x,y;
int main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	memset(f,127/3,sizeof(f));
	int t=0,w;
	h[w=1][0]=0;
	h[w][1]=0;
	f[0][0]=0;
	while(t<w)
	{
		++t;
		if(t==1000000) t=0;
		int ux=h[t][0];
		int uy=h[t][1];
		for(int k=0;k<8;++k)
		{
			int vx=ux+dx[k],vy=uy+dy[k];
			if(vx>=0&&vx<=1000&&vy>=0&&vy<=1000&&f[ux][uy]+1<f[vx][vy])
			{
				f[vx][vy]=f[ux][uy]+1;
				if(!vis[vx][vy])
				{
					vis[vx][vy]=1;
					++w;
					if(w==1000000) w=0;
					h[w][0]=vx;
					h[w][1]=vy;
				}
			}
		}
	}
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>x>>y;
		if(x<=1000&&y<=1000) printf("%d\n",f[x][y]);
		else
		{
			if(!y)
			{
				x++;
				x-=2;
				y=(x-1)/4+1;
				y*=2;
				if(x%2==1)
					printf("%d\n",y);
				else printf("%d\n",y+1);
			} 
			else
			{
				y=((x-1)/3+1)*2;
				printf("%d\n",y);
			}
		}
	}
} 
