/*---------------------------*/
/*                           */
/* Problem: Zombie Land 2    */
/* Role:    Random Generator */
/* Author:  Darsein          */
/*                           */
/*---------------------------*/

#pragma once

#include "../xrand1.h"
#include "../constraints.h"
#include "case_generator_base.hpp"

#include <cassert>
#include <algorithm>
namespace test_case {
  class RandomCaseGenerator : public CaseGeneratorBase {
  protected:
    // Override
    std::string test_case_name() override {
      if (_constraints_type == 1) return "rand_small";
      if (_constraints_type == 2) return "rand_max";
      return "rand";
    }
    
    TestCase makeCase() override {
      TestCase test_case;

      if (_constraints_type == 2) {
	test_case.N = MAX_N;
      } else {
	test_case.N = rand.NextInt(MIN_N, MAX_N);
      }

      if (_constraints_type == 1) {
	test_case.D = rand.NextInt(0, 10);
      } else {
	test_case.D = rand.NextInt(MIN_D, MAX_D);
      }
      
      test_case.X.resize(test_case.N + 1);
      test_case.Y.resize(test_case.N + 1);
      test_case.VX.resize(test_case.N + 1);
      test_case.VY.resize(test_case.N + 1);
      for (int i = 0; i <= test_case.N; ++i) {
	if (_constraints_type == 1) {
	  test_case.X[i] = rand.NextInt(-100, 100);
	  test_case.Y[i] = rand.NextInt(-100, 100);
	  test_case.VX[i] = rand.NextInt(-100, 100);
	  test_case.VY[i] = rand.NextInt(-100, 100);
	} else {
	  test_case.X[i] = rand.NextInt(MIN_X, MAX_X);
	  test_case.Y[i] = rand.NextInt(MIN_Y, MAX_Y);
	  test_case.VX[i] = rand.NextInt(MIN_VX, MAX_VX);
	  test_case.VY[i] = rand.NextInt(MIN_VY, MAX_VY);
	}
      }

      return test_case;
    }
  };
} // namespace test_case

