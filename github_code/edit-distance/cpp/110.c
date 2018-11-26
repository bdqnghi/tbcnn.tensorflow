#include "levenshtein_distance.hpp"
#include <cstring>
#include <vector>
#include <numeric>
#include <algorithm>

namespace cryptopals {

unsigned int levenshtein_distance(const char * str1, const char * str2)
{
    // Wagner-Fischer algorithm, with the "two matrix rows" space optimization
    size_t str2_len = strlen(str2);
    std::vector<unsigned int> dist(str2_len + 1);
    std::iota(dist.begin(), dist.end(), 0u);

    size_t str1_len = strlen(str1);
    for (size_t i = 1; i <= str1_len; ++i) {
        auto prev_dist = dist;
        dist[0] = i;
        for (size_t j = 1; j <= str2_len; ++j)
            if (str1[i - 1] == str2[j - 1])
                dist[j] = prev_dist[j - 1];
            else
                dist[j] =
                    1 + std::min({dist[j - 1], prev_dist[j], prev_dist[j - 1]});
    }
    return dist.back();
}

}  // namespace cryptopals
