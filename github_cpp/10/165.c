
#include "the/string.h"
#include "the/text/string_levenshtein_distance.h"
#include "the/invalid_operation_exception.h"


the::text::string_levenshtein_distance::string_levenshtein_distance(void) {
    throw the::invalid_operation_exception("string_levenshtein_distance::ctor",
        __FILE__, __LINE__);
}



the::text::string_levenshtein_distance::string_levenshtein_distance(
        const string_levenshtein_distance& src) {
    throw the::invalid_operation_exception("StringLevenshteinDistance::ctor",
        __FILE__, __LINE__);
}



the::text::string_levenshtein_distance::~string_levenshtein_distance(void) {
    throw the::invalid_operation_exception("string_levenshtein_distance::dtor",
        __FILE__, __LINE__);
}
