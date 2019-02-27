PLL ex_gcd(LL a, LL b){
	if(b == 0) return MP(1, 0);
	else{
		LL p = a / b;
		PLL q = ex_gcd(b, a % b);
		return MP(q.S, q.F - q.S * p);
	}
}

