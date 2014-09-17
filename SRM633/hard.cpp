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

#define MAXN 10000
vector<int> conn[MAXN], rconn[MAXN];
bool visited[MAXN];
int sta[MAXN], top, mark[MAXN], color;
void dfs(int idx) {
	visited[idx] = true;
	for (int i = 0; i < conn[idx].size(); ++i)
		if (!visited[conn[idx][i]])
			dfs(conn[idx][i]);
	sta[top++] = idx;
}
void rdfs(int idx) {
	visited[idx] = true;
	mark[idx] = color;
	for (int i = 0; i < rconn[idx].size(); ++i)
		if (!visited[rconn[idx][i]])
			rdfs(rconn[idx][i]);
}
//n节点数，从0开始标号
void Kosaraju(int n) {
	int i;
	memset(visited, 0, sizeof(bool) * n);
	for (i = top = 0; i < n; ++i)
		if (!visited[i])
			dfs(i);
	memset(visited, 0, sizeof(bool) * n);
	for (i = top - 1, color = 0; i >= 0; --i)
		if (!visited[sta[i]])
			rdfs(sta[i]), ++color;
}
void addedge(int a, int b) {
	//cout << a << " " << b << endl;
	conn[a].push_back(b);
	rconn[b].push_back(a);
}

class GCDLCM {
public:
	string possible(int, string, vector<int> , vector<int> , vector<int> );
};

int prime[20000];

int v[205];

string GCDLCM::possible(int n, string type, vector<int> a, vector<int> b,
		vector<int> c) {
	int m, i, j;
	int pn = 0;
	m = a.size();
	for (i = 0; i < m; ++i) {
		int x = c[i];
		for (j = 2; j * j <= x; ++j) {
			if (x % j == 0) {
				prime[pn++] = j;
				while (x % j == 0)
					x /= j;
			}
		}
		if (x != 1)
			prime[pn++] = x;
	}
	if (pn == 0)
		return "Solution exists";
	sort(prime, prime + pn);
	j = 1;
	for (i = 1; i < pn; ++i) {
		if (prime[j - 1] != prime[i]) {
			prime[j] = prime[i];
			j++;
		}
	}
	pn = j;
	for (int r = 0; r < pn; ++r) {
		int y = prime[pn];
		int mx = 0;
		for (i = 0; i < m; ++i) {
			v[i] = 0;
			int x = c[i];
			while (x % y == 0) {
				x /= y;
				v[i]++;
			}
			mx = max(mx, v[i]);
		}
		int s = n * (mx + 1);
		int col = mx + 1;
		for (i = 0; i < 2 * s; ++i) {
			conn[i].clear();
			rconn[i].clear();
		}
		for (i = 0; i < n; ++i) {
			for (j = 0; j < mx; ++j) {
				addedge(i * col + j + 1, i * col + j);
				addedge(s + i * col + j, s + i * col + j + 1);
			}
		}
		for (i = 0; i < m; ++i) {
			if (type[i] == 'L') {
				addedge(a[i] * col + v[i], s + a[i] * col + v[i]);
				addedge(b[i] * col + v[i], s + b[i] * col + v[i]);
				if (v[i] != 0) {
					addedge(s + a[i] * col + v[i] - 1, b[i] * col + v[i] - 1);
					addedge(s + b[i] * col + v[i] - 1, a[i] * col + v[i] - 1);
				}
			} else {
				if (v[i] != 0) {
					addedge(s + a[i] * col + v[i] - 1, a[i] * col + v[i] - 1);
					addedge(s + b[i] * col + v[i] - 1, b[i] * col + v[i] - 1);
				}
				addedge(a[i] * col + v[i], s + b[i] * col + v[i]);
				addedge(b[i] * col + v[i], s + a[i] * col + v[i]);
			}
		}
		Kosaraju(2 * s);
		for (i = 0; i < s; ++i) {
			if (mark[i] == mark[i + s])
				break;
		}
		if (i != s)
			return "Solution does not exist";
	}
	return "Solution exists";
}
