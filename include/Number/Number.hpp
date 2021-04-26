//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>


const int CellVal = 10;

class Number {
public:
    using NumberContainer = std::vector<std::int16_t>;

    Number();
    explicit Number(const std::string & str);

    [[nodiscard]] std::string ToString () const;

    friend std::ostream & operator <<(std::ostream & ostream, const Number & number);

    Number & operator--();
    Number & operator++();

    bool operator <(const Number & number) const;
    bool operator >(const Number & number) const;

    bool operator ==(const Number & number) const;
    bool operator !=(const Number & number) const;

    bool operator <=(const Number & number) const;
    bool operator >=(const Number & number) const;


    friend class Operations;

private:
    enum class ComparisonSign : int {Less = -1, Equality = 0, Greater = 1};

    void Resize(size_t size);
    void Update();
    ComparisonSign ComparisonResult(const Number & number) const;

    //The Fast additional functions
    void NumberDivByTwo();


private:
    NumberContainer m_Number;
    size_t          m_Length;
};
