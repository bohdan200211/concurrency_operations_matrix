//
// Created by Bohdan on 2021-04-25.
//

//The naive implementation
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
Number Operations::ConcurrencyMultiplication(const Number & lhs, const Number & rhs) {
    Number result;
    result.Resize(lhs.m_Length + rhs.m_Length);

    size_t OptimalAmountOfThreads = AmountOfThreads;

    if (AmountOfThreads < rhs.m_Length
        || AmountOfThreads < lhs.m_Length) {

        OptimalAmountOfThreads = std::min(rhs.m_Length, lhs.m_Length);
    }

    size_t lhs_working_interval = (lhs.m_Length % OptimalAmountOfThreads)
                                  ? lhs.m_Length / OptimalAmountOfThreads + 1
                                  : lhs.m_Length / OptimalAmountOfThreads;

    size_t rhs_working_interval = (rhs.m_Length % OptimalAmountOfThreads)
                                  ? rhs.m_Length / OptimalAmountOfThreads + 1
                                  : rhs.m_Length / OptimalAmountOfThreads;

    std::vector<std::thread> ArrOfThreads;

    for (size_t lhs_startPos = 0, rhs_startPos = 0, i = 0; i < OptimalAmountOfThreads; ++i) {
        size_t temp_lhs_endOfCurrInterval = (lhs_startPos + lhs_working_interval <= lhs.m_Length
                                            ? lhs_startPos + lhs_working_interval
                                            : lhs.m_Length % lhs_startPos);

        size_t temp_rhs_endOfCurrInterval = (rhs_startPos + rhs_working_interval <= rhs.m_Length
                                             ? rhs_startPos + rhs_working_interval
                                             : rhs.m_Length % rhs_startPos);


        std::thread th([&](){
            OneThreadMultiplication(result, lhs, rhs
                                   , lhs_startPos, temp_lhs_endOfCurrInterval
                                   , rhs_startPos, temp_rhs_endOfCurrInterval);
        });

        ArrOfThreads.push_back(std::move(th));

        lhs_startPos = temp_lhs_endOfCurrInterval;
        rhs_startPos = temp_rhs_endOfCurrInterval;
    }

    for (auto & th : ArrOfThreads) {
        th.join();
    }

    return result;
}

template<size_t AmountOfThreads>
Number Operations::ConcurrencySquare(const Number & lhs, const Number & rhs) {
    return Number();
}

template<size_t AmountOfThreads>
Number Operations::ConcurrencyPow(const Number & lhs, const Number & rhs) {
    return Number();
}

void Operations::OneThreadMultiplication(Number & result, const Number & lhs, const Number &rhs
                                        , size_t lhs_start_pos, size_t lhs_end_pos
                                        , size_t rhs_start_pos, size_t rhs_end_pos) {

    static std::mutex mtx;

    auto carry = 0;

    for (int i = rhs_start_pos; i <= rhs_end_pos; ++i) {
        carry = 0;

        for (int j = lhs_start_pos; j <= lhs_end_pos; ++j) {
            //lock_guard's scope
            {
                std::lock_guard<std::mutex> guard(mtx);

                auto &resultCell = result.m_Number[i + j];

                resultCell += rhs.m_Number[i] * lhs.m_Number[j] + carry;
                carry = resultCell / CellVal;
                resultCell %= CellVal;
            }
        }

        //lock_guard's scope
        {
            std::lock_guard<std::mutex> guard(mtx);
            result.m_Number[i + lhs.m_Length] = carry;
        }
    }
}

