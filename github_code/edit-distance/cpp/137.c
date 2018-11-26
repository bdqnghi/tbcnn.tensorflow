#include "Translator/LevenshteinDistance.h"

size_t &minimum(size_t _a, size_t _b, size_t _c) {
    size_t &min = (_a < _b) ? _a : _b;
    return (min < _c) ? min : _c;
}

size_t LevenshteinDistance(string &_first, string &_second) {
    size_t fst_size = _first.size(),
           snd_size = _second.size();

    if(fst_size == 0)
        return snd_size;
    if(snd_size == 0)
        return fst_size;

    fst_size++;
    snd_size++;

    size_t  a[snd_size],
            b[snd_size],
            *v0 = a,
            *v1 = b,
            *tmp,
            cost,
            aux_size = fst_size - 1;

    for (size_t i = 0; i < snd_size; ++i) //Inicialización de v0
        v0[i] = i;

    for (size_t i = 1; i < fst_size; ++i) {
        v1[0] = i;
        for (size_t j = 1; j < snd_size; j++) {
            cost = (_first.at(i-1) == _second.at(j-1)) ? 0 : 1;
            v1[j] = minimum(  v1[j-1] + 1, v0[j] + 1, v0[j-1] + cost);
        }

        if(i != aux_size) {
            tmp = v0;
            v0 = v1;
            v1 = tmp;
        }
    }

    return v1[snd_size - 1];
}
