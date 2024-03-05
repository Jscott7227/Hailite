#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Declare a 5 ∗ 7 ∗ 12 ∗ n View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  
  // Set n to 30
  int n = 30; 
  // Make View
  Kokkos::View<int****> A("name", 5, 7, 12, n);
  
  // Print name
  std::cout << "The label of A is " << A.label() << std::endl;
  
  }
  Kokkos::finalize();
}
