#include "bloom-filter.h"
#include <stdlib.h>
#include <cmath>

#include "xxhash.h"

size_t BloomFilter::default_bytes_nb = 120;
size_t BloomFilter::default_seeds_nb = 8;
std::string BloomFilter::default_serialization_path = "";
std::string BloomFilter::default_serialization_filename = "blob.bf";
unsigned int BloomFilter::magic_header = 11062016;
unsigned int BloomFilter::serialization_version = 0;

BloomFilter::BloomFilter()
	: bytes_nb(default_bytes_nb)
	, seeds_nb(default_seeds_nb)
{
	Initialize();
}

BloomFilter::BloomFilter(size_t bytes_nb)
	: bytes_nb(bytes_nb)
	, seeds_nb(default_seeds_nb)
{
	Initialize();
}

BloomFilter::BloomFilter(size_t items_nb, float false_positive_probability)
{
	size_t bits = (size_t)(-(items_nb * std::log(false_positive_probability)) / (std::pow(std::log(2), 2)));
	bytes_nb = std::ceil(bits / 8);
	seeds_nb = (unsigned int)((items_nb / bits) * std::log(2));

	Initialize();
}

void BloomFilter::Initialize()
{
	serialization_filename = default_serialization_filename;
	serialization_path = default_serialization_path;
	U64_nb = (size_t)std::ceil(bytes_nb / 8);
	bitset = (U64*)calloc(std::ceil(bytes_nb / 8), sizeof(U64));
	for (size_t i = 0; i < seeds_nb; ++i)
	{
		seeds.push_back(rand());
	}
}

BloomFilter::~BloomFilter()
{
	free(bitset);
}

bool BloomFilter::Lookup(const std::string& input) const
{
	std::vector<std::pair<unsigned int, unsigned int>> indexes(seeds_nb);
	unsigned int ind = 0;
	bool probably_exist = true;

	std::for_each(seeds.begin(), seeds.end(), [&](unsigned int seed) {
		U64 hash = XXH64((void*)input.c_str(), input.size(), seed);
		indexes[ind++] = std::pair<unsigned int, unsigned int>{hash % U64_nb, (hash & 0b1111111) | 1};
	});
	std::sort(indexes.begin(), indexes.end());

	std::for_each(indexes.begin(), indexes.end(),
		[&](std::pair<unsigned int, unsigned int> index) { probably_exist &= (((bitset[index.first] >> index.second) & 1) != 0); });
	return probably_exist;
}

bool BloomFilter::Add(const std::string& input)
{
	std::vector<std::pair<unsigned int, unsigned int>> indexes(seeds_nb);
	unsigned int ind = 0;
	bool probably_exist = true;

	std::for_each(seeds.begin(), seeds.end(), [&](unsigned int seed) {
		U64 hash = XXH64((void*)input.c_str(), input.size(), seed);
		indexes[ind++] = std::pair<unsigned int, unsigned int>{hash % U64_nb, (hash & 0b1111111) | 1};
	});
	std::sort(indexes.begin(), indexes.end());

	std::for_each(indexes.begin(), indexes.end(), [&](std::pair<unsigned int, unsigned int> index) {
		probably_exist &= (((bitset[index.first] >> index.second) & 1) != 0);
		bitset[index.first] |= ((U64)1 << index.second);
	});
	return probably_exist;
}

bool BloomFilter::Serialize() const
{
	FILE* file;
	std::string filepath = serialization_path + serialization_filename;
	file = fopen(filepath.c_str(), "w");
	if (file == nullptr)
	{
		return false;
	}

	fwrite(&magic_header, sizeof(unsigned int), 1, file);
	fwrite(&serialization_version, sizeof(unsigned int), 1, file);
	fwrite(&seeds_nb, sizeof(size_t), 1, file);
	std::for_each(seeds.begin(), seeds.end(), [&](unsigned int seed) { fwrite(&seed, sizeof(U64), 1, file); });
	fwrite(&U64_nb, sizeof(size_t), 1, file);
	fwrite(bitset, sizeof(U64), U64_nb, file);

	fclose(file);
	return true;
}

bool BloomFilter::Unserialize()
{
	FILE* file;
	std::string filepath = serialization_path + serialization_filename;
	file = fopen(filepath.c_str(), "r");
	if (file == nullptr)
	{
		return false;
	}
	unsigned int* serialized_magic_header = new unsigned int;
	unsigned int* serialized_version = new unsigned int;
	size_t* serialized_seeds_nb = new size_t;
	size_t* serialized_U64_nb = new size_t;

	fread(serialized_magic_header, 1, sizeof(unsigned int), file);
	bool isSuccess = true;
	if (*serialized_magic_header == magic_header)
	{
		fread(serialized_version, 1, sizeof(unsigned int), file);

		fread(serialized_seeds_nb, 1, sizeof(size_t), file);
		seeds_nb = *serialized_seeds_nb;

		U64* serialized_seeds = new U64[seeds_nb];
		fread(serialized_seeds, seeds_nb, sizeof(U64), file);
		seeds = std::vector<U64>(serialized_seeds, serialized_seeds + seeds_nb);
		delete[] serialized_seeds;

		fread(serialized_U64_nb, 1, sizeof(size_t), file);
		U64_nb = *serialized_U64_nb;
		bytes_nb = U64_nb * 8;

		fread(bitset, U64_nb, sizeof(U64), file);
	}
	else
	{
		isSuccess = false;
	}
	fclose(file);
	delete serialized_magic_header;
	delete serialized_version;
	delete serialized_seeds_nb;
	delete serialized_U64_nb;

	return isSuccess;
}
