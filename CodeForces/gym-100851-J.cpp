#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 1234
int n,m;char s[N],t[N];
void gen(char *s){
	for(int i=0;i<n;i++)s[i]='0'+(rand()&1); 
	puts(s);
}
char rev(char &x){
	return x=='0'?'1':'0';
}
int main(){
	int i;
	srand(20010403);
 	scanf("%d",&n); 
	for(m=0;!m;gen(s),fflush(stdout),scanf("%d",&m));
	if(m==n)return 0;
	t[0]=s[0];s[0]=rev(s[0]);
	for(i=1;i<n;i++){
		s[i]=rev(s[i]);puts(s);fflush(stdout);scanf("%d",&m);
		if(m==n)return 0;
		t[i]=m?s[i]:rev(s[i]);
		s[i]=rev(s[i]); 
    }
	puts(t);fflush(stdout);scanf("%d",&m);
	if(m==n)return 0; 
	for(i=0;i<n;i++)t[i]=rev(t[i]);
	puts(t);fflush(stdout);scanf("%d",&m);  
	return 0;
}


