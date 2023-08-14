#include "testlib.h"
#include "constraints.h"

using namespace std;

int main() {
  registerValidation();

  int N = inf.readInt(MIN_N, MAX_N, "N");
  inf.readSpace();
  int D = inf.readInt(MIN_D, MAX_D, "D");
  inf.readEoln();
  for (int i = 0; i < N + 1; ++i) {
    int x = inf.readInt(MIN_X, MAX_X, "x");
    inf.readSpace();
    int y = inf.readInt(MIN_Y, MAX_Y, "y");
    inf.readSpace();
    int vx = inf.readInt(MIN_VX, MAX_VX, "vx");
    inf.readSpace();
    int vy = inf.readInt(MIN_VY, MAX_VY, "vy");
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}
