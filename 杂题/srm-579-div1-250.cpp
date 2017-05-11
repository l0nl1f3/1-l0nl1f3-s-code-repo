#include<bits/stdc++.h>
using namespace std;

class UndoHistory{
	int n,m,len[1001];
	public:
		int solve(string i,string j){
			int k,a=i.size(),b=j.size();
			for(k=0;k<min(a,b)&&i[k]==j[k];k++);
			return k;
		}
		int minPresses(vector <string> l){
			int i,j,k=0;
			n=l.size();m=l[0].size()+n;
			for(i=0;i<n;i++)len[i]=l[i].size();
			for(i=1;i<n;i++){
				int t=0;
				if(solve(l[i],l[i-1])==len[i-1])
					t=len[i-1]+2;
				for(j=0;j<i;j++)t=max(t,solve(l[i],l[j]));
				k=k+len[i]-t+2;
			}
			return k+m;
		}
}b;
vector<string>a;
int main(){
	a.push_back("tomorrow");
	a.push_back("topcoder");
	cout<<b.minPresses(a);
}
