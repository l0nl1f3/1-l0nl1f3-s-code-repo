#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1010
#define ll long long
using namespace std;

int n,a[N],b[N];
ll m,f[N];
int mxa[N][N],mnb[N][N];
ll sumb[N][N];

bool judge(int x){
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(sumb[j][i]<=x&&mnb[1][j-1]>mxa[j][i]){
				f[i]=min(f[i],f[j-1]+mxa[j][i]);
			}
		}
	}
	if(f[n]<=m) return 1;
	return 0;
}

int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%I64d",&n,&m);
	ll l=0,r=0,mid,ans;
	memset(mnb,0x3f,sizeof(mnb));
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		r+=b[i];
		mnb[i][i]=b[i];
		mxa[i][i]=a[i];
		sumb[i][i]=b[i];
	}
	for(int k=2;k<=n;k++){
		for(int r=k;r<=n;r++){
			mnb[r-k+1][r]=min(mnb[r-k+1][r-1],b[r]);
			mxa[r-k+1][r]=max(mxa[r-k+1][r-1],a[r]);
			sumb[r-k+1][r]=sumb[r-k+1][r-1]+b[r];
		}
	}
	while(l<=r){
		mid=(l+r)>>1;
		if(judge(mid)){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
