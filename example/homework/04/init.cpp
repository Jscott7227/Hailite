#include <Kokkos_Core.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>

// Do simple parallel reduce to output the maximum element in a View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  
  // Seed rand 
  srand(time(NULL));

  // Make View and create values
  int n = 16;
  Kokkos::View<int*> A("A", n);
  
  //Asign view with random values in loop
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {

		A(i) = (rand() % (1000 - 0 + 1));
		//A(i) = 4*i;
    });
  int max;
  int lmax = 0; 
  // Do a parallel reduction
   Kokkos::parallel_reduce(A.extent(0), KOKKOS_LAMBDA (const int& i, int& lmax) {

        lmax = lmax > A(i) ? lmax : A(i);
    }, Kokkos::Max<int>(max));
  
  std::cout << "Max value: " << max << std::endl;
  }
  Kokkos::finalize();
}
