#include <cmath>
#include <cstdio>
 
const int N = 5100;
const double PI = acos(-1.0);
int n, sz, alpha;
double ans, sinA, cosA, sum, prod;
bool exist[N][N];
void genHilbert() {
  sz = 1;
  exist[1][1] = true;
  double a = alpha / 180.0 * PI;
  sinA = sin(a), cosA = cos(a);
  sum = sinA + cosA, prod = sinA * cosA;
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= sz; ++j) 
      for (int k = 1; k <= sz; ++k) {
        exist[j][k + sz + 1] = exist[j][k];
        exist[k + sz + 1][sz - j + 1] = !exist[j][k];
        exist[sz - k + 1 + sz + 1][j + sz + 1] = !exist[j][k];
      }
    int mid = sz + 1;
    sz = sz * 2 + 1;
    for (int j = 1; j <= sz; ++j) 
      exist[mid][j] = true,exist[j][mid] = (j >= mid);
  }
}
double calc(double h) {
  if (!alpha) return 1.0;
  if (alpha <= 45) {
    if (h <= sinA) return h * h;
    if (h <= cosA) return (h * 2.0 - sinA) * sinA;
    h = sum - h;
    return prod * 2.0 - h * h;
  }
  if (h <= cosA) return h * h;
  if (h <= sinA) return (h * 2.0 - cosA) * cosA;
  h = sum - h;
  return prod * 2.0 - h * h;
}
void dfs(int x, int y, double h) {
  if (h <= 1e-8 || !exist[x][y]) return ;
  if (h > sum) h = sum;
  exist[x][y] = false;
  ans += calc(h);
  dfs(x - 1, y, h + cosA);
  dfs(x, y - 1, h + sinA);
  dfs(x + 1, y, h - cosA);
  dfs(x, y + 1, h - sinA);
}
 
int main() {
  scanf("%d%d", &n, &alpha);
  genHilbert();
  for (int i = 1; i <= sz; ++i)
    dfs(sz, i, cosA);
  if (alpha) ans /= prod * 2.0;
  printf("%.6lf\n", ans);
  return 0;
}
 
 
