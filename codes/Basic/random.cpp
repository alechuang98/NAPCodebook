#include <random>
mt19937 rng(0x5EED);
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ 
  return uniform_int_distribution<int>(lb, ub)(rng); 
}
