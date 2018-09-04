typedef double Type;
struct Point{
  Type x, y;
  Point(){};
  Point(Type _x, Type _y){
    x = _x, y = _y;
  }
  void read(){
    scanf("%lf %lf", &x, &y);
  }
  Point operator +(const Point & P2){
    return Point(x + P2.x, y + P2.y); 
  }
  Point operator -(const Point & P2){
    return Point(x - P2.x, y - P2.y); 
  }
  Point operator *(const Type & Len){
    return Point(x*Len, y*Len); 
  }
  Type operator *(const Point & P2){
    return x*P2.x + y*P2.y;
  }
  Type operator ^(const Point & P2){
    return x*P2.y - y*P2.x;
  }
  Type dis(){
    return x*x+y*y;
  }
};
struct Line{
  Point s, e;
  Line(){};
  Line(Point _s, Point _e){
    s = _s, e = _e;
  }
  void read(){ 
    s.read(); e.read(); 
  }
};

