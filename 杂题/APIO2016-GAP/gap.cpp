#include "gap.h"
#include <bits/stdc++.h>
using namespace std;
#include <stdio.h>
#include <stdlib.h>

static void my_assert(int k){ if (!k) exit(1); }

static int subtask_num, N;
static long long A[100001];
static long long call_count;
/*
long long findGap(int, int);

void MinMax(long long s, long long t, long long *mn, long long *mx)
{
	int lo = 1, hi = N, left = N+1, right = 0;
	my_assert(s <= t && mn != NULL && mx != NULL);
	while (lo <= hi){
		int mid = (lo+hi)>>1;
		if (A[mid] >= s) hi = mid - 1, left = mid;
		else lo = mid + 1;
	}
	lo = 1, hi = N;
	while (lo <= hi){
		int mid = (lo+hi)>>1;
		if (A[mid] <= t) lo = mid + 1, right = mid;
		else hi = mid - 1;
	}
	if (left > right) *mn = *mx = -1;
	else{
		*mn = A[left];
		*mx = A[right];
	}
	if (subtask_num == 1) call_count++;
	else if (subtask_num == 2) call_count += right-left+2;
}

int main()
{
	FILE *in = stdin, *out = stdout;
	my_assert(2 == fscanf(in, "%d%d", &subtask_num, &N));
	my_assert(1 <= subtask_num && subtask_num <= 2);
	my_assert(2 <= N && N <= 100000);
	for (int i=1;i<=N;i++) my_assert(1 == fscanf(in, "%lld", A+i));
	for (int i=1;i<N;i++) my_assert(A[i] < A[i+1]);
	fprintf(out, "%lld\n", findGap(subtask_num, N));
	fprintf(out, "%lld\n", call_count);
}*/
#define ll long long
ll i,j,k,x,y,z,lx,ln;
long long findGap(int T, int N)
{
	if(T==1){
		MinMax(0,1e18,&A[1],&A[N]); 
		for(i=2;i<=(N+1)/2;i++){
			MinMax(A[i-1]+1,A[N-i+2]-1,&A[i],&A[N-i+1]);
		}
		long long x=0;
		for(i=2;i<=N;i++)x=max(x,A[i]-A[i-1]);
		return x;
	}else{
		MinMax(0,1e18,&x,&y);
		//elements from x~y
		ll step=(y-x)/(N-1),ans=0;
		for(lx=y,ans=step,x;x<=y;x+=step+1){
			MinMax(x,x+step,&j,&k);
			if(~j){
				ans=max(ans,j-lx);
			}
			if(~k)lx=k;	
		}
		return ans;
	}
}
