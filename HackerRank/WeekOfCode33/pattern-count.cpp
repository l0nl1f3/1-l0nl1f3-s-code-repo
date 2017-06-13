#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmin(T &a,const T &b){
	return a>b?a=b,1:0;
}
template<typename T>
inline bool cmax(T &a,const T &b){
	return a<b?a=b,1:0;
}
int n,q;string s;
int main(){
	int i,j;
	scanf("%d",&q);
	while(q--){
		cin>>s;
		int ans=0;
		n=s.length();
		for(i=0;i<n;i++){
			if(s[i]=='1'){
				for(j=i+1;s[j]=='0';j++);
				if(j!=i+1&&s[j]=='1')ans++;
				i=j-1;
			}
		}
		cout<<ans<<endl;
	}

	return 0;
}


