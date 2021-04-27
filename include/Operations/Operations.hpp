//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include <mutex>
#include <thread>

#include "../Number/Number.hpp"

class Operations {
public:
    //The naive implementation
    static Number NaiveMultiplication (const Number & lhs, const Number & rhs);

    static Number NaiveSquare (const Number & num);

    static Number NaivePow (const Number & base, const Number & exponent);


    //The Fast implementation
    static Number FastSquare (const Number & num);

    static Number FastPow (const Number & base, const Number & exponent);


    //The Concurrency implementation
    template<size_t AmountOfThreads>
    static Number ConcurrencyMultiplication (const Number & lhs, const Number & rhs);

    template<size_t AmountOfThreads>
    static Number ConcurrencySquare (const Number & lhs, const Number & rhs);

    template<size_t AmountOfThreads>
    static Number ConcurrencyPow (const Number & lhs, const Number & rhs);

    //... Concurrency helping methods
    static void OneThreadMultiplication(Number & result, const Number & lhs, const Number & rhs
                                       , size_t lhs_start_pos, size_t lhs_end_pos
                                       , size_t rhs_start_pos, size_t rhs_end_pos);
};

#include "Operations.inl"
