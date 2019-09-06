bool Inter(Pt p1, Pt p2, Circ cc) {
    D d1 = norm(cc.O - p1);
    D d2 = norm(cc.O - p2);
    if (min(d1, d2) <= cc.R - eps) return true;
    if ( ((cc.O - p1) * (p2 - p1)) < 0 ) return false;
    if ( ((cc.O - p2) * (p1 - p2)) < 0 ) return false;
    Pt d3 = cc.O - p1;
    Pt d4 = (p2 - p1) / norm(p2 - p1) ;
    return fabs(d3 ^ d4) < cc.R;
}