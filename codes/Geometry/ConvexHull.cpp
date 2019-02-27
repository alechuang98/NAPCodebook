double cross(Pt o, Pt a, Pt b) {
	return (a - o) ^ (b - o);
}
vector<Pt> convex_hull(vector<Pt> pt) {
	sort( ALL(pt) );
	int top = 0;
	vector<Pt> stk(2*SZ(pt));
	for (int i = 0; i < SZ(pt); i++) {
		while (top >= 2 && cross(stk[top-2], stk[top-1], pt[i])<= 0)
			top--;
		stk[top++] = pt[i];
	}
	for (int i = SZ(pt) - 2, t = top + 1; i >= 0; i--) {
		while (top >= t && cross(stk[top-2], stk[top-1], pt[i]) <= 0)
			top--;
		stk[top++] = pt[i];
	}
	stk.resize(top-1);
	return stk;
}
