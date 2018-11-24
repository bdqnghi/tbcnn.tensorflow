#include "palindrome.hpp"

#include <cmath>

namespace rdp
{
    std::uint64_t
    largest_palindrome(std::uint8_t const factor_length)
    {
        auto const lower_bound = static_cast<std::uint64_t>(std::pow(10.0f, factor_length - 1));
        auto const upper_bound = static_cast<std::uint64_t>(std::pow(10.0f, factor_length)) - 1;
        auto diagonal_x = upper_bound;
        auto diagonal_y = upper_bound;

        while (diagonal_x >= lower_bound && diagonal_y >= lower_bound)
        {
            auto x = diagonal_x;
            auto y = diagonal_y;

            do
            {
                if (is_palindrome(x * y))
                {
                    return x * y;
                }

                ++x;
                --y;
            }
            while (x <= upper_bound && y >= lower_bound);

            if (diagonal_x == diagonal_y)
            {
                --diagonal_y;
            }
            else
            {
                --diagonal_x;
            }
        }

        return 0;
    }
}
