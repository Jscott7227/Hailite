#include <Kokkos_Core.hpp>
#include <cstdio>

// Create a program that does matrix multiply between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions

bool checkDim(int col2d, int row1d)
{
  return (col2d == row1d) 
}


int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and add values
  int row2d, col2d, col1d
    do{
        std::cout << " Enter the number of rows for the 2d view: ";
	      std::cin >> row2d;
	      std::cout << std::endl << " Enter the number of columns for the 2d view: ";
	      std::cout << std::endl << " Enter the number of rows for the 1d view: ";
        std::cin >> numRowsVector;
        std::cout << std::endl;

    }while(checkDim(col2d, col1d))

    // Make View and add values
    Kokkos::View<int*> A("1D", col1d);
    
    for (int i = 0; i < col1d; i++) {
      std::cout << " Enter the value for the 1d view at " << i << " ";
	    std::cin >> A(i);
  }

    Kokkos::View<int**>B("2D", row2d, col2d)
    for (int i = 0; i < col2d; i++) {
      for (int i = 0; i < row2d; i++) {
        std::cout << " Enter the value for the 2d view at col " << i << " row " << j << " ";
	      std::cin >> B(i,j);
  }}

  kos::View<int*>C("Result", row2d)
  
  // Do a matrix multiply
  Kokkos::parallel_for("Loop i", row2d, KOKKOS_LAMBDA(const int i)  {
	  int total = 0;
    Kokkos::parallel_for("Loop j", row1d, KOKKOS_LAMBDA(const int j)  {
      dot_product += A(i,j) * B(j);
	    C(i) = dot_product;
    });
  });
  
  // Output Result
  for(int i = 0; i < col2d; i++) {

    for(int j = 0 ; j < row2d; j++){

      std::cout << " " << C(i,j);
    }
    
		std::cout << std::endl;
  } 
  }
  Kokkos::finalize();
}
