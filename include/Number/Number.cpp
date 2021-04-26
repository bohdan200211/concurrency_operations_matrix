//
// Created by Bohdan on 2021-04-25.
//

#include "Number.hpp"

Number::Number() noexcept
    : m_Length(1)
    , m_Number({0}) {}

Number::Number(const std::string & str)
    : m_Length(str.length()) {

    m_Number.resize(m_Length);

    if (std::regex_match(str, std::regex("[1-9]([0-9]*)"))) {
        size_t it_str = 0;

        for (size_t num_it = m_Length; num_it > 0; it_str++, num_it--) {
            m_Number[num_it - 1] = str[it_str] - '0';
        }
    } else if (str == "0") {
        m_Number[0] = 0;
    } else {
        throw std::runtime_error("Could not create instance of number");
    }
}

void Number::Resize(size_t size) noexcept {
    m_Number.resize(size, 0);
    m_Length = size;
}

std::string Number::ToString() const noexcept {
    std::string result(m_Length, '.');

    for (size_t str_it = 0, num_it = m_Length - 1; str_it < m_Length; str_it++, num_it--) {
        result[str_it] = char(m_Number[num_it] + '0');
    }

    return result;
}

std::ostream & operator <<(std::ostream & ostream, const Number & number) noexcept {
    return ostream << number.ToString();
}

Number &Number::operator--() {
    if (m_Length == 1 && m_Number[0] == 0) {
        throw std::runtime_error("The Number field work only in the field of natural numbers");
    }

    int8_t carry = 1;
    size_t it;

    for (it = 0; it < m_Length; ++it) {
        auto & CellResult = m_Number[it];

        if (CellResult == 0) {
            CellResult = CellVal - carry;
        } else {
            ++it;
            break;
        }
    }


    m_Number[it - 1] -= carry;
    Update();

    return *this;
}

Number &Number::operator++() noexcept {
    int8_t carry = 1;

    for (size_t it = 0; it < m_Length && carry; ++it) {
        auto & CellResult = m_Number[it];

        CellResult += carry;
        carry       = CellResult / CellVal;
        CellResult %= CellVal;
    }

    if (carry) {
        m_Number.push_back(carry);
        m_Length++;
    }

    return *this;
}

void Number::Update() noexcept {
    size_t ActualLength = m_Number.size();
    while (ActualLength > 1 && m_Number[ActualLength - 1] == 0) {
        --ActualLength;
    }

    Resize(ActualLength);
}

bool Number::operator<(const Number & number) const noexcept {
    return ComparisonResult(number) == Number::ComparisonSign::Less;
}

bool Number::operator>(const Number & number) const noexcept {
    return ComparisonResult(number) == Number::ComparisonSign::Greater;
}

bool Number::operator==(const Number & number) const noexcept {
    return ComparisonResult(number) == Number::ComparisonSign::Equality;
}

bool Number::operator!=(const Number & number) const noexcept {
    return ComparisonResult(number) != Number::ComparisonSign::Equality;
}

bool Number::operator<=(const Number & number) const noexcept {
    return ComparisonResult(number) != Number::ComparisonSign::Greater;
}

bool Number::operator>=(const Number & number) const noexcept {
    return ComparisonResult(number) != Number::ComparisonSign::Less;
}

Number::ComparisonSign Number::ComparisonResult(const Number & number) const noexcept {
    if (m_Length == number.m_Length) {
        for (size_t i = m_Length; i > 0; i--) {
            if (m_Number[i - 1] < number.m_Number[i - 1]) {
                return Number::ComparisonSign::Less;
            } else if (m_Number[i - 1] > number.m_Number[i - 1]) {
                return Number::ComparisonSign::Greater;
            }
        }
        return Number::ComparisonSign::Equality;
    } else if (m_Length < number.m_Length) {
        return Number::ComparisonSign::Less;
    } else {
        return Number::ComparisonSign::Greater;
    }
}

void Number::NumberDivByTwo() noexcept {
    m_Number[0] /= 2;
    for (size_t i = 1; i < m_Length; i++) {
        bool isNotDivByTwo = m_Number[i] % 2;
        m_Number[i] /= 2;

        if (isNotDivByTwo) {
            m_Number[i - 1] += CellVal / 2;
        }
    }
    Update();
}









