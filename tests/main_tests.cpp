//
// Created by Bohdan on 2021-04-25.
//

#include <doctest/doctest.h>
#include <MatrixOperations.hpp>
#include <cmath>

TEST_CASE("Test for addition") {
    SquareMatrix OneThreadResult;
    SquareMatrix MultiThreadResult;

    const size_t n               = 31;
    const size_t AmountOfThreads = 4;

    SquareMatrix A(n,
                   [](int x, int y) { return (x + y + 1); }
    );

    SquareMatrix B(n,
                   [](int x, int y) { return (x + y + 1); }
    );

    MatrixOperations::Addition(OneThreadResult, A, B);
    MatrixOperations::MultiThreadsAddition(AmountOfThreads, MultiThreadResult, A, B);

    CHECK(MatrixOperations::CheckEquality(OneThreadResult, MultiThreadResult));
}

TEST_CASE("Test for multiplication") {
    SquareMatrix OneThreadResult;
    SquareMatrix MultiThreadResult;

    const size_t n               = 31;
    const size_t AmountOfThreads = 4;

    SquareMatrix A(n,
                   [](int x, int y) { return (x + y + 1); }
    );

    SquareMatrix B(n,
                   [](int x, int y) { return (x + y + 1); }
    );

    MatrixOperations::Multiplication(OneThreadResult, A, B);
    MatrixOperations::MultiThreadsMultiplication(AmountOfThreads, MultiThreadResult, A, B);

    CHECK(MatrixOperations::CheckEquality(OneThreadResult, MultiThreadResult));
}
