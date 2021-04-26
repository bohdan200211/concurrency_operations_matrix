//
// Created by Bohdan on 2021-04-25.
//


#include "Operations.hpp"

Number Operations::NaiveMultiplication(const Number & lhs, const Number & rhs) {
    auto carry = 0;

    Number result;

    result.Resize(lhs.m_Length + rhs.m_Length);

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

    result.Update();

    return result;
}


//The naive implementation
Number Operations::NaiveSquare(const Number & num) {
    return NaiveMultiplication(num, num);
}

Number Operations::NaivePow(const Number & base, const Number & exponent) {
    if (exponent == Number("0")) {
        return Number();
    }

    Number result("1");

    for (Number it = Number("0"); it < exponent; ++it) {
        result = std::move(NaiveMultiplication(result, base));
    }

    return result;
}


//The Fast implementation
Number Operations::FastSquare(const Number & num) {
    auto NumLength = num.m_Length;
    auto carry = 0;

    Number result;
    result.Resize(2 * NumLength);

    for (int i = 0; i < NumLength; ++i) {
        carry = 0;

        for (int j = i; j < NumLength; ++j) {
            auto & resultCell = result.m_Number[i + j];

            if (i == j) {
                resultCell += std::pow(num.m_Number[i], 2);
            } else {
                resultCell += 2 * num.m_Number[i] * num.m_Number[j];
            }

            resultCell += carry;
            carry       = resultCell / CellVal;
            resultCell %= CellVal;
        }

        result.m_Number[i + NumLength] = carry;
    }

    result.Update();

    return result;
}

Number Operations::FastPow(const Number & base, const Number & exponent) {
    std::vector<bool> binaryPowerRepresentation;
    Number result("1");
    Number Zero("0");
    Number Pow = exponent;

    while(Pow != Zero) {
        binaryPowerRepresentation.push_back(Pow.m_Number[0] % 2);
        Pow.NumberDivByTwo();
    }


    for(size_t i = binaryPowerRepresentation.size(); i > 0; i--) {
        result = std::move(FastSquare(result));
        if(binaryPowerRepresentation[i - 1] == 1) {
            result = std::move(NaiveMultiplication(result, base));
        }
    }

    result.Update();

    return result;
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


