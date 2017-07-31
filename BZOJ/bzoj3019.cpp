#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}

namespace io
{
	const int MAXBUF = 1 << 20;
	const int OUTPUT = 1 << 23;
	char B[MAXBUF], *S = B, *T = B;
	#define RG register
	#define getc() (S == T && (T = (S = B) + fread(B, 1, MAXBUF, stdin), S == T) ? 0 : *S++)
	#define fastcall __attribute__((optimize("-O3")))
	#define inline __inline__ __attribute__((always_inline))
	template<class Type> inline Type read()
	{
		RG Type aa = 0; RG bool bb = 0; RG char ch, *S = io::S, *T = io::T;
		for(ch = getc(); (ch < '0' || ch > '9') && ch != '-'; ch = getc())
			;
		for(ch == '-' ? bb = 1 : aa = ch - '0', ch = getc(); '0' <= ch && ch <= '9'; ch = getc())
			aa = aa * 10 + ch - '0';
		io::S = S, io::T = T; return bb ? -aa : aa;
	}
	int (*inp)() = read<int>;
	inline int gets(RG char *s)
	{
		RG char *iter = s, *S = io::S, *T = io::T;
		while(*iter = getc(), *iter == ' ' || *iter == '\n' || *iter == '\r')
			;
		while(*++iter = getc(), *iter != ' ' && *iter != '\n' && *iter != '\r')
			;
		*iter = 0;		
		io::S = S, io::T = T;
		return iter - s;
	}
	inline char get()
	{
		RG char ch;
		while(ch = getc(), ch == ' ' || ch == '\n' || ch == '\r')
			;
		return ch;
	}
	
	char buff[OUTPUT], *iter = buff;
	template<class T>inline void P(RG T x, RG char ch = '\n')
	{
		static int stack[110]; RG int O = 0; RG char *iter = io::iter;
		if(!x)*iter++ = '0';
		else
		{
			(x < 0) ? x = -x, *iter++ = '-' : 1;
			for(; x; x /= 10) stack[++O] = x % 10;
			for(; O; *iter++ = '0' + stack[O--])
				;
		}
		*iter++ = ch, io::iter = iter;
	}

	inline void puts(RG const char *s) {while(*s) *iter++ = *s++;}
	inline void output() {fwrite(buff, 1, iter - buff, stdout), iter = buff;}
}
using io :: inp;

const int MaxN = 401234, MaxM = MaxN << 2;
const int P = 1000000007;

int n, m, p[MaxN], chk[3][3];
int f[MaxN][3][3];

#define add(x, y) (x + y >= P ? x + y - P : x + y)
#define mul(x, y) ((LL) x * y % P)

int lb[MaxM], rb[MaxM], way[MaxM], a[MaxN];

void build(int p, int l, int r){
	lb[p] = l; rb[p] = r; way[p] = 1;
	if(l == r) return;
	build(p << 1, l, l + r >> 1);
	build(p << 1 | 1, (l + r >> 1) + 1, r);
} 

void seg_modify(int p, int l, int r, int q, int d){
	if(l == r){
		a[l] = d;
		if(d < 0) lb[p] = rb[p] = 0;
		return;
	}
	if(q <= l + r >> 1)
		seg_modify(p << 1, l, l + r >> 1, q, d);
	else 
		seg_modify(p << 1 | 1, (l + r >> 1) + 1, r, q, d);
	
	lb[p] = lb[p << 1] ? lb[p << 1] : lb[p << 1 | 1];
	rb[p] = rb[p << 1 | 1] ? rb[p << 1 | 1] : rb[p << 1];
	way[p] = mul(way[p << 1], way[p << 1 | 1]);
	if(rb[p << 1] && lb[p << 1 | 1])
		way[p] = mul(way[p], f[lb[p << 1 | 1] - rb[p << 1] + 1][a[rb[p << 1]]][a[lb[p << 1 | 1]]]);
}

bool modify(int q, int d){
	if(~ d){
		if(q > 1 && ~ a[q - 1]) if(chk[a[q - 1]][d]) return 0;
		if(q < n && ~ a[q + 1]) if(chk[d][a[q + 1]]) return 0;
	}
	seg_modify(1, 1, n, q, d);
	return 1;
}

int query(){
	int ans = way[1], i, j;
	if(lb[1] > 1){
		for(i = j = 0; i < 3; i++)
			j = add(j, f[lb[1]][i][a[lb[1]]]);
		ans = mul(ans, j);
	}	
	if(rb[1] < n){
		for(i = j = 0; i < 3; i++)
			j = add(j, f[n - rb[1] + 1][a[rb[1]]][i]);
		ans = mul(ans, j);
	}
	return ans;
}

char s[MaxN]; int T[MaxN];
int main() {
	int i, j, k, x, y;
	n = inp();
	for(i = 1; i <= n; i++) p[i] = inp();
	m = inp();
	for(i = 1; i <= m; i++){
		char ch[5];
		io :: gets(ch);
		chk[ch[0] - '0' - 1][ch[1] - '0' - 1] = 1;
	}
	for(i = 0; i < 3; i++) f[1][i][i] = 1;
	for(i = 2; i <= n; i++)
		for(k = 0; k < 3; k++)
			for(x = 0; x < 3; x++)
				if(!chk[x][k]){
					for(j = 0; j < 3; j++)
						f[i][j][k] = add(f[i][j][k], f[i - 1][j][x]);
				}

	io :: gets(s + 1);	
	for(i = 1; i <= n; i++) a[i] = T[i] = s[i] - '0' - 1;
	 
	int ans = 0;
	build(1, 1, n);
	for(int lcp = n; lcp; lcp--){
		int np = p[lcp];
		for(i = 0; i < T[np]; i++)
			if(modify(np, i))
				ans = add(ans, query());
		modify(np, -1);
	}
	cout << add(ans, 1);
	return 0;
}



