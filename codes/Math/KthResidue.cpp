/*
 * find x for x^t = m (mod p) p is prime
 * 1. find PrimitiveRoot of p (assume it is v) O( sqrt(n)log(n) )
 * 2. v^(at) = v^b
 * 3. use Bsgs to find b O( sqrt(n) + m*log(m) )
 * 4. use ex_gcd to find a(ax + by = gcd, at + b(p-1) = gcd) O(log(n))
 */
LL mypow(LL v, LL t, LL md = mod) {
	LL res = 1;
	while (t) {
		if (t & 1) res = res*v%md;
		t >>= 1;
		v = v*v%md;
	}
	return res;
}
LL gcd(LL v1, LL v2){
	while (v1) {
		LL tmp = v2 % v1;
		v2 = v1;
		v1 = tmp;
	}
	return v2;
}
struct KthResidue{
	struct PriRoot{
		int a[MXN], cntp;
		LL phi(LL n){
			int h = sqrt(n);
			LL res = n, v = n;
			for (int i = 2; i <= h; i++) {
				if (v % i == 0) {
					res = res / i * (i - 1);
					while (v % i == 0) v /= i;
				}
			}
			if (v != 1) res = res / v * (v - 1);
			return res;
		}
		int solve(LL n){
			LL num = phi(n); // if n is prime, num = n - 1
			LL v = num;
			int h = sqrt(num);
			cntp = 0;
			for (int i = 2; i <= h; i++) {
				if (v % i == 0) {
					a[++cntp] = i;
					while (v % i == 0) v /= i;
				}
			}
			if (v != 1) a[++cntp] = v;
			v = num;
			for (int i = 2; i < n; i++) {
				if (gcd(n, i) != 1) continue;
				bool ok = 1;
				for (int j = 1; j <= cntp; j++) {
					if (mypow(i, v / a[j], n) == 1) {
						ok = 0; break;
					}
				}
				if (ok) return i;
			}
			return -1;
		}
	}root;
	struct Bsgs{
		map<LL, int>mp;
		LL solve(LL v, LL m, LL p){
			mp.clear();
			int h = ceil( sqrt(p + 0.5) );
			LL cv = 1;
			for (int i = 0; i < h; i++) {
				mp[cv] = i;
				cv = cv*v%p;
			}
			cv = mypow(cv, p - 2, p);
			int ok = 0, ans = 0;
			for (int i = 0; i <= h; i++) {
				if (mp.find(m) != mp.end()) {
					ans += mp[m];
					ok = 1; break;
				}
				ans += h;
				m = m*cv%p;
			}
			return ok ? ans : -1;
		}
	}bsgs;

	PLL ex_gcd(LL a, LL b){
		if(b == 0) return MP(1, 0);
		else{
			LL p = a / b;
			PLL q = ex_gcd(b, a % b);
			return MP(q.S, q.F - q.S * p);
		}
	}
	
	LL solve(LL t, LL m, LL p){
		LL v = root.solve(p);
		LL gd = bsgs.solve(v, m, p);
		if (gd == -1) return -1;

		PLL res = ex_gcd(t, p-1);
		LL val = (t*res.F + (p-1)*res.S);
		if (gd % val) return -1;
		LL num = (res.F*(gd / val)%(p-1) + p - 1) % (p-1);
		return mypow(v, num, p);
	}
}residue;
