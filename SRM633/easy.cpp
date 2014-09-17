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

class PeriodicJumping {
public:
	int minimalTime(int, vector<int> );
};

int PeriodicJumping::minimalTime(int X, vector<int> jp) {
	long long x, sum, now, mxall, mx, ti;
	int i, n;
	x = abs(X);
	n = jp.size();
	mxall = 0;
	mx = 0;
	sum = 0;
	for (i = 0; i < n; ++i) {
		mxall = max(mxall, (long long) jp[i]);
		sum += jp[i];
	}
	ti = x / sum;
	if (ti == 0) {
		now = 0;
		mx = 0;
	} else {
		now = ti * sum;
		mx = mxall;
	}
	if (now >= x && mx <= x + now - mx)
		return ti * n;
	for (i = 0;; ++i) {
		now += jp[i % n];
		mx = max(mx, (long long) jp[i % n]);
		if (now >= x && mx <= x + now - mx)
			break;
	}
	return ti * n + i + 1;
}
