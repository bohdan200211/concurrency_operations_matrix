//
// Created by Bohdan on 2021-04-25.
//

#include <regex>

#include "Number.hpp"

Number::Number()
    : m_Number({})
    , m_Length(0)
    , m_Sign(Sign::Plus) {}

Number::Number(const std::string & str)
    : m_Length(str.length()) {


    if (std::regex_match(str, std::regex("([+-]?)[1-9]([0-9]*)"))) {
        size_t it_str = 1;

        if (str[0] == '+') {
            m_Sign = Sign::Plus;
        } else if (str[0] == '-'){
            m_Sign = Sign::Minus;
        } else {
            m_Sign = Sign::Plus;
            it_str--;
        }

        m_Number.resize(m_Length - it_str);

        for (size_t num_it = m_Length - 1; num_it > -1; it_str++, num_it--) {
            m_Number[num_it] = str[it_str] - '0';
        }

    } else {
        //exception
        std::cerr << "Could not create instance of number: " << str << std::endl;
    }
}

void Number::Resize(size_t size) {
    m_Number.resize(size, 0);
}

std::string Number::ToString() const {
    std::string result(m_Length, ' ');

    for (size_t str_it = 0, num_it = m_Length - 1; str_it < m_Length; str_it++, num_it--) {
        result[str_it] = char(m_Number[num_it] + '0');
    }

    return result;
}

std::ostream & operator <<(std::ostream & ostream, const Number & number) {
    return ostream << number.ToString();
}

