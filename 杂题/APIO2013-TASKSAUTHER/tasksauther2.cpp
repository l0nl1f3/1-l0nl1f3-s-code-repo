#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	freopen("tasksauthor2.out","w",stdout);
	int i,j;
	printf("%d\n",n=100);
	int m=1000,v=2333;
	for(i=0;i<n;i++,puts("")){
		int e=min(m,15);
		m-=e;
		printf("%d ",e+(i!=0));
		if(i!=0)printf("%d %d ",i-1,v);
		for(j=1;j<=e;j++)printf("%d %d ",i,v);
	}
	int q=10;
	cout<<q<<endl;
	while(q--)
	printf("%d %d\n",99,0);
}
