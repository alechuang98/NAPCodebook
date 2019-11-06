int a[201][201];
struct DLX {
	int L[MXN], R[MXN], U[MXN], D[MXN];
	int rr[MXN], cc[MXN], S[MXN];
	int re[MXN], bst[MXN], ans;
	int n, m, cntp;
	void init() {
		for (int i = 0; i <= m; i++) {
			L[i] = i - 1; R[i] = i + 1;
			U[i] = D[i] = i;
			S[i] = 0;
		}
		L[0] = m; R[m] = 0;
		cntp = m + 1;
		for (int i = 1; i <= n; i++) {
			int f = -1;
			for (int j = 1; j <= m; j++) {
				if (!a[i][j]) continue ;
				if (f == -1) f = cntp;
				L[cntp] = cntp - 1; R[cntp] = cntp + 1;
				U[cntp] = U[j]; D[U[j]] = cntp;
				D[cntp] = j; U[j] = cntp;
				rr[cntp] = i; cc[cntp] = j;
				S[j]++;
				cntp++;
			}
			if (f != -1) {
				L[f] = cntp - 1;
				R[cntp-1] = f;
			}
		}
	}
	void cover(int c) {
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		for (int i = D[c]; i != c; i = D[i]) {
			for (int j = R[i]; j != i; j = R[j]) {
				S[cc[j]]--;
				D[U[j]] = D[j]; U[D[j]] = U[j];
			}
		}
	}
	void uncover(int c) {
		for (int i = U[c]; i != c; i = U[i]) {
			for (int j = L[i]; j != i; j = L[j]) {
				S[cc[j]]++;
				D[U[j]] = j; U[D[j]] = j;
			}
		}
		R[L[c]] = c; L[R[c]] = c;
	}
	void dfs(int dep) {
		if (dep > ans) return ;
		if (R[0] == 0) {
			ans = min(ans, dep);
			return ;
		}
		int c = R[0];
		for (int i = R[0]; i != 0; i = R[i]) {
			if (S[i] < S[c]) c = i;
		}
		cover(c);
		for (int i = D[c]; i != c; i = D[i]) {
			re[dep] = rr[i];
			for (int j = R[i]; j != i; j = R[j]) {
				cover(cc[j]);
			}
			dfs(dep+1);
			for (int j = L[i]; j != i; j = L[j]) {
				uncover(cc[j]);
			}
		}
		uncover(c);
		return ;
	}
	int solve(int _n, int _m) {
		n = _n, m = _m;
		init(); ans = n + 1;
		dfs(0);
		if (ans == n + 1) return -1;
		return ans;
	}
} dlx;