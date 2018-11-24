#include "common.hpp"
#include <benchmark/benchmark.h>

#include <salgo/hash-table.hpp>

#include <unordered_set>

using namespace benchmark;

using namespace salgo;





static void REHASH_std(State& state) {
	srand(69); clear_cache();

	const int size = state.range(0);

	for(auto _ : state) {
		state.PauseTiming();

		{
			std::unordered_multiset<int> s;
			s.rehash(size);
			for(int i=0; i<size; ++i) s.emplace( rand() );

			state.ResumeTiming();
			s.rehash( state.range(1) );
			state.PauseTiming();

			for(auto e : s) DoNotOptimize(e);
		}

		state.ResumeTiming();
	}
}
BENCHMARK( REHASH_std )->Args({1'056'323, 1'142'821})->Unit(benchmark::kMillisecond)->MinTime(0.1);





static void REHASH_salgo(State& state) {
	srand(69); clear_cache();
	
	const int size = state.range(0);

	for(auto _ : state) {
		state.PauseTiming();

		{
			salgo::Hash_Table<int> s;
			s.rehash(size);
			for(int i=0; i<size; ++i) s.emplace( rand() );

			// std::cout << "max_bucket_size: " << s.max_bucket_size() << std::endl;

			state.ResumeTiming();
			s.rehash( state.range(1) );
			state.PauseTiming();

			for(auto& e : s) DoNotOptimize(e());
		}

		state.ResumeTiming();
	}
}
BENCHMARK( REHASH_salgo )->Args({1'056'323, 1'142'821})->Unit(benchmark::kMillisecond)->MinTime(0.1);
















static void INSERT__std(State& state) {
	srand(69); clear_cache();

	std::unordered_multiset<int> s;

	for(auto _ : state) {
		s.emplace( rand() );
	}
}
BENCHMARK( INSERT__std )->MinTime(0.1);





static void INSERT__salgo(State& state) {
	srand(69); clear_cache();

	Hash_Table<int> s;

	for(auto _ : state) {
		s.emplace( rand() );
	}
}
BENCHMARK( INSERT__salgo )->MinTime(0.1);















static void RESERVED_INSERT__std(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	std::unordered_multiset<int> s;
	s.rehash( N + 10 );

	for(auto _ : state) {
		s.emplace( rand() );
	}
}
BENCHMARK( RESERVED_INSERT__std )->MinTime(0.1);





static void RESERVED_INSERT__salgo(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	Hash_Table<int> s;
	s.rehash( N + 10 );

	for(auto _ : state) {
		s.emplace( rand() );
	}
}
BENCHMARK( RESERVED_INSERT__salgo )->MinTime(0.1);










static void FIND__std(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	std::unordered_multiset<int> s;
	s.rehash( N + 10 );

	for(int i=0; i<N; ++i) {
		s.emplace( rand() % N );
	}

	for(auto _ : state) {
		auto iter = s.find( rand() % N );
		if(iter != s.end()) DoNotOptimize(*iter);
	}
}
BENCHMARK( FIND__std )->MinTime(0.1);





static void FIND__salgo(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	salgo::Hash_Table<int> s;
	s.rehash( N + 10 );

	for(int i=0; i<N; ++i) {
		s.emplace( rand() % N );
	}

	for(auto _ : state) {
		auto acc = s( rand() % N );
		if(acc.exists()) DoNotOptimize( acc() );
	}
}
BENCHMARK( FIND__salgo )->MinTime(0.1);










static void FIND_ERASE__std(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	std::unordered_multiset<int> s;
	s.rehash( N + 10 );

	for(int i=0; i<N; ++i) {
		s.emplace( rand() % N );
	}

	for(auto _ : state) {
		auto iter = s.find( rand() % N );
		if(iter != s.end()) s.erase( iter );
	}
}
BENCHMARK( FIND_ERASE__std )->MinTime(0.1);





static void FIND_ERASE__salgo(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	salgo::Hash_Table<int> s;
	s.rehash( N + 10 );

	for(int i=0; i<N; ++i) {
		s.emplace( rand() % N );
	}

	for(auto _ : state) {
		auto e = s( rand() % N );
		if(e.exists()) e.erase();
	}
}
BENCHMARK( FIND_ERASE__salgo )->MinTime(0.1);













static void ITERATE__std(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	std::unordered_multiset<int> s;
	s.rehash( N + 10 );

	for(int i=0; i<N; ++i) {
		s.emplace( rand() % N );
	}

	while( state.KeepRunningBatch(s.size()) ) {
		long long result = 0;
		for(auto e : s) result += e;
		DoNotOptimize(result);
	}
}
BENCHMARK( ITERATE__std )->MinTime(0.1);



static void ITERATE__salgo(State& state) {
	srand(69); clear_cache();

	const int N = state.iterations();

	salgo::Hash_Table<int> s;
	s.rehash( N + 10 );

	for(int i=0; i<N; ++i) {
		s.emplace( rand() % N );
	}

	while( state.KeepRunningBatch(s.count()) ) {
		long long result = 0;
		for(auto& e : s) result += e;
		DoNotOptimize(result);
	}
}
BENCHMARK( ITERATE__salgo )->MinTime(0.1);












BENCHMARK_MAIN();






