struct Polyop {
	NTT<P, root, MAXN> ntt;
	static int nxt2k(int x) {
    int i = 1; for (; i < x; i <<= 1); return i;
  }
	void Mul(int n, LL a[], int m, LL b[], LL c[]) {
    static LL aa[MAXN], bb[MAXN];
    int N = nxt2k(n+m);
    copy(a, a+n, aa); fill(aa+n, aa+N, 0);
    copy(b, b+m, bb); fill(bb+m, bb+N, 0);
    ntt.tran(N, aa); ntt.tran(N, bb);
    for(int i = 0; i < N; i++) c[i] = aa[i] * bb[i] % P;
    ntt.tran(N, c, true);
  }
	void Inv(int n, LL a[], LL b[]) {
    // ab = aa^-1 = 1 mod x^(n/2)
    // (b - a^-1)^2 = 0 mod x^n
    // bb + a^-2 - 2 ba^-1 = 0
    // bba + a^-1 - 2b = 0
    // -bba + 2b = a^-1
    static LL tmp[MAXN];
    if (n == 1) {
			b[0] = mypow(a[0], P-2); 
			return;
		}
    Inv((n+1)/2, a, b);
    int N = nxt2k(n*2);
    copy(a, a+n, tmp2);
    fill(tmp+n, tmp+N, 0);
    fill(b+n, b+N, 0);
    ntt.tran(N, tmp); ntt.tran(N, b);
    for (int i = 0; i < N; i++) {
      LL t1 = (2 - b[i] * tmp[i]) % P;
      if (t1 < 0) t1 += P;
      b[i] = b[i] * t1 % P;
    }
    ntt.tran(N, b, true);
    fill(b+n, b+N, 0);
  }
	void Sqrt(int n, LL a[], LL b[]) {
    // (a+(b')^2) / 2b'
    static LL tmp[MAXN], tmp2[MAXN];
    if (n == 1) {
			b[0] = sqrt(a[0]); // if (!exist b[0]) => false
			return ;
		}
    int N = nxt2k(n*2);
		int m = (n+1)>>1;
    Sqrt(m, a, b);
		Inv(n, b, tmp);
		fill(tmp + n, tmp + N, 0);
		copy(a, a + n, tmp2);
		fill(tmp2 + n, tmp2 + N, 0);
		ntt.tran(N, tmp2); ntt.tran(N, tmp);
		for (int i = 0; i < N; i++)
			tmp2[i] = tmp2[i]*tmp[i]%P;
		ntt.tran(N, tmp2, true);
		for (int i = 0; i < n; i++)
			b[i] = (b[i] + tmp2[i]) * inv2 % P;
		fill(tmp2, tmp2 + N, 0);
		fill(tmp, tmp + N, 0);
		fill(b + n, b + N, 0);
  }
} op;

