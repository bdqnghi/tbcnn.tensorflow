



#include "routine.h"
#include "util/debug.h"
#include <cassert>
#include <cstring>
#include <array>

static inline int
cmp(const unsigned char* a, const unsigned char* b)
{
	assert(a != 0);
	assert(b != 0);
	return strcmp(reinterpret_cast<const char*>(a),
	              reinterpret_cast<const char*>(b));
}

#include "losertree.h"

void mergesort_4way(unsigned char**, size_t, unsigned char**);

template <unsigned K>
static void
mergesort_losertree(unsigned char** strings, size_t n, unsigned char** tmp)
{
	if (n < 0x10000) {
		mergesort_4way(strings, n, tmp);
		return;
	}
	debug() << __func__ << "(), n="<<n<<"\n";
	const size_t split = size_t(double(n) / double(K));
	std::array<std::pair<unsigned char**, size_t>, K> ranges;
	for (unsigned i=0; i < K-1; ++i) {
		ranges[i] = std::make_pair(strings+i*split, split);
	}
	ranges[K-1] = std::make_pair(strings+(K-1)*split, n-(K-1)*split);
	for (unsigned i=0; i < K; ++i) {
		mergesort_losertree<K>(ranges[i].first, ranges[i].second,
				tmp+(ranges[i].first-strings));
	}
	unsigned char** result = tmp;
	loser_tree<unsigned char*> tree(ranges.begin(), ranges.end());
	while (tree._nonempty_streams) { *result++ = tree.min(); }
	(void) memcpy(strings, tmp, n*sizeof(unsigned char*));
}

void mergesort_losertree_64way(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree<64>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_128way(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree<128>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_256way(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree<256>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_512way(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree<512>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_1024way(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree<1024>(strings, n, tmp);
	free(tmp);
}

ROUTINE_REGISTER_SINGLECORE(mergesort_losertree_64way,
		"64way loser tree based mergesort")
ROUTINE_REGISTER_SINGLECORE(mergesort_losertree_128way,
		"128way loser tree based mergesort")
ROUTINE_REGISTER_SINGLECORE(mergesort_losertree_256way,
		"256way loser tree based mergesort")
ROUTINE_REGISTER_SINGLECORE(mergesort_losertree_512way,
		"512way loser tree based mergesort")
ROUTINE_REGISTER_SINGLECORE(mergesort_losertree_1024way,
		"1024way loser tree based mergesort")

void mergesort_4way_parallel(unsigned char**, size_t, unsigned char**);

template <unsigned K>
static void
mergesort_losertree_parallel(unsigned char** strings, size_t n, unsigned char** tmp)
{
	if (n < 0x10000) {
		mergesort_4way_parallel(strings, n, tmp);
		return;
	}
	debug() << __func__ << "(), n="<<n<<"\n";
	const size_t split = size_t(double(n) / double(K));
	std::array<std::pair<unsigned char**, size_t>, K> ranges;
	for (unsigned i=0; i < K-1; ++i) {
		ranges[i] = std::make_pair(strings+i*split, split);
	}
	ranges[K-1] = std::make_pair(strings+(K-1)*split, n-(K-1)*split);
#pragma omp parallel for
	for (unsigned i=0; i < K; ++i) {
		mergesort_losertree_parallel<K>(ranges[i].first, ranges[i].second,
				tmp+(ranges[i].first-strings));
	}
	unsigned char** result = tmp;
	loser_tree<unsigned char*> tree(ranges.begin(), ranges.end());
	while (tree._nonempty_streams) { *result++ = tree.min(); }
	(void) memcpy(strings, tmp, n*sizeof(unsigned char*));
}

void mergesort_losertree_64way_parallel(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree_parallel<64>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_128way_parallel(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree_parallel<128>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_256way_parallel(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree_parallel<256>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_512way_parallel(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree_parallel<512>(strings, n, tmp);
	free(tmp);
}
void mergesort_losertree_1024way_parallel(unsigned char** strings, size_t n)
{
	unsigned char** tmp = static_cast<unsigned char**>(
			malloc(n*sizeof(unsigned char*)));
	mergesort_losertree_parallel<1024>(strings, n, tmp);
	free(tmp);
}

ROUTINE_REGISTER_MULTICORE(mergesort_losertree_64way_parallel,
		"Parallel 64way loser tree based mergesort")
ROUTINE_REGISTER_MULTICORE(mergesort_losertree_128way_parallel,
		"Parallel 128way loser tree based mergesort")
ROUTINE_REGISTER_MULTICORE(mergesort_losertree_256way_parallel,
		"Parallel 256way loser tree based mergesort")
ROUTINE_REGISTER_MULTICORE(mergesort_losertree_512way_parallel,
		"Parallel 512way loser tree based mergesort")
ROUTINE_REGISTER_MULTICORE(mergesort_losertree_1024way_parallel,
		"Parallel 1024way loser tree based mergesort")
