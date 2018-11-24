#include "bloom-filter.hpp"
#include "util.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <limits>
#include <cstdlib>
#include <cassert>
#include <iostream>

// https://github.com/ArashPartow/bloom
// http://www.partow.net/programming/bloomfilter/index.html

namespace psync {

bloom_parameters::bloom_parameters()
: minimum_size(1)
, maximum_size(std::numeric_limits<unsigned int>::max())
, minimum_number_of_hashes(1)
, maximum_number_of_hashes(std::numeric_limits<unsigned int>::max())
, projected_element_count(200)
, false_positive_probability(1.0 / projected_element_count)
, random_seed(0xA5A5A5A55A5A5A5AULL)
{}

bool
bloom_parameters::compute_optimal_parameters()
{
  double min_m = std::numeric_limits<double>::infinity();
  double min_k = 0.0;
  double curr_m = 0.0;
  double k = 1.0;

  while (k < 1000.0)
  {
    double numerator   = (- k * projected_element_count);
    double denominator = std::log(1.0 - std::pow(false_positive_probability, 1.0 / k));
    curr_m = numerator / denominator;
    if (curr_m < min_m)
    {
      min_m = curr_m;
      min_k = k;
    }
    k += 1.0;
  }

  optimal_parameters_t& optp = optimal_parameters;

  optp.number_of_hashes = static_cast<unsigned int>(min_k);
  optp.table_size = static_cast<unsigned int>(min_m);
  optp.table_size += (((optp.table_size % bits_per_char) != 0) ? (bits_per_char - (optp.table_size % bits_per_char)) : 0);

  if (optp.number_of_hashes < minimum_number_of_hashes)
     optp.number_of_hashes = minimum_number_of_hashes;
  else if (optp.number_of_hashes > maximum_number_of_hashes)
     optp.number_of_hashes = maximum_number_of_hashes;

  if (optp.table_size < minimum_size)
     optp.table_size = minimum_size;
  else if (optp.table_size > maximum_size)
     optp.table_size = maximum_size;

  return true;
}

/*************************************************************************/
/* bloom-filter */

bloom_filter::bloom_filter()
: bit_table_(0)
, salt_count_(0)
, table_size_(0)
, raw_table_size_(0)
, projected_element_count_(0)
, inserted_element_count_(0)
, random_seed_(0)
, desired_false_positive_probability_(0.0)
{}

bloom_filter::bloom_filter(const bloom_parameters& p)
: bit_table_(0)
, projected_element_count_(p.projected_element_count)
, inserted_element_count_(0)
, random_seed_((p.random_seed * 0xA5A5A5A5) + 1)
, desired_false_positive_probability_(p.false_positive_probability)
{
  salt_count_ = p.optimal_parameters.number_of_hashes;
  table_size_ = p.optimal_parameters.table_size;
  generate_unique_salt();
  raw_table_size_ = table_size_ / bits_per_char;
  //bit_table_ = new cell_type[static_cast<std::size_t>(raw_table_size_)];
  bit_table_.resize(static_cast<std::size_t>(raw_table_size_), 0x00);
}

void
bloom_filter::clear()
{
  bit_table_.resize(static_cast<std::size_t>(raw_table_size_), 0x00);
  inserted_element_count_ = 0;
}

void
bloom_filter::insert(const std::string& key)
{
  std::size_t bit_index = 0;
  std::size_t bit = 0;
  for (std::size_t i = 0; i < salt_.size(); ++i)
  {
     compute_indices(MurmurHash3(salt_[i], ParseHex(key)), bit_index, bit);
     bit_table_[bit_index/bits_per_char] |= bit_mask[bit];
  }
  ++inserted_element_count_;
}

bool
bloom_filter::contains(const std::string& key)
{
  // This was a hack for subscribe all
  // A good implementation would have a human readable
  // component instead of empty subscription list that would indicate full sync
  // and never calls bloom filter
  /*if (projected_element_count_== 1 && desired_false_positive_probability_ == 0.001) {
    // subscribe all
    return true;
  }*/

  std::size_t bit_index = 0;
  std::size_t bit = 0;

  for (std::size_t i = 0; i < salt_.size(); ++i)
  {
    compute_indices(MurmurHash3(salt_[i], ParseHex(key)), bit_index, bit);
    if ((bit_table_[bit_index/bits_per_char] & bit_mask[bit]) != bit_mask[bit]) {
      return false;
    }
  }

  return true;
}

std::vector <bloom_filter::cell_type>
bloom_filter::table()
{
  return bit_table_;
}

void
bloom_filter::setTable(std::vector <bloom_filter::cell_type> table)
{
  assert(table.size() == raw_table_size_);
  bit_table_ = table;
}

unsigned int
bloom_filter::getTableSize()
{
  return raw_table_size_;
}

void
bloom_filter::generate_unique_salt()
{
  const unsigned int predef_salt_count = 128;
  static const bloom_type predef_salt[predef_salt_count] =
                             {
                                0xAAAAAAAA, 0x55555555, 0x33333333, 0xCCCCCCCC,
                                0x66666666, 0x99999999, 0xB5B5B5B5, 0x4B4B4B4B,
                                0xAA55AA55, 0x55335533, 0x33CC33CC, 0xCC66CC66,
                                0x66996699, 0x99B599B5, 0xB54BB54B, 0x4BAA4BAA,
                                0xAA33AA33, 0x55CC55CC, 0x33663366, 0xCC99CC99,
                                0x66B566B5, 0x994B994B, 0xB5AAB5AA, 0xAAAAAA33,
                                0x555555CC, 0x33333366, 0xCCCCCC99, 0x666666B5,
                                0x9999994B, 0xB5B5B5AA, 0xFFFFFFFF, 0xFFFF0000,
                                0xB823D5EB, 0xC1191CDF, 0xF623AEB3, 0xDB58499F,
                                0xC8D42E70, 0xB173F616, 0xA91A5967, 0xDA427D63,
                                0xB1E8A2EA, 0xF6C0D155, 0x4909FEA3, 0xA68CC6A7,
                                0xC395E782, 0xA26057EB, 0x0CD5DA28, 0x467C5492,
                                0xF15E6982, 0x61C6FAD3, 0x9615E352, 0x6E9E355A,
                                0x689B563E, 0x0C9831A8, 0x6753C18B, 0xA622689B,
                                0x8CA63C47, 0x42CC2884, 0x8E89919B, 0x6EDBD7D3,
                                0x15B6796C, 0x1D6FDFE4, 0x63FF9092, 0xE7401432,
                                0xEFFE9412, 0xAEAEDF79, 0x9F245A31, 0x83C136FC,
                                0xC3DA4A8C, 0xA5112C8C, 0x5271F491, 0x9A948DAB,
                                0xCEE59A8D, 0xB5F525AB, 0x59D13217, 0x24E7C331,
                                0x697C2103, 0x84B0A460, 0x86156DA9, 0xAEF2AC68,
                                0x23243DA5, 0x3F649643, 0x5FA495A8, 0x67710DF8,
                                0x9A6C499E, 0xDCFB0227, 0x46A43433, 0x1832B07A,
                                0xC46AFF3C, 0xB9C8FFF0, 0xC9500467, 0x34431BDF,
                                0xB652432B, 0xE367F12B, 0x427F4C1B, 0x224C006E,
                                0x2E7E5A89, 0x96F99AA5, 0x0BEB452A, 0x2FD87C39,
                                0x74B2E1FB, 0x222EFD24, 0xF357F60C, 0x440FCB1E,
                                0x8BBE030F, 0x6704DC29, 0x1144D12F, 0x948B1355,
                                0x6D8FD7E9, 0x1C11A014, 0xADD1592F, 0xFB3C712E,
                                0xFC77642F, 0xF9C4CE8C, 0x31312FB9, 0x08B0DD79,
                                0x318FA6E7, 0xC040D23D, 0xC0589AA7, 0x0CA5C075,
                                0xF874B172, 0x0CF914D5, 0x784D3280, 0x4E8CFEBC,
                                0xC569F575, 0xCDB2A091, 0x2CC016B4, 0x5C5F4421
                             };

  if (salt_count_ <= predef_salt_count)
  {
    std::copy(predef_salt,
              predef_salt + salt_count_,
              std::back_inserter(salt_));
    for (unsigned int i = 0; i < salt_.size(); ++i)
    {
      salt_[i] = salt_[i] * salt_[(i + 3) % salt_.size()] + static_cast<bloom_type>(random_seed_);
    }
  }
  else
  {
    std::copy(predef_salt,predef_salt + predef_salt_count,std::back_inserter(salt_));
    srand(static_cast<unsigned int>(random_seed_));
    while (salt_.size() < salt_count_)
    {
      bloom_type current_salt = static_cast<bloom_type>(rand()) * static_cast<bloom_type>(rand());
      if (0 == current_salt) continue;
      if (salt_.end() == std::find(salt_.begin(), salt_.end(), current_salt))
      {
        salt_.push_back(current_salt);
      }
    }
  }
}

void
bloom_filter::compute_indices(const bloom_type& hash, std::size_t& bit_index, std::size_t& bit)
{
  bit_index = hash % table_size_;
  bit = bit_index % bits_per_char;
}

} // namespace psync