#include "BucketSort.h"

BucketSort::BucketSort(){

}

BucketSort::~BucketSort()
{
	data.clear();
	data.shrink_to_fit();
}

void BucketSort::sort(std::vector<long long int>& in_data)
{
	this->data = in_data;
	int bucket_size = this->data.size() * 0.1;
	long long int bucket_range = ceil(pow(10, (int)log10((long long int)*std::max_element(data.begin(), data.end())) + 1)/bucket_size);
	running_time = clock();
	bucket(bucket_size, bucket_range);
	running_time = clock() - running_time;
}

void BucketSort::bucket(int size, long long int range)
{
	std::vector<std::vector<long long int>> buckets(size);
	
	for (int i = 0; i < this->data.size(); i++)
	{
		buckets[this->data[i] / range].push_back(this->data[i]);
	}

	int data_index = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < buckets[i].size(); j++)
		{
			this->data[data_index++] = buckets[i][j];
		}
	}
	insertionSortForBucketSort();
}

void BucketSort::insertionSortForBucketSort()
{
	long long int temp;
	int j;
	for (int i = 1; i < data.size(); i++) {
		temp = data[i];
		j = i - 1;
		while (j >= 0 && data[j] > temp) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = temp;
	}
}

void BucketSort::print()
{
	std::cout << "Bucket Sort: " << std::endl;
	AbstractSortAlgorithm::print();
}

void BucketSort::printRunningTime(std::string& file_name)
{
	int pos = file_name.find("/");
	std::string out_file_name = file_name.substr(pos + 1, file_name.size() - 1);
	std::string message = "Bucket Sort";
	AbstractSortAlgorithm::exportSortedData(std::string("bucket_sort_"), out_file_name);
	AbstractSortAlgorithm::exportRunningTime(message, out_file_name);
}
