#include "common_header.h"

typedef unsigned InputType;



unsigned long HanoiTowerRecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (HanoiTowerRecursive(n - 1) << 1) + 1;
    }
}


unsigned long HanoiTowerClosedform(const InputType n) {
    return ((unsigned long)1 << n) - 1;
}




unsigned long IndirectHanoiTowerRecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return IndirectHanoiTowerRecursive(n - 1) * 3 + 2;
    }
}


unsigned long IndirectHanoiTowerClosedform(const InputType n) {
    return std::pow(double(3.0), n) - 1;
}




unsigned long DoubleHanoiTowerARecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (DoubleHanoiTowerARecursive(n - 1) << 1) + 2;
    }
}


unsigned long DoubleHanoiTowerAClosedform(const InputType n) {
    return (long(1) << (n + 1)) - 2;
}


unsigned long DoubleHanoiTowerBClosedform(const InputType n) {
    return (long(1) << (n + 2)) - 5;
}

constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr InputType UPPER = LONG_BITS_NUM - 1;
constexpr InputType SAMPLE = 8;

SIMPLE_BENCHMARK(HanoiTowerRecursive, LOWER);
SIMPLE_BENCHMARK(HanoiTowerRecursive, UPPER);
SIMPLE_BENCHMARK(HanoiTowerRecursive, SAMPLE);
RANDOM_BENCHMARK(HanoiTowerRecursive, LOWER, UPPER);

SIMPLE_BENCHMARK(HanoiTowerClosedform, LOWER);
SIMPLE_BENCHMARK(HanoiTowerClosedform, UPPER);
SIMPLE_BENCHMARK(HanoiTowerClosedform, SAMPLE);
RANDOM_BENCHMARK(HanoiTowerClosedform, LOWER, UPPER);

SIMPLE_TEST(HanoiTowerRecursive, TestLOWER, 0, LOWER);
SIMPLE_TEST(HanoiTowerRecursive, TestUPPER, std::numeric_limits<unsigned long>::max() / 2, UPPER);
SIMPLE_TEST(HanoiTowerRecursive, TestSAMPLE, 255, SAMPLE);

SIMPLE_TEST(HanoiTowerClosedform, TestLOWER, 0, LOWER);
SIMPLE_TEST(HanoiTowerClosedform, TestUPPER, std::numeric_limits<unsigned long>::max() / 2, UPPER);
SIMPLE_TEST(HanoiTowerClosedform, TestSAMPLE, 255, SAMPLE);

MUTUAL_RANDOM_TEST(HanoiTowerRecursive, HanoiTowerClosedform, LOWER, UPPER);


constexpr InputType IndirectHanoiTowerUPPER = LONG_BITS_NUM / 3;

SIMPLE_BENCHMARK(IndirectHanoiTowerRecursive, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTowerRecursive, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTowerRecursive, SAMPLE);
RANDOM_BENCHMARK(IndirectHanoiTowerRecursive, LOWER, IndirectHanoiTowerUPPER);

SIMPLE_BENCHMARK(IndirectHanoiTowerClosedform, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTowerClosedform, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTowerClosedform, SAMPLE);
RANDOM_BENCHMARK(IndirectHanoiTowerClosedform, LOWER, IndirectHanoiTowerUPPER);

SIMPLE_TEST(IndirectHanoiTowerRecursive, TestLOWER, 0, LOWER);
SIMPLE_TEST(IndirectHanoiTowerRecursive, TestIndirectHanoiTowerUPPER, 10460353202,
            IndirectHanoiTowerUPPER);
SIMPLE_TEST(IndirectHanoiTowerRecursive, TestSAMPLE, 6560, SAMPLE);

SIMPLE_TEST(IndirectHanoiTowerClosedform, TestLOWER, 0, LOWER);
SIMPLE_TEST(IndirectHanoiTowerClosedform, TestIndirectHanoiTowerUPPER, 10460353202,
            IndirectHanoiTowerUPPER);
SIMPLE_TEST(IndirectHanoiTowerClosedform, TestSAMPLE, 6560, SAMPLE);

MUTUAL_RANDOM_TEST(IndirectHanoiTowerRecursive, IndirectHanoiTowerClosedform, LOWER,
                   IndirectHanoiTowerUPPER);

const InputType DoubleHanoiTowerUPPER = UPPER - 2;

SIMPLE_BENCHMARK(DoubleHanoiTowerARecursive, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTowerARecursive, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTowerARecursive, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTowerARecursive, LOWER, DoubleHanoiTowerUPPER);

SIMPLE_BENCHMARK(DoubleHanoiTowerAClosedform, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTowerAClosedform, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTowerAClosedform, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTowerAClosedform, LOWER, DoubleHanoiTowerUPPER);

const InputType DoubleHanoiTowerBLOWER = 1;

SIMPLE_BENCHMARK(DoubleHanoiTowerBClosedform, DoubleHanoiTowerBLOWER);
SIMPLE_BENCHMARK(DoubleHanoiTowerBClosedform, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTowerBClosedform, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTowerBClosedform, LOWER, DoubleHanoiTowerUPPER);

SIMPLE_TEST(DoubleHanoiTowerARecursive, TestLOWER, 0, LOWER);
SIMPLE_TEST(DoubleHanoiTowerARecursive, TestDoubleHanoiTowerUPPER, 4611686018427387902,
            DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTowerARecursive, TestSAMPLE, 510, SAMPLE);

SIMPLE_TEST(DoubleHanoiTowerAClosedform, TestLOWER, 0, LOWER);
SIMPLE_TEST(DoubleHanoiTowerAClosedform, TestDoubleHanoiTowerUPPER, 4611686018427387902,
            DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTowerAClosedform, TestSAMPLE, 510, SAMPLE);

MUTUAL_RANDOM_TEST(DoubleHanoiTowerARecursive, DoubleHanoiTowerAClosedform, LOWER,
                   DoubleHanoiTowerUPPER);

SIMPLE_TEST(DoubleHanoiTowerBClosedform, TestDoubleHanoiTowerBLOWER, 3, DoubleHanoiTowerBLOWER);
SIMPLE_TEST(DoubleHanoiTowerBClosedform, TestDoubleHanoiTowerUPPER, 9223372036854775803,
            DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTowerBClosedform, TestSAMPLE, 1019, SAMPLE);
