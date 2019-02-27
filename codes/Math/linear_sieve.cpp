int ck[MXN];
vector<int> pr;
void linear_sieve(){
	for (int i = 2; i < MXN; i++) {
		if(!ck[i]) pr.pb(i);
		for (int j = 0; i*pr[j] < MXN; j++){
			ck[ i*pr[j] ] = pr[j];
			if(i % pr[j] == 0) break;
		}
	}
}
