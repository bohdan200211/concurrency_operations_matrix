//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

#include <fort.hpp>


class SquareMatrix {
private:
    using IntegerType = int;
    using row                 = std::vector<IntegerType>;
    using mtrx_representation = std::vector<row>;

    mtrx_representation m_Matrix;
    size_t              m_Dimension;


public:
    SquareMatrix()
        : m_Matrix()
        , m_Dimension(0) {}

    explicit SquareMatrix(const mtrx_representation & mtrx)
        : m_Matrix(mtrx)
        , m_Dimension(mtrx.size()) {

        if (!mtrx.empty()) {
            for (size_t i = 0; i < m_Dimension; ++i) {
                if (m_Dimension != mtrx[i].size()) {
                    throw std::runtime_error("This is not a square matrix(37)");
                }
            }
        }
    }

    explicit SquareMatrix(const size_t dimension, IntegerType (*SomeFunction)(IntegerType, IntegerType))
        : m_Dimension(0) {

        Resize(dimension);

        for (size_t i = 0; i < m_Dimension; ++i) {
            for (size_t j = 0; j < m_Dimension; ++j) {
                m_Matrix[i][j] = SomeFunction(i, j);
            }
        }
    }


          IntegerType & operator()(IntegerType idx, IntegerType idy)       { return m_Matrix[idx][idy]; }
    const IntegerType & operator()(IntegerType idx, IntegerType idy) const { return m_Matrix[idx][idy]; }

    IntegerType f(IntegerType idx, IntegerType idy) const { return m_Matrix[idx][idy]; }



    [[nodiscard]] row::const_iterator begin(size_t id_row) const noexcept { return m_Matrix[id_row].begin(); }
    [[nodiscard]] row::const_iterator end(size_t id_row) const noexcept { return m_Matrix[id_row].begin(); }

    //work only with std::vector
    void Resize(size_t n) {
        if (m_Dimension != n) {
            m_Matrix.resize(n, std::vector<IntegerType>(n, 0));
            m_Dimension = n;
        }
    }

    [[nodiscard]] size_t GetDimension () const { return m_Dimension; }
};


class MatrixOperations {
public:
    //The OneThread implementation
    static void Addition (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B);

    static void BruteForceMultiplication (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B);

    //The MultiThreads implementation
    static void MultiThreadsAddition (size_t AmountOfThreads, SquareMatrix & output,
                                      const SquareMatrix & A, const SquareMatrix & B);

    static void MultiThreadsBruteForceMultiplication (size_t AmountOfThreads, SquareMatrix & output,
                                                      const SquareMatrix & A, const SquareMatrix & B);


    static void PrintSquareMatrix (const SquareMatrix & mtrx);

    static bool CheckEquality (const SquareMatrix & A, const SquareMatrix & B);

private:
    static void OneThreadAddition (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B,
                                   size_t StartRow, size_t EndRow);

    static void MultiThreadAddition (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B,
                                   size_t StartRow, size_t EndRow);
};

