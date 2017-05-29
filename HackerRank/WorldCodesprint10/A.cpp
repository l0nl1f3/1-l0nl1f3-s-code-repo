#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main(){
	scanf("%d%d%d",&a,&b,&c);
	printf("%d",min(a*10,100)+min(b*10,100)+min(c*10,100));
}
