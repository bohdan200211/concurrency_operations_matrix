//
// Created by Bohdan on 2021-04-25.
//


#include "Operations.hpp"

Number Operations::NaiveMultiplication(const Number &lhs, const Number &rhs) {
    auto carry = 0;

    Number result;

    result.Resize(lhs.m_Length + rhs.m_Length);
    result.m_Sign = lhs.m_Sign == rhs.m_Sign ? Number::Sign::Plus : Number::Sign::Minus;

    for (int i = 0; i < rhs.m_Length; ++i) {
        carry = 0;

        for (int j = 0; j < lhs.m_Length; ++j) {
            auto & resultCell = result.m_Number[i + j];

            resultCell += rhs.m_Number[i] * lhs.m_Number[j] + carry;
            carry       = resultCell / CellVal;
            resultCell %= CellVal;
        }

        result.m_Number[i + lhs.m_Length] = carry;
    }

    return result;
}


//The naive implementation
Number Operations::NaiveSquare(const Number &lhs, const Number &rhs) {
    return Number();
}

Number Operations::NaivePow(const Number &lhs, const Number &rhs) {
    return Number();
}


//The Fast implementation
Number Operations::FastSquare(const Number &lhs, const Number &rhs) {
    return Number();
}

Number Operations::FastPow(const Number &lhs, const Number &rhs) {
    return Number();
}


//The Concurrency implementation
template<size_t AmountOfThreads>
Number Operations::ConcurrencySquare(const Number &lhs, const Number &rhs) {
    return Number();
}

template<size_t AmountOfThreads>
Number Operations::ConcurrencyPow(const Number &lhs, const Number &rhs) {
    return Number();
}


