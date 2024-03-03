#include <Kokkos_Core.hpp>
#include <cstdio>
#include <cstdlib>

// Do simple parallel reduce to output the maximum element in a View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
  int n = 16;
  Kokkos::View<int*> A("A", n);
  
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {

		A(i) = (rand() % (1000 - 0 + 1))*i;
    });
  // Do a parallel reduction
   Kokkos::parallel_reduce(A.extent(0), KOKKOS_LAMBDA (const int& i, int& lmax) {

        lmax = lamx > i ? lmax : i;
    }, Kokkos::Min<int>(max));
  
  std::cout << "Max value: " << max << std::endl;
  }
  Kokkos::finalize();
}
