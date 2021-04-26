//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include "../Number/Number.hpp"

class Operations {
public:
    static Number NaiveMultiplication (const Number & lhs, const Number & rhs);


    //The naive implementation
    static Number NaiveSquare (const Number & num);

    static Number NaivePow (const Number & base, const Number & exponent);


    //The Fast implementation
    static Number FastSquare (const Number & num);

    static Number FastPow (const Number & base, const Number & exponent);


    //The Concurrency implementation
    template<size_t AmountOfThreads>
    static Number ConcurrencySquare (const Number & lhs, const Number & rhs);

    template<size_t AmountOfThreads>
    static Number ConcurrencyPow (const Number & lhs, const Number & rhs);
};


