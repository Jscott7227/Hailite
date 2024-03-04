#include <Kokkos_Core.hpp>
#include <cstdio>

// Declare a 5 ∗ 7 ∗ 12 ∗ n View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  n = 30 
  // Make View
  Kokkos::View<int****> A("name", 5, 7, 12, n);
  
  // print name
  std::cout << "The label of A is " << A.label() << std::endl;
  
  }
  Kokkos::finalize();
}
