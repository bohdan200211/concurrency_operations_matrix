//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <regex>
#include <stdexcept>


const int CellVal = 10;

class Number {
public:
    using NumberContainer = std::vector<std::int16_t>;

    Number() noexcept;
    explicit Number(const std::string & str);

    [[nodiscard]] std::string ToString () const noexcept;

    friend std::ostream & operator <<(std::ostream & ostream, const Number & number) noexcept;

    Number & operator--();
    Number & operator++() noexcept;

    bool operator <(const Number & number) const noexcept;
    bool operator >(const Number & number) const noexcept;

    bool operator ==(const Number & number) const noexcept;
    bool operator !=(const Number & number) const noexcept;

    bool operator <=(const Number & number) const noexcept;
    bool operator >=(const Number & number) const noexcept;


    friend class Operations;

private:
    enum class ComparisonSign : int {Less = -1, Equality = 0, Greater = 1};

    void Resize(size_t size) noexcept;
    void Update() noexcept;
    ComparisonSign ComparisonResult(const Number & number) const noexcept;

    //The FastLib's additional functions
    void NumberDivByTwo() noexcept;


private:
    NumberContainer m_Number;
    size_t          m_Length;
};
