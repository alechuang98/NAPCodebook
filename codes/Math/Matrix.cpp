struct Mat {
	int n, m;
	static const int N = (int)3e2 + 7;
	LL a[ N ][ N ];
	void init(int _n, int _m) {
		n = _n, m = _m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				a[i][j] = 0;
	}
	Mat operator *(const Mat &p2) {
		Mat res; res.init(n, p2.m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 1; k <= p2.m; k++)
					res.a[i][k] = (res.a[i][k] + a[i][j]*p2.a[j][k]) % mod;
		return res;
	}
	Mat operator ^(const LL &p2) {
		LL t = p2 - 1;
		Mat res = *this, x = *this;
		while (t) {
			if(t & 1) res = res*x;
			t >>= 1;
			x = x*x;
		}
		return res;
	}
};
