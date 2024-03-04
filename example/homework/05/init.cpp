#include <Kokkos_Core.hpp>
#include <cstdio>
#include <cstdlib>

// Create a program that compares a parallel for loop and a standard for loop for summing rows of a View with Kokkos Timer.

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
  int n = 16;
  Kokkos::View<int*> A("A", n);
  
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {

		A(i) = (rand() % (1000 - 0 + 1))*i;
    });
  
  //Create Timer time starts here
  Kokkos::Timer timer;

  int parallel_sum = 0;

  // Parallel Sum  
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {

		parallel_sum += A(i);
    });
  
  double parallel_time = timer.seconds;
  //Reset Timer 
  timer.reset();

  //Serial Sum
  for (int i = 0; i < n; i++) {
    serial_sum += A(i);
  }

  double serial_time = timer.seconds;
  timer.reset();
  // Output times
  std::cout << "Parallel time: " << parallel_time << std::endl;
  std::cout << "Serial time " << serial_time << std::endl;

  }
  Kokkos::finalize();
}
