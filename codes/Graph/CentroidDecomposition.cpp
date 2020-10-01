void dfssz(int u) {
	ck[u] = true; siz[u] = 1, mxn[u] = 0;
	for (int x : edge[u]) {
		if (ck[x]) continue ;
		dfssz(x);
		mxn[u] = max(mxn[u], siz[x]);
		siz[u] += siz[x];
	}
}
void go(int u, int dpt, int d) {
	ck[u] = true; cdis[dpt][u] = d;
	for (int x : edge[u]) {
		if (ck[x]) continue ;
		go(x, dpt, d + 1);
	}
}
void dfs(int u, int dpt) {
	st.clear(); dfssz(u);
	int bst = -1, k = SZ(st);
	for (int v : st) {
		if (max(mxn[v], k - siz[v]) * 2 <= k) bst = v;
		ck[v] = false;
	}
	go(bst, dpt, 0);
	for (int v : st) {
		ck[v] = false;
		cprt[dpt][v] = bst;
		dd[bst].push_back(cdis[dpt][v]);
		if (dpt) re_dd[bst].push_back(cdis[dpt-1][v]);
	}
	sort(dd[bst].begin(), dd[bst].end());
	sort(re_dd[bst].begin(), re_dd[bst].end());

	cdep[bst] = dpt;
	ck[bst] = true;
	for (int v : edge[bst]) {
		if (ck[v]) continue ;
		dfs(v, dpt + 1);
	}
}
int qy(int v, int d) {
	int res = upper_bound(dd[v].begin(), dd[v].end(), d) - dd[v].begin();
	for (int i = cdep[v]; i >= 1; i--) {
		int pa = cprt[i-1][v], u = cprt[i][v];
		res += upper_bound(dd[pa].begin(), dd[pa].end(), d - cdis[i-1][v]) - dd[pa].begin();
		res -= upper_bound(re_dd[u].begin(), re_dd[u].end(), d - cdis[i-1][v]) - re_dd[u].begin();
	}
	return res;
}