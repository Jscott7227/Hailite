#include <Kokkos_Core.hpp>
#include <cstdio>

// Problem: Make an n ∗ m View where each index equals 1000 ∗ i ∗ j

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // set n and m, you can change these values
  int n,m = 16;
  Kokkos::View<int*> A("A", n, m);
  
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {
		Kokkos::parallel_for("Loop2", A.extent(1), KOKKOS_LAMBDA (const int j) {
		  
		  A(i, j) = 1000*i*j;
    });
	  });
  }
  Kokkos::finalize();
}
