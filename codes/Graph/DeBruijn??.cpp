vector<int> v;
vector<vector<int>> res;
int t;
inline bool add() { res.push_back(v); if (--t == 0) return true; return false;}
bool rec(int i, int j, int l, int r, int dir){
	if (i > j) return false;
	int m = j - i + 1;
	int len = (r - l + 1) - m;
	
	if (dir == 0) {
		for (int d = 0; d < len; d++) {
			if (d & 1) {
				if (rec(i + 1, j, l + 1 + d, r, 1)) return true;
				for(int z = i; z <= j; z++) v[z]++;
				if (add()) return true;
			} else {
				if (rec(i + 1, j, l + 1 + d, r, 0))return true;
				v[i]++; 
				if (add()) return true;
			}
		}
	} else {
		for (int d = 0; d < len; d++) {
			if (d & 1) {
				if (rec(i, j - 1, l, r - d - 1, 0)) return true;
				for (int z = i; z <= j; z++) v[z]--;
				if (add()) return true;
			} else {
				if (rec(i, j - 1, l, r - d - 1, 1)) return true;
				v[j]--;
				if (add()) return true;
			}
		}
	}
	return false;
}
bool sol(int n, int m, int k) {
    t = k;
	for (int i = 1; i <= m; i++) v.push_back(i);
    res.push_back(v);
	if (--t) {
		if (!rec(0, m - 1, 1, n, 0)) return false ;
	}
	return true;
}