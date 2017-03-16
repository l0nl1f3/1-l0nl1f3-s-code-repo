#include <ctime>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 4e5;
const int A = 1e6;
int K;
int main() {
	freopen("magic.in", "w", stdout);
	srand(time(NULL));
	K = (ll)rand() * rand() % A + 1;
	printf("%d %d\n", N, K);
	for (int i = 1; i <= N; ++i) {
		int x = (ll)rand() * rand() % K;
		printf("%d ", x);
	}
	fclose(stdin);
	fclose(stdout);
}
