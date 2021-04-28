//#include <string>
#include <cmath>

#include <MatrixOperations.hpp>

int main() try {
    SquareMatrix OneThreadResult;
    SquareMatrix MultiThreadResult;

    const size_t n               = 10000;
    const size_t AmountOfThreads = 2;

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

//    std::cout << "isEqual : " << MatrixOperations::CheckEquality(OneThreadResult, MultiThreadResult) << std::endl;
    std::cout << "Addition() time :\t\t\t" << dur1.count() << std::endl;
    std::cout << "MultiThreadsAddition<" << AmountOfThreads << ">() : " << dur2.count() << std::endl;

//    *******************************************TIME-TABLE********************************************

    /*const size_t MaxThreads      = 4;
    const size_t MinThreads      = 2;
    const size_t MaxPowByBaseTwo = 15;
    const size_t MinPowByBaseTwo = 5;

    fort::char_table table;

    table.set_border_style(FT_SOLID_ROUND_STYLE);

    table << fort::header;
    table << "N\\AmountOfThreads";

    for (size_t i = 1; i <= MaxThreads; ++i) {
        table[0][i] = std::to_string(i);
    }

    for (size_t i = MinPowByBaseTwo,j = 1; i <= MaxPowByBaseTwo; ++i, ++j) {
        table[j][0] = std::to_string(std::pow(2, i));
    }

    for (size_t i = MinPowByBaseTwo, N = std::pow(2, i), j = 1; i <= MaxPowByBaseTwo; ++i, N *= 2, ++j) {
        SquareMatrix A(N,
                       [](int x, int y) { return (x + y + 1); }
                       );

        SquareMatrix B(N,
                       [](int x, int y) { return (x + y + 1); }
                       );

        SquareMatrix MultiThreadResult;
        SquareMatrix OneThreadResult;

        OneThreadResult.Resize(N);
        MultiThreadResult.Resize(N);

        auto t1 = std::chrono::high_resolution_clock::now();
        MatrixOperations::Addition(OneThreadResult, A, B);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        table[j][1] = std::to_string(dur.count());
        std::cout << "OneThreadResult,N"<<N<<"\n";

        for (size_t AmountOfThreads = MinThreads; AmountOfThreads <= MaxThreads; ++AmountOfThreads) {
            t1 = std::chrono::high_resolution_clock::now();
            MatrixOperations::MultiThreadsAddition(AmountOfThreads, MultiThreadResult, A, B);
            t2 = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            table[j][AmountOfThreads] = std::to_string(dur.count());
            std::cout << "MultiThreadResult,N:"<<N<<"\tAmountOfThreads:"<<AmountOfThreads<<"\n";
        }
    }

    std::cout << table.to_string() << std::endl;*/
//    *******************************************TIME-TABLE********************************************

    return 0;
} catch (const std::exception & ex) {
    std:: cout << ex.what();
}
