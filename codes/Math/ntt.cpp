const int P = 998244353, root = 3, MAXNUM=2097152;
int bigmod(LL v, LL t){
	LL res = 1;
	while(t){
		if(t & 1) res = res*v%mod;
		v = v*v%mod;
		t >>= 1;
	}
	return res;
}
int inv(LL a, LL b){
	if(a == 1)return 1;
	return ( ( (a - inv(b%a,a))*b + 1) / a )%b;
}
std::vector<long long> ps(MAXNUM);
struct poly{
	vector<LL> co;
	int n;//polynomial degree = n
	poly(int d = 0){n = d; co.resize(n,0); }
	void init(int _n, LL _co[]){
		n = _n; 
		co.resize(n);
		for(int i = 0; i < n; ++i) 
			co[i] = _co[i];
	}
	void trans2(int NN){
		int r = 0;
		while( (1<<r) < (NN>>1) ) ++r;
		for(int N = 2; N <= NN; N <<= 1, --r){
			for(int st = 0; st < NN; st += N){
				int ss = st + (N>>1);
				for(int i = (N>>1)-1; i >= 0; --i){
					LL a = co[st + i], b = ps[i<<r]*co[ss+i]%P;
					co[st+i] = a + b; if(co[st+i] >= P) co[st + i] -= P;
					co[ss+i] = a - b; if(co[ss+i] < 0) co[ss + i] += P;
				}
			}
		}
	}
	void trans1(int NN){
		int r = 0;
		for(int N = NN; N > 1; N >>= 1, ++r){
			for(int st = 0; st < NN; st += N){
				int ss = st + (N>>1);
				for(int i = (N>>1)-1; i >= 0; --i){
					LL a = co[st + i], b = co[ss + i];
					co[st+i] = a + b; if(co[st+i] >= P) co[st+i] -= P;
					co[ss+i] = (a + P - b)*ps[i<<r]%P;
				}
			}
		}
	}
	poly operator*(const poly& _b) const{
		poly a = *this, b = _b;
		int k = n + b.n, N = 1;
		while( N <= k ) N <<= 1;
		a.co.resize(N,0); b.co.resize(N,0);
		int r = bigmod(root, (P-1)/N), Ni = inv(N, P);
		ps[0] = 1;
		for(int i = 1; i < N; ++i) ps[i] = ps[i-1]*r%P;
		a.trans1(N); b.trans1(N);
		for(int i = 0;i < N; ++i) a.co[i]= a.co[i]*b.co[i]%P;
		r = inv(r, P);
		for(int i = 1; i < N / 2; ++i) swap(ps[i], ps[N-i]);
		a.trans2(N);
		for(int i = 0; i < k; ++i) a.co[i] = a.co[i]*Ni%P;
		a.n = k - 1; return a;
	}
};
