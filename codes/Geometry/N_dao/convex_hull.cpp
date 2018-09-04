int ori(Point s, Point e, Point P){
  Type val = (s - e)^(P - e);
  if(fabs(val) < eps) return 0;
  else if(val > 0) return 1;
  else return -1;
}
vector<Point> convex_hull(vector<Point> pt){
  sort(pt.begin(), pt.end());
  int top=0;
  vector<Point> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && ori(stk[top-2],stk[top-1],pt[i]) >= 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && ori(stk[top-2],stk[top-1],pt[i]) >= 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}

