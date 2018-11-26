#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <random>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T1, typename T2 >
void BM_matrix_multiplication(benchmark::State& state){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T1 > dis1(
		std::numeric_limits< T1 >::min(),
		std::numeric_limits< T1 >::max()
	);
	std::uniform_int_distribution< T2 > dis2(
		std::numeric_limits< T2 >::min(),
		std::numeric_limits< T2 >::max()
	);

	auto m1 = make_matrix_fn(100_CD, 50_RD, [&dis1, &gen](auto, auto){
		return dis1(gen);
	});

	auto m2 = make_matrix_fn(50_CD, 100_RD, [&dis2, &gen](auto, auto){
		return dis2(gen);
	});

	while(state.KeepRunning()){
		auto res = m1 * m2;
	}
}

int main(int argc, char** argv) {
	using i1 = std::int8_t;
	using i2 = std::int16_t;
	using i4 = std::int32_t;
	using i8 = std::int64_t;
	using f4 = float;
	using f8 = double;

	benchmark::RegisterBenchmark("i1*i1", BM_matrix_multiplication< i1, i1 >);
	benchmark::RegisterBenchmark("i1*i2", BM_matrix_multiplication< i1, i2 >);
	benchmark::RegisterBenchmark("i1*i4", BM_matrix_multiplication< i1, i4 >);
	benchmark::RegisterBenchmark("i1*i8", BM_matrix_multiplication< i1, i8 >);
	benchmark::RegisterBenchmark("i1*f4", BM_matrix_multiplication< i1, f4 >);
	benchmark::RegisterBenchmark("i1*f8", BM_matrix_multiplication< i1, f8 >);

	benchmark::RegisterBenchmark("i2*i1", BM_matrix_multiplication< i2, i1 >);
	benchmark::RegisterBenchmark("i2*i2", BM_matrix_multiplication< i2, i2 >);
	benchmark::RegisterBenchmark("i2*i4", BM_matrix_multiplication< i2, i4 >);
	benchmark::RegisterBenchmark("i2*i8", BM_matrix_multiplication< i2, i8 >);
	benchmark::RegisterBenchmark("i2*f4", BM_matrix_multiplication< i2, f4 >);
	benchmark::RegisterBenchmark("i2*f8", BM_matrix_multiplication< i2, f8 >);

	benchmark::RegisterBenchmark("i4*i1", BM_matrix_multiplication< i4, i1 >);
	benchmark::RegisterBenchmark("i4*i2", BM_matrix_multiplication< i4, i2 >);
	benchmark::RegisterBenchmark("i4*i4", BM_matrix_multiplication< i4, i4 >);
	benchmark::RegisterBenchmark("i4*i8", BM_matrix_multiplication< i4, i8 >);
	benchmark::RegisterBenchmark("i4*f4", BM_matrix_multiplication< i4, f4 >);
	benchmark::RegisterBenchmark("i4*f8", BM_matrix_multiplication< i4, f8 >);

	benchmark::RegisterBenchmark("i8*i1", BM_matrix_multiplication< i8, i1 >);
	benchmark::RegisterBenchmark("i8*i2", BM_matrix_multiplication< i8, i2 >);
	benchmark::RegisterBenchmark("i8*i4", BM_matrix_multiplication< i8, i4 >);
	benchmark::RegisterBenchmark("i8*i8", BM_matrix_multiplication< i8, i8 >);
	benchmark::RegisterBenchmark("i8*f4", BM_matrix_multiplication< i8, f4 >);
	benchmark::RegisterBenchmark("i8*f8", BM_matrix_multiplication< i8, f8 >);

	benchmark::RegisterBenchmark("f4*i1", BM_matrix_multiplication< f4, i1 >);
	benchmark::RegisterBenchmark("f4*i2", BM_matrix_multiplication< f4, i2 >);
	benchmark::RegisterBenchmark("f4*i4", BM_matrix_multiplication< f4, i4 >);
	benchmark::RegisterBenchmark("f4*i8", BM_matrix_multiplication< f4, i8 >);
	benchmark::RegisterBenchmark("f4*f4", BM_matrix_multiplication< f4, f4 >);
	benchmark::RegisterBenchmark("f4*f8", BM_matrix_multiplication< f4, f8 >);

	benchmark::RegisterBenchmark("f8*i1", BM_matrix_multiplication< f8, i1 >);
	benchmark::RegisterBenchmark("f8*i2", BM_matrix_multiplication< f8, i2 >);
	benchmark::RegisterBenchmark("f8*i4", BM_matrix_multiplication< f8, i4 >);
	benchmark::RegisterBenchmark("f8*i8", BM_matrix_multiplication< f8, i8 >);
	benchmark::RegisterBenchmark("f8*f4", BM_matrix_multiplication< f8, f4 >);
	benchmark::RegisterBenchmark("f8*f8", BM_matrix_multiplication< f8, f8 >);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
