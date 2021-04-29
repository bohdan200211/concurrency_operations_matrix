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

    /// <summary>
/// Constructor. It construct the matrix of dimension=("dimension" * "dimension")
/// and set the value of each cell(i, j) = SomeFunction(i, j)
/// </summary>
/// <param name="dimension">Obviously...</param>
/// <param name="IntegerType (*SomeFunction)(IntegerType, IntegerType)">The initial value of parameter(array.size)</param>
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
    /// <summary>
    /// Simple implementation of an algorithm for matrix addition. output = A + B
    /// </summary>
    static void Addition (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B);

    /// <summary>
    /// Similar to Addition()
    /// </summary>
    static void Multiplication (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B);

    //The MultiThreads implementation
    /// <summary>
    /// Function divides rows between threads evenly and run OneThreadAddition() for each of them
    /// </summary>
    static void MultiThreadsAddition (size_t AmountOfThreads, SquareMatrix & output,
                                      const SquareMatrix & A, const SquareMatrix & B);

    /// <summary>
    /// Similar to MultiThreadsAddition()
    /// </summary>
    static void MultiThreadsMultiplication (size_t AmountOfThreads, SquareMatrix & output,
                                                      const SquareMatrix & A, const SquareMatrix & B);


    static void PrintSquareMatrix (const SquareMatrix & mtrx);

    static bool CheckEquality (const SquareMatrix & A, const SquareMatrix & B);

private:
    /// <summary>
    /// Function executes Addition() on the interval of rows. [StartRow, EndRow)
    /// </summary>
    static void OneThreadAddition (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B,
                                   size_t StartRow, size_t EndRow);

    /// <summary>
    /// Similar to OneThreadAddition()
    /// </summary>
    static void OneThreadMultiplication (SquareMatrix & output, const SquareMatrix & A, const SquareMatrix & B,
                                   size_t StartRow, size_t EndRow);
};

