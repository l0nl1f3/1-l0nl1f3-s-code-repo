#include<iostream>
#include<cstdio>
using namespace std;
int t,x,y,tim[110][110];
#define abs(x) x>0?x:-x
inline void dfs(int x,int y){
	if(x+1<=100 && y+2<=100 && tim[x+1][y+2]>tim[x][y]+1){
		tim[x+1][y+2]=tim[x][y]+1;w
		dfs(x+1,y+2);
	}
	if(x+1<=100 && y-2>=0 && tim[x+1][y-2]>tim[x][y]+1){
		tim[x+1][y-2]=tim[x][y]+1;
		dfs(x+1,y-2);
	}
	if(x-1>=0 && y+2<=100 && tim[x-1][y+2]>tim[x][y]+1){
		tim[x-1][y+2]=tim[x][y]+1;
		dfs(x-1,y+2);
	}
	if(x-1>=0 && y-2>=0 && tim[x-1][y-2]>tim[x][y]+1){
		tim[x-1][y-2]=tim[x][y]+1;
		dfs(x-1,y-2);
	}
	if(x+2<=100 && y+1<=100 && tim[x+2][y+1]>tim[x][y]+1){
		tim[x+2][y+1]=tim[x][y]+1;
		dfs(x+2,y+1);
	}
	if(x+2<=100 && y-1>=0 && tim[x+2][y-1]>tim[x][y]+1){
		tim[x+2][y-1]=tim[x][y]+1;
		dfs(x+2,y-1);
	}
	if(x-2>=0 && y+1<=100 && tim[x-2][y+1]>tim[x][y]+1){
		tim[x-2][y+1]=tim[x][y]+1;
		dfs(x-2,y+1);
	}
	if(x-2>=0 && y-1>=0 && tim[x-2][y-1]>tim[x][y]+1){
		tim[x-2][y-1]=tim[x][y]+1;
		dfs(x-2,y-1);
	}
}
int main(){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	//freopen("jump.out","w",stdout);
	scanf("%d",&t);
	for(int i=0;i<=100;i++)for(int j=0;j<=100;j++)tim[i][j]=0x3f3f3f3f;
	tim[0][0]=0;
	dfs(0,0);
	//for(int i=0;i<=50;i++)for(int j=0;j<=50;j++)printf("%2d%c",tim[i][j],j==50?'\n':' ');
	/*while(t--){
		scanf("%d%d",&x,&y);
		x=abs(x),y=abs(y);
		if(x>y)swap(x,y);
		int c=(2*x-y)/3;
		x-=3*c,y-=3*c;
		
	}*/
	/*while(t--){
		int ans=0;
		scanf("%d%d",&x,&y);
		x=abs(x),y=abs(y);
		if(x>y)swap(x,y);
		int c=x/3;
		ans+=2*c;
		x-=3*c,y-=3*c;
		if(x==1)ans++,y-=2;
		if(x==2)ans++,y-=1;
		if(y==1)ans+=3;
		else if(y!=0)ans+=(y+2)/4*2+(y&1);
		printf("%d\n",ans);
	}*/
	while(t--){
		scanf("%d%d",&x,&y);
		x=abs(x),y=abs(y);
		if(x>y)swap(x,y);
		int ans=0;
		if(y-x>90){
			int p=min(x,y-x);
			x-=p,y-=2*p;
			ans+=p;
		}
		if(x>100){
			int p=(x-98)/3;
			ans+=2*p;
			x-=3*p,y-=3*p;
		}
		if(y>100)ans+=(y+2)/4*2+(y&1);
		else ans+=tim[x][y];
		printf("%d\n",ans);
	}
	return 0;
}

