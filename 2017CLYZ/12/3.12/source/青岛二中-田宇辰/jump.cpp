#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int N=1510,M=1500;
struct node{
	int x,y;
	node(){}
	node(int x,int y):x(x),y(y){}
};node q[N*N];int h,t;
int s[N][N];int vis[N][N];int d[N][N];
int dx[8]={-2,-1,1,2,2,1,-1,-2},dy[8]={1,2,2,1,-1,-2,-2,-1};

int main(){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	node tmp;int x,y,xx,yy,p,i,j;int T;int ans;
	vis[5][5]=1;h=t=0;q[++t]=node(5,5);s[5][5]=0;
	while(h<t){
		tmp=q[++h];x=tmp.x;y=tmp.y;
		rep(i,0,7){
			xx=x+dx[i];yy=y+dy[i];
			if(xx<1||xx>M||yy<1||yy>M||vis[xx][yy])	continue;
			vis[xx][yy]=1;s[xx][yy]=s[x][y]+1;
			q[++t]=node(xx,yy);	
		}
	}
	rep(i,1,M){
		rep(j,1,M){
			d[abs(i-5)][abs(j-5)]=s[i][j];
		}
	}
	/*rep(i,0,10){
		rep(j,0,10){
			printf("d[%d][%d]=%d ",i,j,d[i][j]);
		}
		printf("\n");
	}*/
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d%d",&x,&y);
		x=abs(x);y=abs(y);
		if(x<y)	swap(x,y);
		if(x<=1000&&y<=1000){
			printf("%d\n",d[x][y]);continue;
		}
		if(x>=2*y){
			if(x-2*y>100){
				ans+=y;
				x-=2*y;y=0;
				p=(x-50)/4;
				ans+=2*p;x-=4*p;
				ans+=d[x][y];
				printf("%d\n",ans);continue;
			}
			else{
				x-=2*y;ans+=y;y=0;
				ans-=10;x+=10*2;y+=10;
				ans+=d[x][y];
				printf("%d\n",ans);continue;
			}	
		}		
		else{
			p=x-y;
			x-=2*p;y-=p;ans+=p;
			if(x<=100&&y<=100){
				x+=2*10;y+=10;ans-=10;
				ans+=d[x][y];
				printf("%d\n",ans);
				continue;
			}
			else{
				p=(x-50)/3;ans+=p*2;
				x-=p*3;y-=p*3;
				ans+=d[x][y];
				printf("%d\n",ans);
				continue;
			}
		}
	}
	return 0;
}
