typedef double type;
typedef pair<type, type> Pt;
typedef pair<Pt, Pt> Line;
typedef pair<Pt, type> Circle; 
#define X first
#define Y second
#define O first
#define R second
Pt operator+(const Pt &p1, const Pt &p2) {
	return { p1.X + p2.X, p1.Y + p2.Y };
}
Pt operator-(const Pt &p1, const Pt &p2) {
	return { p1.X - p2.X, p1.Y - p2.Y };
}
Pt operator*(const Pt &p1, const type &p2) {
	return { p1.X*p2, p1.Y*p2 };
}
Pt operator/(const Pt &p1, const type &p2) {
	return { p1.X/p2, p1.Y/p2 };
}
type operator*(const Pt &p1, const Pt &p2) {
	return p1.X*p2.X + p1.Y*p2.Y ;
}
type operator^(const Pt &p1, const Pt &p2) {
	return p1.X*p2.Y - p1.Y*p2.X ;
}
type norm2(const Pt &p1) {
	return p1*p1; 
}
double norm(const Pt &p1) {
	return sqrt(p1*p1);
}
Pt perp(const Pt &p1) {
	return { -p1.Y, p1.X };
}
