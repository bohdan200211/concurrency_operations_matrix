#include <string>

#include <MatrixOperations.hpp>

int main() try {
    SquareMatrix OneThreadResult;
    SquareMatrix MultiThreadResult;

    const size_t n               = 1000;
    const size_t AmountOfThreads = 6;

    SquareMatrix A(n,
                   [](int x, int y) { return (x + y + 1); }
                   );

    SquareMatrix B(n,
                   [](int x, int y) { return (x + y + 1); }
                   );



    auto t1 = std::chrono::high_resolution_clock::now();
    MatrixOperations::Addition(OneThreadResult, A, B);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto dur1 = t2 - t1;

    t1 = std::chrono::high_resolution_clock::now();
    MatrixOperations::MultiThreadsAddition<AmountOfThreads>(MultiThreadResult, A, B);
    t2 = std::chrono::high_resolution_clock::now();

    auto dur2 = t2 - t1;



//    *******************************************TABLE********************************************
//    MatrixOperations::PrintSquareMatrix(A);
//    MatrixOperations::PrintSquareMatrix(B);
//    MatrixOperations::PrintSquareMatrix(OneThreadResult);
//    MatrixOperations::PrintSquareMatrix(MultiThreadResult);
//    *******************************************/TABLE********************************************

    std::cout << "isEqual : " << MatrixOperations::CheckEquality(OneThreadResult, MultiThreadResult) << std::endl;
    std::cout << "Addition() time :\t\t\t" << dur1.count() << std::endl;
    std::cout << "MultiThreadsAddition<" << AmountOfThreads << ">() : " << dur2.count() << std::endl;

    return 0;
} catch (const std::exception & ex) {
    std:: cout << ex.what();
}
