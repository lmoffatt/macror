#include "plotter.h"

using namespace std;


int main(int argc, char* argv[])
{

  vector<double> v;
  vector<double> v2;
  vector<double> v3;
  vector<double> y;

  for (double i=0; i<10; i++) v.push_back(i*i);
  for (double i=0; i<10; i++) v2.push_back(i+5);
  for (double i=0; i<10; i++) v3.push_back(-i*i);
  for (double i=0; i<10; i++) y.push_back(i*i);

  Plotter p2;
  p2.addCurve(v, "^2", LINE_SOLID, "3", DOT_SQUARE, COLOR_ORANGE);
  p2.addCurve(v2, "+5", LINE_NONE, "1", DOT_CIRCLE, COLOR_PINK);
  p2.addCurve(v3, "-^2", LINE_SOLID, "1", DOT_NONE, COLOR_PURPLE);
  p2.defineSteps(y);
  p2.setXLimits(-10,150);
  p2.setYLimits(-100,100);
  p2.setXTicks(100,3);
  p2.setYTicks(50,0);

  p2.show(argc, argv);

  return 0;
}
