#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
int x,y,t;
inline void Aireen(){ 
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&x,&y);
		x=abs(x);y=abs(y);
//		if()
		if(x>y) swap(x,y);
		if(!x){
			if(!y) puts("0");
			else if(y==1) puts("3");
			else if(y==2) puts("2");
			else if(y==3) puts("3");
			else printf("%d\n",y/4*2+y%4); 
		}
		else if(y>=(x<<1)){
			y-=(x<<1);
			printf("%d\n",x+y/4*2+y%4);
		}
		else if(x>=4){
			y-=x;x-=4;
			if(!(x%3)){
//				printf("%d\n",(2+x/3)*2-1);
				if(!y) printf("%d\n",(2+x/3)*2);
				else printf("%d\n",(2+x/3)*2-1+(y-1)/3+(y-1)%3);
				
			}
			else if(x%3==1){
				if(!y) printf("%d\n",(2+x/3)*2);
				else if(y==1) printf("%d\n",(2+x/3)*2+1);
				else printf("%d\n",(2+x/3)*2+(y-2)/3+(y-2)%3);
			}
			else printf("%d\n",(2+x/3)*2+y/3+y%3);
		}
		else{
			if(x==1) puts("2");
			else if(x==2) printf("%d\n",6-y); 
			else if(x==3) printf("%d\n",y-1);
		}
	}
}
int main(){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	Aireen();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

