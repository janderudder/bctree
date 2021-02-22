#pragma once
#include <iostream>
#include <string>
#include <type_traits>



constexpr auto _echo_lambda = [](std::string_view label, auto&& value)
{
    using value_type = decltype(value);

    if constexpr (std::is_convertible_v<std::decay_t<value_type>, std::string>)
    {
        std::cout
            << label << " : \""<<(std::forward<decltype(value)>(value))<<"\"";
    }
    else
    {
        std::cout
            << label << " : " << (std::forward<decltype(value)>(value));
    }
};



/**
 *  Print expression, then evaluate it and print result.
 */
#define ECHO(ECHO_MACRO_PARAM)                              \
    (_echo_lambda(#ECHO_MACRO_PARAM, ECHO_MACRO_PARAM))



/**
 *  Print expression, evaluate it and print result, then print a new line.
 */
#define ECHO_LN(ECHO_LN_MACRO_PARAM)                                \
    ([](std::string_view label, auto&& value) {                     \
        _echo_lambda(label, std::forward<decltype(value)>(value));  \
        std::cout << std::endl;                                     \
    })(#ECHO_LN_MACRO_PARAM, ECHO_LN_MACRO_PARAM)



/**
 *  Print a new line
 */
#define NL(Stream)                                      \
    ([](std::ostream& os = std::cout) {                 \
        os << "\n";                                     \
    }(Stream))
