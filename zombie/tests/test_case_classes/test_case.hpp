/*-----------------------------*/
/*                             */
/* Problem: Zombie Land 2      */
/* Role:    Test Case Template */
/* Author:  Darsein            */
/*                             */
/*-----------------------------*/

#pragma once

#include "../constraints.h"
#include <fstream>
#include <vector>

namespace test_case {
  class TestCase {
  public:
    int N;
    int D;
    std::vector<int> X;
    std::vector<int> Y;
    std::vector<int> VX;
    std::vector<int> VY;
    std::string name;

    TestCase(int n = MAX_N)
      : N(n) {
      D = 0;
      X = std::vector<int>(N + 1);
      Y = std::vector<int>(N + 1);
      VX = std::vector<int>(N + 1);
      VY = std::vector<int>(N + 1);
      name = "";
    }

    void generate(void) {
      std::ofstream fout(name + ".in");
      fout << N << " " << D << std::endl;
      for (int i = 0; i <= N; ++i) {
	fout << X[i] << " " << Y[i] << " " << VX[i] << " " << VY[i] << std::endl;
      }
    }
  };
}

