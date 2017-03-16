#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x<0) x=-x;
		if(y<0) y=-y;
		if(x<y) swap(x,y);
		if(x==0&&y==0){
			printf("0\n");
			continue;
		}
		if(x==1&&y==0){
			printf("3\n");
			continue;
		}
		if(x==y){
			if(x==2){
				printf("4\n");
			}else{
				int d=(x-1)/3;
				printf("%d\n",2*(d+1));
			}
		}else{
			int base=y*2;
			if(x<base){
				int d=(base-x-1)/3;
				int mx=y+1-d;
				printf("%d\n",mx-(base-x-1)%3);
			}else if(x==base){
				printf("%d\n",y);
			}else{
				int d=(x-base)/4;
				int mn=y+d*2;
				printf("%d\n",mn+(x-base)%4);
			}
		}
	}
	return 0;
}
