/*---------------------------------*/
/*                                 */
/* Problem: Zombie Land 2          */
/* Role:    Generator Base Class   */
/* Author:  Darsein                */
/*                                 */
/*---------------------------------*/

#pragma once

#include "../xrand1.h"
#include "test_case.hpp"
#include <map>

namespace test_case {
  std::map<int, std::string> case_name;

  class CaseGeneratorBase {
  protected:
    // TODO: introduce another class for case_type and constraints_type
    int _case_prefix;
    int _case_type;
    int _constraints_type;
    int _case_num;
    XRand rand;

    // Override the two methods for each test case generator
    // TODO: brush up the way of injection
    virtual std::string test_case_name() = 0;

    virtual TestCase makeCase() = 0;

    std::string getCaseName(const int id) {
      char name_char[100]; // TODO
      sprintf(name_char, "%d_%s_%02d",
	      _case_prefix, test_case_name().c_str(), id);
      return std::string(name_char);
    }
    
  public:
    CaseGeneratorBase(int case_type = 1, int constraints_type = 0, int case_num = 1):
      _case_type(case_type),
      _constraints_type(constraints_type),
      _case_num(case_num) {
      rand = XRand(1111);
    }

    void setParams(int case_prefix, int constraints_type = 0, int case_num = 1) {
      _case_prefix = case_prefix;
      _constraints_type = constraints_type;
      _case_num = case_num;
      rand = XRand(_case_prefix);
    }

    void generate(void) {
      for (int id = 0; id < _case_num; ++id) {
	TestCase test_case = makeCase();
	test_case.name = getCaseName(id);
	test_case.generate();
      }
    }
  };
  
} // namespace test_case

