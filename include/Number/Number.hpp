//
// Created by Bohdan on 2021-04-25.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>


const int CellVal = 10;

class Number {
public:
    enum class Sign : bool {Minus = false, Plus = true};
    using NumberContainer = std::vector<std::int8_t>;

    Number();

    explicit Number(const std::string & str);

    [[nodiscard]] std::string ToString () const;

    friend std::ostream & operator <<(std::ostream & ostream, const Number & number);

    friend class Operations;

private:
    void Resize(size_t size);

private:
    NumberContainer m_Number;
    size_t          m_Length;
    Sign            m_Sign;
};
