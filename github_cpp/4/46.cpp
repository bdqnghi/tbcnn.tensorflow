//
// Created by RobertVoropaev on 06.07.18.
//

#include <cstdlib>
#include <atomic>
#include <vector>
#include <forward_list>
#include <mutex>
#include <shared_mutex>

class Semaphore {
public:
    explicit Semaphore(const size_t count = 0)
            : count_(count) {}

    void Acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        while(count_ == 0){
            has_tokens_.wait(lock);
        }
        count_--;
    }

    void Release() {
        std::lock_guard<std::mutex> lock(mutex_);
        count_++;
        has_tokens_.notify_one();
    }

private:
    size_t count_;
    std::mutex mutex_;
    std::condition_variable has_tokens_;
};


class ReaderWriterLock {
public:
    ReaderWriterLock()
            :  semaphore_(1),
               reader_counter_(0) {}

    void lock_shared() {
        std::lock_guard<std::mutex> lock(mutex_);
        if(reader_counter_.fetch_add(1) == 0){
            semaphore_.Acquire();
        }

    }

    void unlock_shared() {
        std::lock_guard<std::mutex> lock(mutex_);
        if(reader_counter_.fetch_sub(1) == 1){
            semaphore_.Release();
        }

    }

    void lock() {
        semaphore_.Acquire();
    }

    void unlock() {
        semaphore_.Release();
    }

private:
    Semaphore semaphore_;
    std::mutex mutex_;
    std::atomic<size_t> reader_counter_;
};


template <typename T, class HashFunction = std::hash<T>>
class StripedHashSet {
private:
    using RWLock = ReaderWriterLock;
    using Stripes = std::vector<ReaderWriterLock>;

    using ReaderLocker = std::shared_lock<RWLock>;
    using WriterLocker = std::unique_lock<RWLock>;

    using Bucket = std::forward_list<T>;
    using Buckets = std::vector<Bucket>;

public:
    explicit StripedHashSet(const size_t concurrency_level = 4,
                            const size_t growth_factor = 2,
                            const double load_factor = 0.8)
            :  stripes_(concurrency_level),
               buckets_(concurrency_level),
               growth_factor_(growth_factor),
               max_load_factor_(load_factor),
               size_(0),
               bucket_count_(concurrency_level),
               concurrency_level_(concurrency_level) {
    }

    StripedHashSet(const std::atomic<size_t> &size_) : size_(size_) {}

    bool Insert(T element) {
        size_t hash_value = HashFunction()(element);
        size_t stripe_index = GetStripeIndex(hash_value);
        WriterLocker locker(stripes_[stripe_index]);
        Bucket& bucket = GetBucket(hash_value);

        if (Element_contains_in_bucket(element, bucket)) {
            return false;
        }

        bucket.push_front(element);
        size_++;

        if (MaxLoadFactorExceeded()) {
            size_t expected_bucket_count = bucket_count_;
            locker.unlock();
            TryExpandTable(expected_bucket_count);
        }
        return true;
    }

    bool Remove(const T& element) {
        size_t hash_value = HashFunction()(element);
        size_t stripe_index = GetStripeIndex(hash_value);
        WriterLocker locker(stripes_[stripe_index]);
        Bucket& bucket = GetBucket(hash_value);

        if (!Element_contains_in_bucket(element, bucket)) {
            return false;
        }

        size_--;
        bucket.remove(element);

        return true;
    }

    bool Contains(const T& element) {
        size_t hash_value = HashFunction()(element);
        size_t stripe_index = GetStripeIndex(hash_value);
        ReaderLocker locker(stripes_[stripe_index]);
        Bucket& bucket = GetBucket(hash_value);

        return Element_contains_in_bucket(element, bucket);
    }

    size_t GetSize() const {
        return size_;
    }

    size_t GetBucketCount() const {
        return bucket_count_;
    }


private:
    bool Element_contains_in_bucket(const T &element, Bucket &bucket) {
        bool result = false;
        for (T& item : bucket) {
            if (element == item) {
                result = true;
                break;
            }
        }
        return result;
    }

    bool MaxLoadFactorExceeded() const {
        return double(size_) / bucket_count_ > max_load_factor_;
    }

    Bucket& GetBucket(const size_t hash_value) {
        return buckets_.at(GetBucketIndex(hash_value));
    }

    const Bucket& GetBucket(const size_t hash_value) const {
        return buckets_.at(GetBucketIndex(hash_value));
    }


    void TryExpandTable(const size_t expected_bucket_count) {
        WriterLocker lockers[concurrency_level_];
        lockers[0] = WriterLocker(stripes_[0]);

        if (bucket_count_ == expected_bucket_count) {
            for (size_t i = 1; i < concurrency_level_; i += 1) {
                lockers[i]= WriterLocker(stripes_[i]);
            }

            bucket_count_ *= growth_factor_;
            Buckets new_buckets(bucket_count_);

            for (auto& bucket: buckets_) {
                for (T& item : bucket) {
                    size_t hash_value = HashFunction()(item);
                    size_t new_bucket_index = GetBucketIndex(hash_value);
                    new_buckets[new_bucket_index].push_front(item);
                }
            }
            buckets_.swap(new_buckets);
        }
    }

    size_t GetBucketIndex(const size_t hash_value) const {
        return hash_value % bucket_count_;
    }

    size_t GetStripeIndex(const size_t hash_value) const {
        return hash_value % concurrency_level_;
    }

private:
    size_t concurrency_level_;
    size_t growth_factor_;
    double max_load_factor_;

    Stripes stripes_;
    Buckets buckets_;

    std::atomic<size_t> size_;
    size_t bucket_count_;
};
