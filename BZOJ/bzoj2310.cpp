#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){	return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){	return a<b?a=b,1:0;}
#define N 10
#define M 10000
int n,m,up,ok,sn,qn,gt,ans,inf=1e9,f[M],g[M],mth[M],s[M],st[M],v[N][N],lg[M][N],id[1<<(2*N+1)];
int gb(int x,int i){return x>>(i<<1)&3;}
void cpy(){for(int i=1;i<=qn;i++)g[i]=f[i];}
void clr(){for(int i=1;i<=qn;i++)f[i]=-inf;}
int main(){
	//freopen("hj.txt","w",stdout);
	int i,j,k,p,q,x,y,z;
	scanf("%d%d",&n,&m);			
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&v[i][j]);
	up=1<<(2*(m+1));ans=-inf;
	for(i=0;i<up;i++){
		for(ok=1,j=sn=gt=0;j<=m;j++){
			k=gb(i,j);
			if(k==1)s[++sn]=j;
			if(k==2){
				if(!sn){ok=0;break;}
				mth[s[sn]]=j;
				mth[j]=s[sn--];
			}
			if(k==3)
				if(++gt>2){ok=0;break;}
		
		}
		if(!sn&&ok){
			for(st[id[i]=++qn]=i,j=0;j<=m;j++)
				lg[qn][j]=mth[j]<<1;
		}
	}
	clr();f[1]=0;cpy();
	for(i=1;i<=n;i++){
		for(clr(),j=1;j<=qn;j++)
			if(g[j]>-inf&&!gb(st[j],m))
				f[id[st[j]<<2]]=g[j];
		cpy();
		for(j=1;j<=m;j++){
			for(cmax(ans,v[i][j]),clr(),k=1;k<=qn;k++)if(g[k]>-inf){
				p=g[k]+v[i][j];q=st[k];
				x=gb(q,j-1);y=gb(q,j);
				z=q^(x<<(j-1<<1))^(y<<(j<<1));
				cout<<k<<","<<q<<","<<x<<","<<y<<","<<z<<","<<p<<endl;
				if(!x&&!y){
					cmax(f[k],p-v[i][j]);
					cmax(f[id[z^(1<<(j-1<<1))^(2<<(j<<1))]],p);
					cmax(f[id[z^(3<<(j-1<<1))]],p);
					cmax(f[id[z^(3<<(j<<1))]],p);
				}
				else if(!x||!y){
					int o=x+y;
					cmax(f[id[z^o<<(j-1<<1)]],p);
					cmax(f[id[z^o<<(j<<1)]],p);
					if(o==3){
					if(!z)cmax(ans,p);
					}
					else{
						if(x)cmax(f[id[z^x<<lg[k][j-1]]],p);
						else cmax(f[id[z^y<<lg[k][j]]],p);
					}
				}else
					if(x==1&&y==1)cmax(f[id[z^lg[k][j]]],p);
					else if(x==2&&y==1)cmax(f[id[z]],p);
					else if(x==2&&y==2)cmax(f[id[z^3<<lg[k][j-1]]],p);
					else if(x==3&&y==3){if(!z)cmax(ans,p);}
					else if(x==3) cmax(f[id[z^y<<lg[k][j]]],p);
					else if(y==3) cmax(f[id[z^x<<lg[k][j-1]]],p);
				
				//for(int k=1;k<=5;k++)printf("%d ",f[k]);puts("");
			}
			cpy();
		}
	}
	cout<<ans;
	return 0;
}



