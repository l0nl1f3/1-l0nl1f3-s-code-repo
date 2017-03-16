#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;
const int N=1000;
int rec1[]={0,3,2,5,2,3,4,5,4,5,6,7,6,7,8,9,8,9,10,11,10,11,12,13,12,13,14,15,14,15,16,17,16,17,18,19,18,19,20,21,20};
int rec2[]={0,4,4,2,4,4,4,6,6,6};
int c[8]={-2,-2,-1,-1,1,1,2,2},d[8]={1,-1,2,-2,2,-2,1,-1};
int vis[1005][1005],st[1005][1005],que[10000005][2];
int X,Y,T;
int bfs()
{
	memset(vis,0,sizeof(vis));
	vis[0][0]=1;
	que[1][0]=0, que[1][1]=0;
	for (int q1=1,q2=1; q1<=q2; ++q1){
		int x=que[q1][0],y=que[q1][1];
	//	printf("\n%d %d\n",x,y);
		for (int i=0; i<8; ++i){
			int dx=x+c[i], dy=y+d[i];
			if ((X-dx)*c[i]<0 && (Y-dy)*d[i]<0) continue;
		//	printf("%d %d\n",dx,dy);
			if (dx<0 || dy<0) continue;
			if (!vis[dx][dy]){
				vis[dx][dy]=1;
				st[dx][dy]=st[x][y]+1;
				que[++q2][0]=dx, que[q2][1]=dy;
				if (dx==X && dy==Y) return st[dx][dy];
			}
		}
	}
	return 0;
}
int main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
//	freopen("test.out","w",stdout);
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&X,&Y);
		X=abs(X); Y=abs(Y);
		if (Y==0) {
			if (X<=20) printf("%d\n",rec1[X]);
			else printf("%d\n",rec1[20+X%20]+((X/20)-1)*10);
			continue;
		}
		if (X==Y){
			if (X<=3) printf("%d\n",rec2[X]);
			else printf("%d\n",((X-1)/3+1)*2);
			continue;
		}
		
	//	X+=N, Y+=N;		
	//	if ((2*Y-X)%3==0 && (2*X-Y)%3==0) printf("%d\n",abs(2*Y-X)/3+abs(2*X-Y)/3);
	//	else{
			//printf("R");
			/*int a=(2*X-Y)/3,b=(2*Y-X)/3,ans=0;
			if (a>=0 && b>=0){
				X=X-2*a-b, Y=Y-a-2*b;
				ans=a+b;
			}			
		//	printf("%d %d %d %d\n",a,b,X,Y);*/
			printf("%d\n",bfs());
	//	}
	}
}
