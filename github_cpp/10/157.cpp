


#include <qflags/qflags.h>

#include <climits>
#include <algorithm>
#include <cctype>



size_t levenshtein(char const* a, char const* b, bool ignore_case, bool print_matrix)
{
    size_t len_a = strlen(a); 
    size_t len_b = strlen(b); 

    
    std::vector<size_t> adjacency((len_a + 1) * (len_b + 1), 0);
    
    auto idx = [&](size_t x, size_t y) -> size_t& {
        return adjacency[(len_a + 1) * y + x];
    };

    
    
    for (size_t ii = 1; ii <= len_a; ++ii) {
        idx(ii, 0) = ii;
    }

    
    
    for (size_t jj = 1; jj <= len_b; ++jj) {
        idx(0, jj) = jj;
    }

    for (size_t ii = 0; ii < len_a; ++ii) {
        for (size_t jj = 0; jj < len_b; ++jj) {
            
            int ch_a = ignore_case ? std::toupper(a[ii]) : a[ii];
            int ch_b = ignore_case ? std::toupper(b[jj]) : b[jj];

            
            
            if (ch_a == ch_b) {
                idx(ii + 1, jj + 1) = idx(ii, jj);
            }
            
            
            else {
                size_t deletion_cost = idx(ii, jj + 1) + 1;
                size_t insertion_cost = idx(ii + 1, jj) + 1;
                size_t substitution_cost = idx(ii, jj) + 1;

                idx(ii + 1, jj + 1) = std::min({deletion_cost,
                                                insertion_cost,
                                                substitution_cost});
            }
        }
    }

    
    if (print_matrix) {
        fprintf(stdout, "      ");
        for (size_t jj = 0; jj < len_b; ++jj) {
            fprintf(stdout, " %1.1s ", b + jj);
        }
        fprintf(stdout, "\n");
        for (size_t ii = 0; ii <= len_a; ++ii) {
            fprintf(stdout, " %1.1s ", ii ? a + ii - 1 : "");
            for (size_t jj = 0; jj <= len_b; ++jj) {
                fprintf(stdout, "%2llu ", (unsigned long long)idx(ii, jj));
            }
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "\n");
    }

    
    return idx(len_a, len_b);
}



void find_nearest(int argc, char const* const* argv, bool ignore_case, bool print_matrix)
{
    std::tuple<size_t, int, int> nearest = std::make_tuple(SIZE_MAX,
                                                           INT_MAX,
                                                           INT_MAX);

    for (int ii = 1; ii < argc; ++ii) {
        for (int jj = 0; jj < ii; ++jj) {
            size_t distance = levenshtein(argv[ii],
                                          argv[jj],
                                          ignore_case,
                                          print_matrix);

            if (distance < std::get<0>(nearest)) {
                nearest = std::make_tuple(distance, ii, jj);
            }
        }
    }

    fprintf(stdout,
            "%llu %s %s\n",
            (unsigned long long)std::get<0>(nearest),
            argv[std::get<1>(nearest)],
            argv[std::get<2>(nearest)]);
}



int main(int argc, char* argv[])
{
    auto command_line = qflags::command_line(argc, argv);
    auto parser = qflags::parser();

    auto ignore_case = qflags::flag("ignore_case", "i");
    auto print_matrix = qflags::flag("print_matrix", "p");

    std::string errors;
    bool result = true;

    result &= parser.add_argument(&ignore_case);
    result &= parser.add_argument(&print_matrix);
    result &= parser.parse(command_line, &errors);

    fprintf(stdout, "%s", errors.c_str());

    
    if (parser.remaining_argc() == 3) {
        unsigned long long distance = levenshtein(parser.remaining_argv()[1],
                                                  parser.remaining_argv()[2],
                                                  ignore_case,
                                                  print_matrix);
        fprintf(stdout, "%llu\n", distance);
    }
    
    else if (parser.remaining_argc() > 3) {
        find_nearest(parser.remaining_argc() - 1,
                     parser.remaining_argv() + 1,
                     ignore_case,
                     print_matrix);
    }
    
    else {
        fprintf(stdout,
                "usage: levenshtein %s <string> <string> [<string>...]\n",
                parser.usage_string().c_str());
    }

    return result ? 0 : 1;
}
