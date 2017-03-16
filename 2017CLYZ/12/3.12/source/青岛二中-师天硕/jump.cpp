#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long ll;
int getint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-')f=-1; ch=getchar();	}
	while('0'<=ch&&ch<='9') { x=x*10+ch-'0'; ch=getchar();	}
	return f*x;
}
#define N 2123
const int dx[]={ 1, 2, 2, 1,-1,-2,-2,-1};
const int dy[]={ 2, 1,-1,-2,-2,-1,1 , 2}; 
int f[N][N],vis[N][N];
pair<int,int > q[11234567];
int sx,sy;
bool inmp(int x,int y){
	return x>0&&y>0&&x<sx+300&&y<sy+300;
}
char ppp(int x){
	if(x==0) return '0';
	if(x<4) return '*';
	if(x==5) return '=';
	if(x==6) return '+';
	if(x==7) return '&';
	return '?'; 
}
int main(){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	memset(f,0x3f,sizeof(f)); 
	int fp=0,rp=0;
	sx=110,sy=110;
	f[sx][sy]=0; vis[sx][sy]=1;
	fp=rp=0; q[rp++]=make_pair(sx,sy);
	while(fp!=rp){
		int x=q[fp].first, y=q[fp++].second;
//		cout<<x<<" "<<y<<endl;
//		if(rp<0||fp>=)cout<<fp<<" "<<rp<<endl;
		for(int i=0;i<8;i++) {
			int nx=x+dx[i], ny=y+dy[i];
			if(!vis[nx][ny]&&inmp(nx,ny)) {
				vis[nx][ny]=1; f[nx][ny]=f[x][y]+1;
				q[rp++]=make_pair(nx,ny);
			}
		}
	} 
	
//	cout<<"vover"<<endl;
	 
	int t=getint(); 
	for(int ttt=1;ttt<=t;ttt++){
		int x=getint(), y=getint();
		x=max(x,-x); y=max(y,-y);
		if(x<y) swap(x,y);
		if(x<10) {printf("%d\n",f[sx+x][sy+y]); continue;}
		x++; y++;
		if((x+y)&1) {
			int z=(x-8+1); if(z%4==0) z=z/4; else z=z/4+1;
			int i=(x-8)%4; int mx=7+2*z-i; 
			int ans=2*z+3;
			if(y>mx) {
				int j=(y-mx); if(j%6==0) j=j/6; else j=j/6+1;
				ans=ans+2*j; 
			}
			printf("%d\n",ans);
		} else {
			int z=(x-6+1); if(z%4==0) z=z/4; else z=z/4+1;
			int i=(x-6)%4; int mx=6+2*z-i; 
			int ans=2*z+2;
			if(y>mx) {
				int j=(y-mx); if(j%6==0) j=j/6; else j=j/6+1;
				ans=ans+2*j; 
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}

