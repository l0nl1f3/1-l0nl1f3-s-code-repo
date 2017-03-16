#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
int T,x,y;
void s_y0(){
	if((x=x<0?-x:x)&1){
		if(x<=6)puts("3");else printf("%d\n",3+((x-6)/4+1)*2);
	}else printf("%d\n",((x-1)/4+1)*2); 
}
void s_exy(int px=0){
	x=abs(x);
	if(x<=3){
		if(x==1)puts("2");
		if(x==2)puts("4");
		if(x==3)puts("2");
	} else printf("%d\n",(x-1)/3*2+2);
}
#define M 1001
#define f(x,y) g[((x)+M)][((y)+M)]
#define I(x,y) inq[((x)+M)][((y)+M)]
int g[M+M][M+M],inq[M+M][M+M];
queue<Pii>q;
int dx[]={-1,1,2,-2,-1,1,2,-2};
int dy[]={2,-2,1,-1,-2,2,-1,1};
void zdl(){
	memset(g,0x3f,sizeof(g));
	q.push(mp(0,0));I(0,0)=1;f(0,0)=0;
	while(!q.empty()){
		Pii c=q.front();q.pop();I(c.fi,c.se)=0;
		for(int i=0;i<8;i++){
			int nx=c.fi+dx[i],ny=c.se+dy[i];
			if(abs(nx)>1000||abs(ny)>1000)continue;
			if(f(nx,ny)>f(c.fi,c.se)+1){
				f(nx,ny)=f(c.fi,c.se)+1;
				if(!I(nx,ny))q.push(mp(nx,ny)),I(nx,ny)=1;
			}
		} 
	}
}
void zgl(){
	puts("≥ˆÃ‚»À**");
}
int main(){
	FO(jump);
	T=gi;
	while(T--){
		x=gi;y=gi;
		if(y==0)s_y0();
		else if(x==y)s_exy();
		else if(x<=1000&&y<=1000)zdl(); 
		else zgl();
	}
	return 0;
}

