#include<bits/stdc++.h>
#define N 1234
using namespace std;
double bit[N],a[N][N],b[N],ans[N];
int n,m,g,nxt[N];char s[N][N],ch[N];
void gauss(int n){
	int i,j,k;
    for(i=1;i<=n;i++){
        for(k=j=i,j++;j<=n;j++)if(fabs(a[j][i])>fabs(a[k][i]))k=j;
        if (k!=i){
        	swap(a[k],a[i]);
            swap(b[k],b[i]);
        }
        for(j=i+1;j<=n;j++) 
        	if(a[j][i]){
            	double t=a[j][i]/a[i][i];
            	for(k=1;k<=n;k++)a[j][k]-=a[i][k]*t;
            	b[j]-=b[i]*t;
        	}
    }
    for(i=n;i>=1;i--){
        ans[i]=b[i];
        for(j=i+1;j<=n;j++)if(a[i][j]) ans[i]-=ans[j]*a[i][j];
        ans[i]/=a[i][i];
    }
}
int main(){
	int i,j,k;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(i=bit[0]=1;i<=m;i++) bit[i]=bit[i-1]*0.5; 
    for(i=1;i<=n;i++)
    	for(j=1;j<=n;j++) {
	        g=0;
	        for(k=1;k<=m;k++)ch[++g]=s[i][k];
	        for(k=1;k<=m;k++)ch[++g]=s[j][k];
	        nxt[1]=0;
		    for(int i=1;i<=g;i++) {
		        int j=nxt[i];
		        while(ch[j]!=ch[i]&&j) j=nxt[j];
		        nxt[i+1]=j+1;
		    } 
		    for(k=nxt[g+1];k>1;a[i][j]+=bit[m-k+1],k=nxt[k]);
     }
    for(i=1;i<=n;i++) a[i][n+1]=-bit[m];
    for(i=b[n+1]=1;i<=n;i++) a[n+1][i]=1.0;
    for(gauss(n+1),i=1;i<=n;i++) printf("%.7lf\n",ans[i]);
}
