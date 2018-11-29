#include "BucketSort.h"

bool BucketSort::aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) const {

    if (x == y) return false;     // if the two numbers are the same then one is not less than the other

    unsigned int a = x;
    unsigned int b = y;

    // work out the digit we are currently comparing on.
    if (pow == 0) {
        a = getFirstDigit(a);
        b = getFirstDigit(b);
    } else {
        while (a / 10 >= powResults[pow]) {
            a /= 10;
        }
        while (b / 10 >= powResults[pow]) {
            b /= 10;
        }
    }

    if (a == b)
        return aLessB(x, y, pow + 1); // recurse if this digit is the same
    else
        return a < b;
}

unsigned int BucketSort::getFirstDigit(unsigned int x) const {
    while (x >= 10) {
        x /= 10;
    }
    return x;
}

void BucketSort::sortBucket() {
    for (auto p = takeCurrBucketIndex(); p.second == true; p = takeCurrBucketIndex()) {
        auto& bucket = buckets[p.first];

        std::sort(bucket.begin(), bucket.end(), [this](const unsigned int& x, const unsigned int& y) {
            return aLessB(x, y);
        });
        auto pos = 0U;
        for (auto i = 0U; i < p.first; ++i) {
            pos += buckets[i].size();   // move to elem 0 of bucket i+1
        }

        for (auto i = 0U; i < bucket.size(); ++i) {
            numbersToSort[pos] = bucket[i];
            ++pos;
        }
    }
}

void BucketSort::calculatePowResults() {
    powResults.clear();
    auto pow = 0U;

    for (auto a = std::numeric_limits<unsigned int>::max(); a > 0; a /= 10) {
        powResults.push_back((unsigned int) std::round(std::pow(10, pow)));
        ++pow;
    }
    powResults.push_back((unsigned int) std::round(std::pow(10, pow)));
}

void BucketSort::sort(const unsigned int numCores) {
    assert(numCores != 0);
    const auto numThreads = numCores - 1;
    calculatePowResults();
    buckets.clear();
    buckets.resize(10);

    // Insert numbers into buckets
    for (const auto& num : numbersToSort) {
        auto firstDigit = getFirstDigit(num);
        buckets[firstDigit].push_back(num);
    }

    auto threads = std::vector<std::thread>{};
    for (auto i = 0U; i < numThreads; ++i) {
        threads.push_back(std::thread{[this]() { this->sortBucket(); }});
    }
    sortBucket();

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

std::pair<unsigned int, bool> BucketSort::takeCurrBucketIndex() {
    std::lock_guard<std::mutex> guard(currBucketIndexMutex);
    if (currBucketIndex < buckets.size()) {
        return std::make_pair(currBucketIndex++, true);
    }
    return std::make_pair(currBucketIndex, false);
}
