Point inter(Line l1, Line l2){
  Type v1 = (l1.s - l1.e) ^ (l2.s - l1.e);
  Type v2 = (l1.s - l1.e) ^ (l1.e - l2.e);
  Type v3 = (v1 + v2);
  if(v3 + eps > 0 && v3 - eps < 0) return Point(nan(""), nan(""));
  return l2.s*(v2/v3) + l2.e*(v1/v3);
}
