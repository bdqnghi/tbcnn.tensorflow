#ifndef FUZZYSEARCH_HPP
#define FUZZYSEARCH_HPP

#include <algorithm>
#include <cstring>
#include <queue>

#include "searchstring.hpp"
#include "directories.hpp"
#include "searchresults.hpp"

/** Fuzzy search using a variant of Levenshtein-distance for determining closest match **/
class FuzzySearch {
private:
    static constexpr unsigned char MAX_STR_LEN = 255;

    //Computes levenshtein-distance between two strings recursivly using dynamic programming
    //Atleast <i>I</i> feel clever :)
    constexpr static float rec(const char* a, const char* b, const int len_a, const int len_b, float memo[][MAX_STR_LEN+1]) {
            return  memo[len_a][len_b] != 0 ? memo[len_a][len_b] :
                    len_a == 0 ? memo[len_a][len_b] = len_b :
                    len_b == 0 ? memo[len_a][len_b] = len_a :
                    memo[len_a][len_b] = std::min({
                        rec(a, b, len_a-1, len_b, memo) + 1.0f,
                        rec(a, b, len_a, len_b-1, memo) + 0.01f, //Low cost for shorthands
                        rec(a, b, len_a-1, len_b-1, memo) + (a[len_a-1] != tolower(b[len_b-1]) ? 1.0f : 0.0f)});
    }

    //This is the method that should be called. 
    constexpr static float levenshtein(const char* a, const char* b) {
        //strlen is O(n) so don't want to call it to much
        const size_t strlen_a = strlen(a), strlen_b = strlen(b);
        float memo[MAX_STR_LEN+1][MAX_STR_LEN+1] {{0}};

        //To long string or empty string are considered bad matches
        return std::max(strlen_a, strlen_b) > MAX_STR_LEN ? MAX_STR_LEN : rec(a, b, strlen_a, strlen_b, memo);
    }
public:

    FuzzySearch() = delete;

    //With a given searchString, look into the directories
    //and put best matches in searchResults
    static void search(
        const SearchString& searchString,
        const Directories& directories,
        SearchResults& searchResults) {

        searchResults.clear();

        //Don't perform any search on empty string;
        if(searchString.get().length() == 0) {
            return;
        }

        using T = ApplicationMatching;
        std::priority_queue<T, std::vector<T>, std::greater<T>> pq;

        //For all applications in loaded directories...
        for(const Directory& directory : directories) {
            for(const Application& application : directory) {

                //Calculate Levenshtein-distance between searchString and application
                const float distance = levenshtein(searchString.get().c_str(), application.getName().c_str());

                constexpr float RANK_THRESHHOLD = 5.0f;
                if(distance <= RANK_THRESHHOLD) {
                    pq.push({distance, &application});
                }
            }
        }

        //Only fill searchResults with maxMatches-amount of results (top 10 best matches)
        unsigned char maxMatches = 10;
        for(const ApplicationMatching& match = pq.top(); !pq.empty() && maxMatches--; pq.pop()) {
            searchResults.insert(match);
        }
    }
};

#endif //FUZZYSEARCH_HPP
