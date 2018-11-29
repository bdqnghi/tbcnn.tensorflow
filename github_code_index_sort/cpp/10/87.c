#include "bucket_sort.hpp"

bucket_sort::bucket_sort(int _nthreads) : sortable(_nthreads) {
	this->bucket_limits.resize(this->nbuckets);
	this->bucket_sizes.resize(this->nbuckets);
	this->buckets.resize(this->nbuckets);
}

std::string bucket_sort::name() const {
	return "Bucket sort";
}

void bucket_sort::limits_thread(int array[], int start, int stop){
	int min = std::numeric_limits<int>::max();
	int max = std::numeric_limits<int>::min();
	for(int x=start; x<stop; x++){
		min = std::min(array[x], min);
		max = std::max(array[x], max);
	}
	
	this->limits_mutex.lock();
	this->limits.first = std::min(this->limits.first, min);
	this->limits.second = std::max(this->limits.second, max);
	this->limits_mutex.unlock();
}

void bucket_sort::determine_bucket_ranges(){
	long long int min = this->limits.first;
	long long int max = this->limits.second;
	long long int count = static_cast<long long int>(ceil(static_cast<double>(max - min + 1) / static_cast<double>(this->nbuckets)));
	
	this->bucket_limits.clear();
	for(long long int start=min, stop=min + count; start <= max; start += count, stop += count){
		this->bucket_limits.push_back(std::make_pair(start, std::min(stop, max+1)));
	}
}

int bucket_sort::bucket_index(int value) const {
	int left = 0, right = static_cast<int>(this->bucket_limits.size());
	while(left <= right){
		int mid = left + (right - left) / 2;
		std::pair<int, int> range = this->bucket_limits[mid];
		if(value < range.first){
			right = mid - 1;
		} else if(value >= range.second){
			left = mid + 1;
		} else {
			return mid;
		}
	}
	
	return -1; //should never reach this
}

void bucket_sort::count_thread(int array[], int start, int stop){
	std::vector<int> _count(this->count.size());
	for(int x=start; x<stop; x++){
		_count[this->bucket_index(array[x])]++;
	}
	for(int x=0; x<_count.size(); x++){
		if(_count[x] > 0){
			this->bucket_mutex[x].lock();
			this->count[x] += _count[x];
			this->bucket_mutex[x].unlock();
		}
	}
}

void bucket_sort::insert_thread(int array[], int start, int stop){
	for(int x=start; x<stop; x++){
		int value = array[x];
		int index = this->bucket_index(value);
		this->bucket_mutex[index].lock();
		this->buckets[index].push_back(value);
		this->bucket_mutex[index].unlock();
	}
}

void bucket_sort::sort_thread(int array[], int bucket_index, int start){
	std::sort(this->buckets[bucket_index].begin(), this->buckets[bucket_index].end());
	std::copy(this->buckets[bucket_index].begin(), this->buckets[bucket_index].end(), array + start);
}

void bucket_sort::sort_array(int array[], int n){
	this->bucket_mutex = new std::mutex[this->nbuckets];
	
	std::vector<std::pair<int, int>> ranges;
	ranges.reserve(this->nthreads);
	
	std::vector<std::thread> threads;
	threads.reserve(this->nthreads);
	
	
	//find the minimum and maximum values in the array
	this->limits = {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	int nelements = static_cast<int>(ceil(static_cast<double>(n) / static_cast<double>(nthreads)));
	for(int x=0, start = 0, stop = nelements; x<this->nthreads && start < n; x++, start += nelements, stop += nelements){
		ranges.push_back(std::make_pair(start, std::min(stop, n)));
		threads.push_back(std::thread(&bucket_sort::limits_thread, this, array, start, stop));
	}
	for(std::size_t x=0; x<threads.size(); x++){
		threads[x].join();
	}
	threads.clear();
	
	
	//determine the minimum and maximum values for each bucket
	this->determine_bucket_ranges();
	
	
	//count how many items are in each bucket
	this->count.clear();
	this->count.resize(this->bucket_limits.size());
	this->bucket_sizes.resize(this->bucket_limits.size());
	this->buckets.resize(this->bucket_limits.size());
	
	for(std::size_t x=0; x<ranges.size(); x++){
		threads.push_back(std::thread(&bucket_sort::count_thread, this, array, ranges[x].first, ranges[x].second));
	}
	for(std::size_t x=0; x<threads.size(); x++){
		threads[x].join();
	}
	threads.clear();
	
	
	//populate each bucket with the values that are in its range
	for(std::size_t x=0; x<this->buckets.size(); x++){
		this->buckets[x].reserve(this->count[x]);
	}
	for(std::size_t x=0; x<ranges.size(); x++){
		threads.push_back(std::thread(&bucket_sort::insert_thread, this, array, ranges[x].first, ranges[x].second));
	}
	for(std::size_t x=0; x<threads.size(); x++){
		threads[x].join();
	}
	threads.clear();
	
	
	//now perform the sorting in each bucket and copy the sorted values back to the original array
	for(std::size_t x=0, start=0; x<buckets.size(); x++){
		if(!buckets[x].empty()){
			threads.push_back(std::thread(&bucket_sort::sort_thread, this, array, x, start));
			start += buckets[x].size();
		}
	}
	for(std::size_t x=0; x<threads.size(); x++){
		threads[x].join();
	}
	threads.clear();
	
	delete[] this->bucket_mutex;
}