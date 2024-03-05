#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Create a program that does matrix multiply between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions

bool checkDim(int col2d, int row1d)
{
  //Checks if multiplication is valid
  return (col2d == row1d); 
}


int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Loop for valid dimensions
  int row2d, col2d, row1d;
    do{
        std::cout << " Enter the number of rows for the 2d view: ";
	      std::cin >> row2d;
	      std::cout << std::endl << " Enter the number of columns for the 2d view: ";
	      std::cin >> col2d;
	      std::cout << std::endl << " Enter the number of rows for the 1d view: ";
        std::cin >> row1d;
        std::cout << std::endl;

    }while(!checkDim(col2d, row1d));

    // 1D View
    Kokkos::View<int*> A("1D", row1d);
    
    for (int i = 0; i < row1d; i++) {
      std::cout << " Enter the value for the 1d view at " << i << " ";
	    std::cin >> A(i);
  }

    //2D view
    Kokkos::View<int**>B("2D", col2d, row2d);
    for (int i = 0; i < row2d; i++) {
      for (int j = 0; j < col2d; j++) {
        std::cout << " Enter the value for the 2d view at row " << i << " col " << j << " ";
	      std::cin >> B(i,j);
  }}

  //Result view
  Kokkos::View<int*>C("Result", row2d); 


  // Do a matrix multiply
  Kokkos::parallel_for("Loop i", col2d, KOKKOS_LAMBDA(const int i)  {
    Kokkos::parallel_for("Loop j", row1d, KOKKOS_LAMBDA(const int j)  {
      C(i) += B(i,j) * A(j);
    });
  });
  
  // Output Result
  for(int i = 0; i < col2d; i++) {
      std::cout << C(i) << std::endl;
    }
    
		std::cout << std::endl;
  } 
  Kokkos::finalize();
}
