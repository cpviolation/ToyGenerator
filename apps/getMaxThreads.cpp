#include <omp.h>
#include <iostream>

int main()
{
  std::cout << omp_get_max_threads() << std::endl;

  return 0;
}