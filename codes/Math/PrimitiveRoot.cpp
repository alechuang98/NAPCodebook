/*
 * Primitive root exist only if :
 * P = 2, 4, prime^x, 2*prime^x
 * if Primitive root exist, then number of root = phi( phi(P) )
 * O( sqrt(P) + m*log(P-1) ) m = number of prime factor of phi(P)
 */
struct PriRoot{
	int a[MXN], cntp;
	LL mypow(LL v, LL t, LL md) {
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

