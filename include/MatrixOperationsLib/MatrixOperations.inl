//
// Created by Bohdan on 2021-04-25.
//



#include "MatrixOperations.hpp"

//**************************************The OneThread implementation**************************************
void MatrixOperations::Sum (SquareMatrix & output,
                            const SquareMatrix & A,
                            const SquareMatrix & B) {

    if (A.GetDimension() != B.GetDimension()) {
        throw std::runtime_error("A and B dimensions are not equal");
    }

    const int n = A.GetDimension();
    output.Resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output(i, j) = A(i, j) + B(i, j);
        }
    }
}

void MatrixOperations::Sub (SquareMatrix & output,
                            const SquareMatrix & A,
                            const SquareMatrix & B) {

}

void MatrixOperations::BruteForceMultiplication (SquareMatrix & output,
                                                 const SquareMatrix & A,
                                                 const SquareMatrix & B) {

}



//**************************************The MultiThreads implementation**************************************
template<size_t AmountOfThreads>
void
MatrixOperations::MultiThreadsSum (SquareMatrix & output,
                                   const SquareMatrix & A,
                                   const SquareMatrix & B) {

}

template<size_t AmountOfThreads>
void
MatrixOperations::MultiThreadsSub (SquareMatrix & output,
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
    table << fort::header;
    for (size_t i = 0; i < mtrx.GetDimension(); ++i) {
        for (size_t j = 0; j < mtrx.GetDimension(); ++j) {
            table[i][j] = std::to_string(mtrx(i, j));
        }
    }

    std::cout << table.to_string() << std::endl;
    //*******************************************/TABLE********************************************
}