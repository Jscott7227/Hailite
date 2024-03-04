#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>


int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {

  // Make View and create values
    int result;
    int n = 15;
    Kokkos::Timer timer;
    Kokkos::View<int*> pre("Pre", n);
    Kokkos::View<int*> post("Post", n);


    Kokkos::parallel_scan("Scan", n,
      KOKKOS_LAMBDA(int i, int& partial_sum, bool final) {
        if(final) pre(i) = partial_sum;
        partial_sum += i;
        if(final) post(i) = partial_sum;
    }, result);

    int time = timer.seconds();
    timer.reset();

    std::cout << "Pre Sum: ";
    for(int i = 0; i < n; i++) {
		  std::cout << pre(i) << ",";
	  }
    std::cout << std::endl << "Post Sum: ";
    for(int i = 0; i < n; i++) {
		  std::cout << post(i) << ",";
	  } 
	std::cout << std::endl << "Time to sum: " << timer.seconds() << " seconds" << std::endl;

  }
  Kokkos::finalize();
}
