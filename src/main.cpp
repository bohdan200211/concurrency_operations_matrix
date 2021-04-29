//#include <string>
#include <cmath>

#include <MatrixOperations.hpp>

int main() try {
    SquareMatrix OneThreadResult;
    SquareMatrix MultiThreadResult;

    const size_t n               = std::pow(2,13);
    const size_t AmountOfThreads = 8;

    SquareMatrix A(n,
                   [](int x, int y) { return (x + y + 1); }
                   );

    SquareMatrix B(n,
                   [](int x, int y) { return (x + y + 1); }
                   );



    auto t1 = std::chrono::high_resolution_clock::now();
    MatrixOperations::Addition(OneThreadResult, A, B);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    t1 = std::chrono::high_resolution_clock::now();
    MatrixOperations::MultiThreadsAddition(AmountOfThreads, MultiThreadResult, A, B);
    t2 = std::chrono::high_resolution_clock::now();
    auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);



//    *******************************************TABLE********************************************
//    MatrixOperations::PrintSquareMatrix(A);
//    MatrixOperations::PrintSquareMatrix(B);
//    MatrixOperations::PrintSquareMatrix(OneThreadResult);
//    MatrixOperations::PrintSquareMatrix(MultiThreadResult);
//    *******************************************\TABLE********************************************

    std::cout << "isEqual : " << MatrixOperations::CheckEquality(OneThreadResult, MultiThreadResult) << std::endl;
    std::cout << "MultiThreadsAddition<" << 1 << ">() : " << dur1.count() << std::endl;
    std::cout << "MultiThreadsAddition<" << AmountOfThreads     << ">() : " << dur2.count() << std::endl;

    return 0;
} catch (const std::exception & ex) {
    std:: cout << ex.what();
}
