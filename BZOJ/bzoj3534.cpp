#include<bits/stdc++.h>
using namespace std;
#define eps (1e-10) 
#define N 55
int n;double a[N][N];
int main(){
	int i,j,k;double l=1,m;
	for(scanf("%d",&n),i=0;i<n;i++)
		for(j=0;j<n;j++){
			scanf("%lf",&a[i][j]);if(i!=j){
				if(a[i][j]>1-eps)a[i][j]-=eps;
				if(i<j)l*=(1-a[i][j]);
				a[i][j]/=1-a[i][j];	
			}
		}
	for(i=0;i<n;i++)for(j=0;j<n;j++)a[i][i]-=(i!=j)*a[i][j];
	for(--n,i=0;i<n;i++){
		for(j=k=i,j++;j<n;j++)if(fabs(a[j][i])>fabs(a[k][i]))k=j;
		if(fabs(a[k][i])<eps)continue;
		if(k!=i)swap(a[k],a[i]);
		for(k=0;k<n;k++)if(k!=i){
			m=a[k][i]/a[i][i];
			for(j=i+1;j<n;j++)a[k][j]-=m*a[i][j];
		}
		if(fabs(a[i][i])<eps)l=0;
	}
	for(i=0;i<n;i++)l*=fabs(a[i][i]);
	printf("%.10lf",l);
}
