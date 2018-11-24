/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2018,  The University of Memphis
 *
 * This file is part of PSync.
 * See AUTHORS.md for complete list of PSync authors and contributors.
 *
 * PSync is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * PSync is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * PSync, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 *

 * This file incorporates work covered by the following copyright and
 * permission notice:

 * The MIT License (MIT)

 * Copyright (c) 2000 Arash Partow

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include "bloom-filter.hpp"
#include "util.hpp"

#include <ndn-cxx/util/logger.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <limits>
#include <cstdlib>

// https://github.com/ArashPartow/bloom

NDN_LOG_INIT(psync.BloomFilter);

namespace psync {

static const std::size_t bits_per_char = 0x08;
static const unsigned char bit_mask[bits_per_char] = {
  0x01,  //00000001
  0x02,  //00000010
  0x04,  //00000100
  0x08,  //00001000
  0x10,  //00010000
  0x20,  //00100000
  0x40,  //01000000
  0x80   //10000000
};

BloomParameters::BloomParameters()
: minimum_size(1)
, maximum_size(std::numeric_limits<unsigned int>::max())
, minimum_number_of_hashes(1)
, maximum_number_of_hashes(std::numeric_limits<unsigned int>::max())
, projected_element_count(200)
, false_positive_probability(1.0 / projected_element_count)
, random_seed(0xA5A5A5A55A5A5A5AULL)
{}

bool
BloomParameters::compute_optimal_parameters()
{
  if (!(*this)) {
    return false;
  }

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

BloomFilter::BloomFilter()
 : bit_table_(0)
 , salt_count_(0)
 , table_size_(0)
 , raw_table_size_(0)
 , projected_element_count_(0)
 , inserted_element_count_(0)
 , random_seed_(0)
 , desired_false_positive_probability_(0.0)
{}

BloomFilter::BloomFilter(const BloomParameters& p)
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

BloomFilter::BloomFilter(unsigned int projected_element_count,
                         double false_positive_probability)
 : BloomFilter(getParameters(projected_element_count, false_positive_probability))
{
}

BloomFilter::BloomFilter(unsigned int projected_element_count,
                         double false_positive_probability,
                         const ndn::name::Component& bfName)
 : BloomFilter(projected_element_count, false_positive_probability)
{
  std::vector<BloomFilter::cell_type> table(bfName.value_begin(), bfName.value_end());

  if (table.size() != raw_table_size_) {
    BOOST_THROW_EXCEPTION(Error("Received BloomFilter cannot be decoded!"));
  }
  bit_table_ = table;
}

BloomParameters
BloomFilter::getParameters(unsigned int projected_element_count,
                           double false_positive_probability)
{
  BloomParameters opt;
  opt.false_positive_probability = false_positive_probability;
  opt.projected_element_count = projected_element_count;

  if (!opt) {
    NDN_LOG_WARN("Bloom parameters are not correct!");
  }

  opt.compute_optimal_parameters();
  return opt;
}

void
BloomFilter::appendToName(ndn::Name& name) const
{
  name.appendNumber(projected_element_count_);
  name.appendNumber((int)(desired_false_positive_probability_ * 1000));
  name.append(bit_table_.begin(), bit_table_.end());
}

void
BloomFilter::clear()
{
  bit_table_.resize(static_cast<std::size_t>(raw_table_size_), 0x00);
  inserted_element_count_ = 0;
}

void
BloomFilter::insert(const std::string& key)
{
  std::size_t bit_index = 0;
  std::size_t bit = 0;
  for (std::size_t i = 0; i < salt_.size(); ++i)
  {
     compute_indices(murmurHash3(salt_[i], key), bit_index, bit);
     bit_table_[bit_index/bits_per_char] |= bit_mask[bit];
  }
  ++inserted_element_count_;
}

bool
BloomFilter::contains(const std::string& key) const
{
  std::size_t bit_index = 0;
  std::size_t bit = 0;

  for (std::size_t i = 0; i < salt_.size(); ++i)
  {
    compute_indices(murmurHash3(salt_[i], key), bit_index, bit);
    if ((bit_table_[bit_index/bits_per_char] & bit_mask[bit]) != bit_mask[bit]) {
      return false;
    }
  }

  return true;
}

std::vector <BloomFilter::cell_type>
BloomFilter::table() const
{
  return bit_table_;
}

void
BloomFilter::generate_unique_salt()
{
  /*
    Note:
    A distinct hash function need not be implementation-wise
    distinct. In the current implementation "seeding" a common
    hash function with different values seems to be adequate.
  */
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
BloomFilter::compute_indices(const bloom_type& hash,
                             std::size_t& bit_index, std::size_t& bit) const
{
  bit_index = hash % table_size_;
  bit = bit_index % bits_per_char;
}

bool
operator==(const BloomFilter& bf1, const BloomFilter& bf2)
{
  auto table1 = bf1.table();
  auto table2 = bf2.table();

  if (table1.size() != table2.size()) {
    return false;
  }

  for (size_t i = 0; i < table1.size(); i++) {
    if (table1[i] != table2[i]) {
      return false;
    }
  }
  return true;
}

std::ostream&
operator<<(std::ostream& out, const BloomFilter& bf)
{
  for (const auto& element : bf.table()) {
    out << unsigned(element);
  }
  return out;
}

} // namespace psync