#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

// Create a program that does matrix addition between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions
bool checkDim(int col2d, int col1d)
{
  //Checks if addition is valid
  return (col2d == col1d); 
}

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    //Loop to assign proper dimensions
    int row2d, col2d, col1d, temp;
    do{
        std::cout << " Enter the number of rows for the 2d view: ";
	std::cin >> row2d;
	std::cout << std::endl << " Enter the number of columns for the 2d view: ";
	std::cin >> col2d;
	std::cout << std::endl << " Enter the number of colums for the 1d view: ";
        std::cin >> col1d;
        std::cout << std::endl;

    }while(!checkDim(col2d, col1d));

    // 1D view
    Kokkos::View<int*> A("1D", col1d);
    
    for (int i = 0; i < col1d; i++) {
      std::cout << " Enter the value for the 1d view at " << i << " ";
      	
	std::cin >> A[i];
  }
    //2D view
    Kokkos::View<int**>B("2D", col2d, row2d);
    for (int i = 0; i < col2d; i++) {
      for (int j = 0; j < row2d; j++) {
        std::cout << " Enter the value for the 2d view at row " << i << " col " << j << " ";
      std::cin >> B(i,j);
  }}

    //View to hold sum
    Kokkos::View<int**>C("Sum", col2d, row2d);


  
  // Do a matrix add
  Kokkos::parallel_for("Loop1", B.extent(0), KOKKOS_LAMBDA (const int i) {
	Kokkos::parallel_for("Loop2", B.extent(1), KOKKOS_LAMBDA (const int j) {
		  
		C(i, j) = B(i,j) + A(j);
    
	});
	});

  // Output addition 
  for(int i = 0; i < col2d; i++) {

    for(int j = 0 ; j < row2d; j++){

      std::cout << " " << C(i,j);
    }

		std::cout << std::endl;
  
   }
  }
  Kokkos::finalize();
  }
