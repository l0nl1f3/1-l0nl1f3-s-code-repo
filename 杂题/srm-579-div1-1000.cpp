#include<bits/stdc++.h>
#define gmax(a,b)  (a)=(a)>(b)?(a):(b) 
using namespace std;
int n;
double ans,R[55],P[55],S[55];
double dp[55][55][55][55];
class RockPaperScissors{
	public:
		double bestScore(vector <int> rr, vector <int> pp, vector <int> ss){
			n=rr.size();
			for(int i=0;i<n;i++){
				R[i]=rr[i]/300.0;
				P[i]=pp[i]/300.0;
				S[i]=ss[i]/300.0;
			}
			for(int a=0;a<n;a++){
				dp[a][0][0][0]=1.0;
				for(int i=0;i<n;i++)
					for(int j=i;j+1;j--)
						for(int k=i-j;k+1;k--)
							for(int s=i-j-k;s+1;s--) {
								if(i!=a){
								dp[a][j+1][k][s]=dp[a][j+1][k][s]+1.0*(j+k+s+1)/(i+1)*R[i]*dp[a][j][k][s];
								dp[a][j][k+1][s]=dp[a][j][k+1][s]+1.0*(j+k+s+1)/(i+1)*P[i]*dp[a][j][k][s];
								dp[a][j][k][s+1]=dp[a][j][k][s+1]+1.0*(j+k+s+1)/(i+1)*S[i]*dp[a][j][k][s];		
								}dp[a][j][k][s]=dp[a][j][k][s]*(1-1.0*(j+k+s)/(i+1));		
							}	
			}
			for(int i=0;i<n;i++){
				for(int j=0;j<n-i;j++){
					for(int k=0;k<n-i-j;k++){
						double r,p,s;
						r=p=s=0;
						//face i rock k scissor j paper
						for(int a=0;a<n;a++){
							double t=dp[a][i][j][k],m=n-i-j-k;
							r=r+t/m*R[a];
							p=p+t/m*P[a];
							s=s+t/m*S[a];
						}
						double tmp=0.0;
						gmax(tmp,3*r+p);
						gmax(tmp,3*p+s);
						gmax(tmp,3*s+r);
						/*
						old version fucking possiblities
						gmax(ans,3*r+p);
						gmax(ans,3*p+s);
						gmax(ans,3*s+r);*/
						ans+=tmp;		
					}
				}
			}
			return ans;
		} 
}zy;
vector<int>a,b,c;
int main(){
	a={300};
	b={0};
    c={0};
    cout<<zy.bestScore(a,b,c); 
}

