//
// Created by Bohdan on 2021-04-29.
//

//#include <string>
#include <cmath>

#include <MatrixOperations.hpp>

int main() try {
//    *******************************************ADD-TIME-TABLE********************************************
    const size_t MaxThreads      = 8;
    const size_t MinThreads      = 2;
    const size_t MaxPowByBaseTwo = 11;
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
        MatrixOperations::Multiplication(OneThreadResult, A, B);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        table[j][1] = std::to_string(dur.count());
        std::cout << "OneThreadResult,N"<<N<<"\n";

        for (size_t AmountOfThreads = MinThreads; AmountOfThreads <= MaxThreads; ++AmountOfThreads) {
            t1 = std::chrono::high_resolution_clock::now();
            MatrixOperations::MultiThreadsMultiplication(AmountOfThreads, MultiThreadResult, A, B);
            t2 = std::chrono::high_resolution_clock::now();
            dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            table[j][AmountOfThreads] = std::to_string(dur.count());
            std::cout << "MultiThreadResult,N:"<<N<<"\tAmountOfThreads:"<<AmountOfThreads<<"\n";
        }
    }

    std::cout << table.to_string() << std::endl;
//    *******************************************\ADD-TIME-TABLE********************************************

    return 0;
} catch (const std::exception & ex) {
    std:: cout << ex.what();
}
