//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include "../Number/Number.hpp"

class Operations {
public:
    static Number NaiveMultiplication (const Number & lhs, const Number & rhs);


    //The naive implementation
    static Number NaiveSquare (const Number & lhs, const Number & rhs);

    static Number NaivePow (const Number & lhs, const Number & rhs);


    //The Fast implementation
    static Number FastSquare (const Number & lhs, const Number & rhs);

    static Number FastPow (const Number & lhs, const Number & rhs);


    //The Concurrency implementation
    template<size_t AmountOfThreads>
    static Number ConcurrencySquare (const Number & lhs, const Number & rhs);

    template<size_t AmountOfThreads>
    static Number ConcurrencyPow (const Number & lhs, const Number & rhs);
};


