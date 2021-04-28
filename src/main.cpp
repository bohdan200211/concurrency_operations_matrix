#include <thread>
#include <string>

#include <MatrixOperations.hpp>

int main() {
    SquareMatrix result;

    SquareMatrix A({
                           {1, 2},
                           {3, 4}
                   });

    SquareMatrix B({
                           {5, 6},
                           {7, 8}
                   });



    MatrixOperations::Sum(result, A, B);




    //*******************************************TABLE********************************************
    MatrixOperations::PrintSquareMatrix(A);
    MatrixOperations::PrintSquareMatrix(B);
    MatrixOperations::PrintSquareMatrix(result);
    //*******************************************/TABLE********************************************
    return 0;
}
