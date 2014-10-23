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
#include <string.h>
using namespace std;

#define N 2009
#define M 2000009
#define inf 2000000000
#define INT int
struct E {
	int t, next;INT flow, cap;
} edge[M];
int node[N], eid;
vector<int> e[N];
int rr[N];
int que[N];
void init() {
	eid = 0;
	memset(rr, -1, sizeof(rr));
	memset(node, -1, sizeof(node));
}
void addedge(int a, int b, INT c) {
	edge[eid].t = b;
	edge[eid].cap = c;
	edge[eid].flow = 0;
	edge[eid].next = node[a];
	node[a] = eid++;

	edge[eid].t = a;
	edge[eid].cap = 0; //0单向，c双向
	edge[eid].flow = 0;
	edge[eid].next = node[b];
	node[b] = eid++;
}
int bfs(int s, int t, int n) {
	memset(rr, -1, sizeof(rr));
	int i;
	for (i = 0; i < n; ++i)
		e[i].clear();
	int u, v;
	int front = 0, rear = 1;
	rr[s] = 0;
	que[0] = s;
	while (rear > front) {
		u = que[front++];
		for (i = node[u]; i != -1; i = edge[i].next) {
			v = edge[i].t;
			if (rr[v] == -1 && edge[i].cap) {
				que[rear++] = v;
				rr[v] = rr[u] + 1;
			}
			if (rr[v] == rr[u] + 1)
				e[u].push_back(i);
		}
	}
	return (rr[t] != -1);
}
INT dinic(int s, int t, int n) {
	int st[N];
	INT maxflow = 0;
	int aux[N];
	int top, cur;
	int p, i, k;
	while (bfs(s, t, n)) {
		top = 0;
		st[top] = s;
		cur = s;
		while (1) {
			if (cur == t) {
				INT minc = inf;
				for (i = 0; i < top; ++i) {
					p = aux[i + 1];
					if (minc > edge[p].cap)
						minc = edge[p].cap, k = i;
				}
				for (i = 0; i < top; ++i) {
					p = aux[i + 1];
					edge[p].cap -= minc;
					edge[p ^ 1].cap += minc;
				}
				maxflow += minc;
				cur = st[top = k];
			}
			int len = e[cur].size();
			while (len) {
				p = e[cur][len - 1];
				if (edge[p].cap && rr[edge[p].t] == rr[cur] + 1)
					break;
				else {
					len--;
					e[cur].pop_back();
				}
			}
			if (len) {
				cur = st[++top] = edge[p].t;
				aux[top] = p;
			} else {
				if (top == 0)
					break;
				rr[cur] = -1;
				cur = st[--top];
			}
		}
	}
	return maxflow;
}

class ConnectingGame {
public:
	string isValid(vector<string>);
};

int f(char c) {
	if ('A' <= c && 'Z' >= c)
		return c - 'A';
	if ('a' <= c && 'z' >= c)
		return c - 'a' + 26;
	if ('0' <= c && '9' >= c)
		return c - '0' + 52;
}
int dir[8][2] = { 0, 1, 1, 0, 0, -1, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1 };
string ConnectingGame::isValid(vector<string> s) {
	int n, m;
	int i, j, k, ii, jj;
	n = s.size();
	m = s[0].size();
	int ss, t1, t2, t3, t4, t;
	ss = 62 * 2;
	t1 = 62 * 2 + 1;
	t2 = 62 * 2 + 2;
	t3 = 62 * 2 + 3;
	t4 = 62 * 2 + 4;
	t = 62 * 2 + 5;
	for (i = 0; i < n - 1; ++i) {
		for (j = 0; j < m - 1; ++j) {
			if (s[i][j] != s[i + 1][j] && s[i + 1][j] != s[i + 1][j + 1]
					&& s[i + 1][j + 1] != s[i][j + 1]
					&& s[i][j + 1] != s[i][j]) {
				init();
				for (ii = 0; ii < n; ++ii) {
					addedge(62 + f(s[ii][0]), t1, 1);
				}
				for (ii = 0; ii < n; ++ii) {
					addedge(62 + f(s[ii][m - 1]), t2, 1);
				}
				for (jj = 0; jj < m; ++jj) {
					addedge(62 + f(s[0][jj]), t3, 1);
				}
				for (jj = 0; jj < m; ++jj) {
					addedge(62 + f(s[n - 1][jj]), t4, 1);
				}
				addedge(t1, t, 1);
				addedge(t2, t, 1);
				addedge(t3, t, 1);
				addedge(t4, t, 1);
				addedge(ss, f(s[i][j]), 1);
				addedge(ss, f(s[i + 1][j]), 1);
				addedge(ss, f(s[i][j + 1]), 1);
				addedge(ss, f(s[i + 1][j + 1]), 1);

				for (ii = 0; ii < 62; ++ii) {
					addedge(ii, ii + 62, 1);
				}
				for (ii = 0; ii < n; ++ii) {
					for (jj = 0; jj < m; ++jj) {
						for (k = 0; k < 8; ++k) {
							int ti = ii + dir[k][0];
							int tj = jj + dir[k][1];
							if (ti >= n || tj >= m || ti < 0 || tj < 0)
								continue;
							addedge(f(s[ii][jj]) + 62, f(s[ti][tj]), 1);
						}
					}
				}
				//printf("%d\n", dinic(ss, t, t + 1));
				if (dinic(ss, t, t + 1) == 4)
					return "invalid";
			}
		}
	}
	return "valid";
}
