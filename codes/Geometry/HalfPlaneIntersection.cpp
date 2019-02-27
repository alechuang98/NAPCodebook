Pt interPnt(Line l1, Line l2, bool &res){
	Pt p1, p2, q1, q2;
	tie(p1, p2) = l1; tie(q1, q2) = l2;
	double f1 = (p2 - p1) ^ (q1 - p1);
	double f2 = (p2 - p1) ^ (p1 - q2);
	double f = (f1 + f2);
	if(fabs(f) < eps){ 
		res = 0; return {0, 0}; 
	}
	res = true;
	return q1 * (f2 / f) + q2 * (f1 / f);
}
bool isin(Line l0, Line l1, Line l2){
	// Check inter(l1, l2) in l0
	bool res; Pt p = interPnt(l1, l2, res);
	return ( (l0.S - l0.F) ^ (p - l0.F) ) > eps;
}
/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.S - l.F) ^ (p - l.F) > 0
 */
/* --^-- Line.FI --^-- Line.SE --^-- */
vector<Line> halfPlaneInter(vector<Line> lines){
	int sz = SZ(lines);
	vector<double> ata(sz), ord(sz);
	for(int i = 0; i < sz; i++) {
		ord[i] = i;
		Pt d = lines[i].S - lines[i].F;
		ata[i] = atan2(d.Y, d.X);
	}
	sort( ALL(ord), [&](int i, int j) {
		if(fabs(ata[i] - ata[j]) < eps)
			return ( (lines[i].S - lines[i].F) ^
							 (lines[j].S - lines[i].F) ) < 0;
		return ata[i] < ata[j];
	});
	vector<Line> fin;
	for (int i = 0; i < sz; i++)
		if (!i || fabs(ata[ord[i]] - ata[ord[i-1]]) > eps)
			fin.pb(lines[ord[i]]);
	deque<Line> dq;
	for (int i = 0; i < SZ(fin); i++) {
		while (SZ(dq) >= 2 && !isin(fin[i], dq[SZ(dq) - 2], dq[SZ(dq) - 1])) 
			dq.pop_back();
		while (SZ(dq) >= 2 && !isin(fin[i], dq[0], dq[1]))
			dq.pop_front();
		dq.pb(fin[i]);
	}
	while (SZ(dq) >= 3 && !isin(dq[0], dq[SZ(dq) - 2], dq[SZ(dq) - 1]))
		dq.pop_back();
	while (SZ(dq) >= 3 && !isin(dq[SZ(dq) - 1], dq[0], dq[1])) 
		dq.pop_front();
	vector<Line> res(ALL(dq));
	return res;
}
