typedef long long LL;
LL powmo(LL a,LL b,LL n){
	LL r = 1;
	for(;b;b>>=1){
		if(b&1) r = r*a%n;
		a = a*a%n;
	}
	return r;
}
LL nabs(LL x, LL p){
	return (x%p+p) % p;
}
// Cipolla alogrithm O( log^2(p) );
LL cip(LL n, LL p){ // solve for x s.t. x^2 == n (mod p);
	if(p == 2 || n <= 1) return n;
	if(powmo(n,p-1>>1,p) == p-1) return -1; // no solution; 
	mt19937_64 rd(time(0));
	LL a = p-1;
	while(powmo(nabs(a*a-n,p), p-1>>1, p) != p-1) a = rd() % p;
	LL b = nabs(a*a-n,p);
	LL nx = a, ny = 1;
	LL rx = 1, ry = 0;;
	LL bb = p+1>>1;
	for(;bb;bb>>=1){
		if(bb&1) {
			LL tmp = rx;
			rx = (rx*nx + ry*ny%p*b) % p;
			ry = (ry*nx + tmp*ny) % p;
		}
		LL tmp = ny;
		ny = 2 * nx%p * ny%p;
		nx = (nx*nx + tmp*tmp%p*b) % p;
	}
	return rx;
}
