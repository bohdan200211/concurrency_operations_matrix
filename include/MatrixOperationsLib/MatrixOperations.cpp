//
// Created by Bohdan on 2021-04-25.
//

#include <MatrixOperations.hpp>

//**************************************The OneThread implementation**************************************
void MatrixOperations::Addition (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal(14)");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = A(i, j) + B(i, j);
        }
    }
}

void MatrixOperations::Multiplication (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal(50)");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = 0;
            for (size_t k = 0; k < n ; ++k) {
                output(i, j) += A(i, k) * B(k, j);
            }
        }
    }
}


//**************************************The MultiThreads implementation**************************************
void MatrixOperations::MultiThreadsAddition (size_t AmountOfThreads, SquareMatrix & output,
                                             const SquareMatrix & A, const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal(49)");
    } else if (AmountOfThreads < 1){
        throw std::runtime_error("AmountOfThreads = 0(51)");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    size_t AmountOfRows           = output.GetDimension();
    size_t OptimalAmountOfThreads = std::min(AmountOfRows, AmountOfThreads);
    size_t ThreadInterval         = AmountOfRows / OptimalAmountOfThreads;
    size_t ThreadRemainder        = AmountOfRows % OptimalAmountOfThreads;

    size_t Intervals[OptimalAmountOfThreads];

    for (auto & x : Intervals) {
        x = ThreadInterval;
    }
    for (size_t i = 0; i < ThreadRemainder; ++i) {
        Intervals[i]++;
    }

    size_t i        = 0;
    size_t StartPos = 0;
    size_t EndPos   = StartPos;

    std::thread ArrOfThreads[OptimalAmountOfThreads];
    for (;i < OptimalAmountOfThreads - 1; ++i) {
        EndPos += Intervals[i];

        ArrOfThreads[i] = std::thread(OneThreadAddition, std::ref(output), std::cref(A), std::cref(B), StartPos, EndPos);

        StartPos = EndPos;
    }

    EndPos += Intervals[OptimalAmountOfThreads - 1];
    OneThreadAddition(output, A, B, StartPos, EndPos);


    for (auto & th : ArrOfThreads) {
        if (th.joinable()){
            th.join();
        }
    }
}

void MatrixOperations::MultiThreadsMultiplication (size_t AmountOfThreads, SquareMatrix & output,
                                                             const SquareMatrix & A, const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal(99)");
    } else if (AmountOfThreads < 1){
        throw std::runtime_error("AmountOfThreads = 0(100)");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    size_t AmountOfRows           = output.GetDimension();
    size_t OptimalAmountOfThreads = std::min(AmountOfRows, AmountOfThreads);
    size_t ThreadInterval         = AmountOfRows / OptimalAmountOfThreads;
    size_t ThreadRemainder        = AmountOfRows % OptimalAmountOfThreads;

    size_t Intervals[OptimalAmountOfThreads];

    for (auto & x : Intervals) {
        x = ThreadInterval;
    }
    for (size_t i = 0; i < ThreadRemainder; ++i) {
        Intervals[i]++;
    }

    size_t i        = 0;
    size_t StartPos = 0;
    size_t EndPos   = StartPos;

    std::thread ArrOfThreads[OptimalAmountOfThreads];
    for (;i < OptimalAmountOfThreads - 1; ++i) {
        EndPos += Intervals[i];

        ArrOfThreads[i] = std::thread(OneThreadMultiplication, std::ref(output), std::cref(A), std::cref(B), StartPos, EndPos);

        StartPos = EndPos;
    }

    EndPos += Intervals[OptimalAmountOfThreads - 1];
    OneThreadMultiplication(std::ref(output), std::cref(A), std::cref(B), StartPos, EndPos);


    for (auto & th : ArrOfThreads) {
        if (th.joinable()){
            th.join();
        }
    }
}

void MatrixOperations::OneThreadAddition(SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B,
                                         size_t StartRow, size_t EndRow) {

    const size_t n = output.GetDimension();


    for (size_t i = StartRow; i < EndRow; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = A(i, j) + B(i, j);
        }
    }
}

void MatrixOperations::OneThreadMultiplication(SquareMatrix &output, const SquareMatrix &A, const SquareMatrix &B,
                                           size_t StartRow, size_t EndRow) {

    const size_t n = output.GetDimension();

    for (size_t i = StartRow; i < EndRow; ++i) {
        for (size_t j = 0; j < n; ++j) {
            output(i, j) = 0;
            for (size_t k = 0; k < n ; ++k) {
                output(i, j) += A(i, k) * B(k, j);
            }
        }
    }
}

//**************************************Additional fucntions**************************************
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

bool MatrixOperations::CheckEquality(const SquareMatrix & A, const SquareMatrix & B) {
    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal(146)");
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

