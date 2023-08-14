/*------------------------*/
/*                        */
/* Problem: Zombie Land 2 */
/* Role:    Generator     */
/* Author:  Darsein       */
/* Status:  Random        */
/*                        */
/*------------------------*/

#include "test_case_classes/test_case.hpp"
#include "test_case_classes/random_case_generator.hpp"

int main(){
  test_case::RandomCaseGenerator random_case_generator;
  random_case_generator.setParams(1, 0, 10);
  random_case_generator.generate();
  random_case_generator.setParams(1, 1, 20);
  random_case_generator.generate();
  random_case_generator.setParams(1, 2, 10);
  random_case_generator.generate();

  return 0;
}
