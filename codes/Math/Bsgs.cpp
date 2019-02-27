/* solve x for v^x = m mod p 
	 p is prime
	 O( sqrt(p)log(p) )			*/
struct Bsgs{
	LL mypow(LL v, LL t, LL md) {
		LL res = 1;
		while (t) {
			if (t & 1) res = res*v%md;
			t >>= 1;
			v = v*v%md;
		}
		return res;
	}
	map<LL, int>mp;
	LL solve(LL p, LL v, LL m){
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

