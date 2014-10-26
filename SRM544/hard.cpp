#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class SplittingFoxes {
public:
	int sum(long long, int, int, int);
};

long long pmod = 1000000007;

long long p[4][4];

void mul(long long a[][4], long long b[][4]) {
	int i, j, k;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			p[i][j] = 0;
			for (k = 0; k < 4; ++k) {
				p[i][j] += a[i][k] * b[k][j] % pmod;
				p[i][j] %= pmod;
			}
		}
	}
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j)
			a[i][j] = p[i][j];
	}
}
int SplittingFoxes::sum(long long n, int S, int L, int R) {
	int i, j, k;
	long long a[4][4];
	a[0][0] = ((S - L - R) % pmod + pmod) % pmod;
	a[0][1] = 0;
	a[0][2] = 0;
	a[0][3] = 0;


	a[1][0] = 0;
	a[1][1] = S;
	a[1][2] = (L - R + pmod) % pmod;
	a[1][3] = 0;

	a[2][0] = S;
	a[2][1] = (R - L + pmod) % pmod;
	a[2][2] = S;
	a[2][3] = 0;

	a[3][0] = 0;
	a[3][1] = S;
	a[3][2] = 0;
	a[3][3] = ((S + R) % pmod + L) % pmod;
	long long t[4][4];
	memset(t, 0, sizeof(t));
	t[0][0] = t[1][1] = t[2][2] = t[3][3] = 1;
	while (n) {
		if (n & 1)
			mul(t, a);
		mul(a, a);
		n >>= 1;
	}
	return t[3][0];
}
