#include<bits/stdc++.h>
#define ll long long 
using namespace std;
template<typename T>
inline bool cmin(T &a,const T &b){
	return a>b?a=b,1:0;
}
template<typename T>
inline bool cmax(T &a,const T &b){
	return a<b?a=b,1:0;
}
#define N 101234
/*
1 2 0 3 2
0 1 2 3 4
0 9 8 9 0

1 0 0
2 1 9
0 2 8
3 3 9
2 4 0
*/
int a1,b1,c1,d1,ms;
inline void upd(int a,int b,int c,int d){
	int ns=(d-b+1)*(c-a+1);
	// printf("%d %d -> %d %d\n",a,b,c,d);
	if(ns>=ms){
		a1=a;b1=b;c1=c;d1=d;ms=ns;
	}
}

int n,m,tg,h[N],h2[N],g[2333],gs[2333];
vector<int>a[N],s[N],cc[N];
int main(){
	int i,j,k;
	//freopen("info.txt","w",stdout);
	scanf("%d%d",&n,&m);
	if(n<=m){
		for(i=0;i<n;i++)a[i].resize(m);
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)	
				scanf("%d",&a[i][j]);
	}else{
		tg=1;
		swap(n,m);
		for(i=0;i<n;i++)a[i].resize(m);
		for(i=0;i<m;i++)
			for(j=0;j<n;j++)
				scanf("%d",&a[j][i]);
	}
	for(i=0;i<n;i++)s[i].resize(m),cc[i].resize(m);
	for(i=0;i<m;i++)
		for(s[0][i]=(1<<a[0][i]),cc[0][i]=(a[0][i]!=0),j=1;j<n;j++){
			s[j][i]=s[j-1][i]^(1<<a[j][i]);
			cc[j][i]=cc[j-1][i]+(a[j][i]!=0);
		}
	int a,b,c,d;
	for(c=0;c<n;c++)
		for(d=c;d<n;d++){
			for(h[0]=s[d][0]^(c?s[c-1][0]:0),
				h2[0]=cc[d][0]-(c?cc[c-1][0]:0),
				i=1;i<m;i++){
					h[i]=h[i-1]^  (s[d][i]^(c?s[c-1][i]:0));
					h2[i]=h2[i-1]+(cc[d][i]-(c?cc[c-1][i]:0));
			}
			memset(g,0,sizeof(g));
			memset(gs,0,sizeof(gs)); 
			//printf("%d %d:\n",c,d);
			for(i=0;i<m;i++){
				int nw=h[i],tow,bc=0;
				//printf("i = %d %d\n",i,nw);
				for(k=0;k<=9;k++)if(nw>>k&1)bc++;
				if(bc<=1&&h2[i]>1){
					//cout<<c<<","<<d<<","<<i<<","<<h2[i]<<endl;
					//cout<<"~"<<__LINE__<<endl;
					upd(c,0,d,i);
				}else{
					tow=nw;
					for(k=0;k<=10;k++){
						if(k<10)tow=nw^(1<<k);
						else tow=nw;
						if(gs[tow]&&h2[i]-h2[g[tow]]>1)
							upd(c,g[tow]+1,d,i);
					}
				}
				if(!gs[h[i]])gs[h[i]]=1,g[h[i]]=i;
			}
		}
	if(!ms)
	ms=1;
	
		if(!tg)

			printf("%d\n%d %d %d %d",ms,a1,b1,c1,d1); 
		else
			printf("%d\n%d %d %d %d",ms,b1,a1,d1,c1); 
		
	return 0;
}

