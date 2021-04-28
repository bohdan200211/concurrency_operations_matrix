//
// Created by Bohdan on 2021-04-25.
//


#include "MatrixOperations.hpp"

//**************************************The OneThread implementation**************************************
void MatrixOperations::Addition (SquareMatrix & output,
                                 const SquareMatrix & A,
                                 const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = A(i, j) + B(i, j);
        }
    }
}

void MatrixOperations::Subtraction (SquareMatrix & output,
                                    const SquareMatrix & A,
                                    const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = A(i, j) - B(i, j);
        }
    }
}

void MatrixOperations::BruteForceMultiplication (SquareMatrix & output,
                                                 const SquareMatrix & A,
                                                 const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n ; ++k) {
                output(i, j) += A(i, k) * B(k, j);
            }
        }
    }
}



//**************************************The MultiThreads implementation**************************************
template<size_t AmountOfThreads>
void MatrixOperations::MultiThreadsAddition (SquareMatrix & output,
                                            const SquareMatrix & A,
                                            const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    size_t AmountOfCells          = output.GetDimension() * output.GetDimension();
    size_t OptimalAmountOfThreads = std::min(AmountOfCells, AmountOfThreads);
    size_t TheadInterval          = (AmountOfCells % OptimalAmountOfThreads
                                    ? AmountOfCells / OptimalAmountOfThreads + 1
                                    : AmountOfCells / OptimalAmountOfThreads);


    std::thread ArrOfThreads[OptimalAmountOfThreads];
    for (size_t i = 0, StartOfCurrInterval = 0; i < OptimalAmountOfThreads; ++i) {
        size_t EndOfCurrInterval = StartOfCurrInterval
                                   + (StartOfCurrInterval + TheadInterval <= AmountOfCells
                                     ? TheadInterval
                                     : AmountOfCells % TheadInterval + 1);

        ArrOfThreads[i] = std::thread(OneThreadAddition,std::ref(output), A, B, StartOfCurrInterval, EndOfCurrInterval);

//        OneThreadAddition(output, A, B, StartOfCurrInterval, EndOfCurrInterval);

        StartOfCurrInterval = EndOfCurrInterval;
    }


    for (auto & th : ArrOfThreads) {
            th.join();
    }
}

template<size_t AmountOfThreads>
void MatrixOperations::MultiThreadsSubtraction (SquareMatrix & output,
                                                const SquareMatrix & A,
                                                const SquareMatrix & B) {

}

template<size_t AmountOfThreads>
void MatrixOperations::MultiThreadsBruteForceMultiplication (SquareMatrix & output,
                                                             const SquareMatrix & A,
                                                             const SquareMatrix & B) {

}

void MatrixOperations::PrintSquareMatrix (const SquareMatrix & mtrx) {
    //*******************************************TABLE********************************************
    fort::char_table table;

    table.set_border_style(FT_SOLID_ROUND_STYLE);

    for (size_t i = 0; i < mtrx.GetDimension(); ++i) {
        table << fort::header;
        for (size_t j = 0; j < mtrx.GetDimension(); ++j) {
            table[i][j] = std::to_string(mtrx(i, j));
        }
    }

    std::cout << table.to_string() << std::endl;
    //*******************************************/TABLE********************************************
}

bool MatrixOperations::CheckEquality(const SquareMatrix & A,
                                     const SquareMatrix & B) {
    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal");
    }

    for (size_t i = 0; i < A.GetDimension(); ++i) {
        for (size_t j = 0; j < A.GetDimension(); ++j) {
            if (A(i, j) != B(i, j)) {
                std::cout << "\n\nqweqwe " << i << ":" << j << "\n\n";
                return false;
            }
        }
    }
    return true;
}

void MatrixOperations::OneThreadAddition(SquareMatrix & output,
                                        const SquareMatrix & A,
                                        const SquareMatrix & B,
                                        size_t StartPos, size_t EndPos) {


    const size_t n = output.GetDimension();


    size_t UpperRow         = StartPos / n;
    size_t EndRow           = EndPos / n;
    size_t UpperRightColumn = (UpperRow == EndRow
                              ? EndPos % n
                              : n);
    size_t EndRightColumn   = EndPos % n;

    for (size_t j = StartPos % n; j < UpperRightColumn; ++j) {
        output(UpperRow, j) = A.f(UpperRow, j) + B.f(UpperRow, j);
    }

    for (size_t i = UpperRow + 1; i < EndRow; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = A.f(i, j) + B.f(i, j);
        }
    }

    if (EndRow == n)
        return;

    for (size_t j = 0; j < EndRightColumn; ++j) {
        output(EndRow, j) = A.f(EndRow, j) + B.f(EndRow, j);
    }
}


