

#include <catch.hpp>

#include <cpp-cache/lru-cache.h>

TEST_CASE("lru", "[lru]")
{
  using key_type = int;
  using value_type = std::string;
  const size_t cache_size = 2;

  const key_type one_key = 1;
  const value_type one_value = "one";
  const key_type two_key = 2;
  const value_type two_value = "two";
  const key_type three_key = 3;
  const value_type three_value = "three";
  const key_type four_key = 4;
  const value_type four_value = "four";

  cpp_cache::lru_cache<key_type, value_type, cache_size> lru_cache;

  REQUIRE(lru_cache.max_size() == cache_size);
  REQUIRE(lru_cache.size() == 0);
  REQUIRE(lru_cache.empty() == true);

  REQUIRE(lru_cache.has(one_key) == false);
  REQUIRE(lru_cache.has(two_key) == false);
  REQUIRE(lru_cache.has(three_key) == false);
  REQUIRE(lru_cache.has(four_key) == false);

  value_type tmp;
  REQUIRE(lru_cache.try_get(one_key, tmp) == false);
  REQUIRE(lru_cache.try_get(two_key, tmp) == false);
  REQUIRE(lru_cache.try_get(three_key, tmp) == false);
  REQUIRE(lru_cache.try_get(four_key, tmp) == false);

  try
  {
    lru_cache.get(one_key);
    REQUIRE(false);
  }
  catch (std::out_of_range&) { REQUIRE(true); }
  catch (...) { REQUIRE(false); }

  lru_cache.insert(one_key, one_value);
  REQUIRE(lru_cache.has(one_key) == true);
  REQUIRE(lru_cache.try_get(one_key, tmp) == true);
  REQUIRE(lru_cache.get(one_key) == one_value);
  REQUIRE(lru_cache.size() == 1);
  REQUIRE(lru_cache.empty() == false);

  lru_cache.insert(two_key, two_value);
  REQUIRE(lru_cache.has(two_key) == true);
  REQUIRE(lru_cache.try_get(two_key, tmp) == true);
  REQUIRE(lru_cache.get(two_key) == two_value);
  REQUIRE(lru_cache.size() == 2);
  REQUIRE(lru_cache.empty() == false);
  REQUIRE(lru_cache.has(one_key) == true);
  REQUIRE(lru_cache.try_get(one_key, tmp) == true);
  REQUIRE(lru_cache.get(one_key) == one_value);

  lru_cache.erase(three_key);
  REQUIRE(lru_cache.size() == 2);
  REQUIRE(lru_cache.empty() == false);
  REQUIRE(lru_cache.has(one_key) == true);
  REQUIRE(lru_cache.has(two_key) == true);

  lru_cache.erase(one_key);
  REQUIRE(lru_cache.size() == 1);
  REQUIRE(lru_cache.empty() == false);
  REQUIRE(lru_cache.has(one_key) == false);
  REQUIRE(lru_cache.has(two_key) == true);

  lru_cache.clear();
  REQUIRE(lru_cache.size() == 0);
  REQUIRE(lru_cache.empty() == true);
  REQUIRE(lru_cache.has(one_key) == false);
  REQUIRE(lru_cache.has(two_key) == false);

  lru_cache.insert(one_key, one_value);
  REQUIRE(lru_cache.has(one_key) == true);

  lru_cache.insert(two_key, two_value);
  REQUIRE(lru_cache.has(two_key) == true);
  REQUIRE(lru_cache.has(one_key) == true);

  lru_cache.insert(three_key, three_value);
  REQUIRE(lru_cache.has(three_key) == true);
  REQUIRE(lru_cache.has(two_key) == true);
  REQUIRE(lru_cache.has(one_key) == false);

  lru_cache.insert(four_key, four_value);
  REQUIRE(lru_cache.has(four_key) == true);
  REQUIRE(lru_cache.has(three_key) == true);
  REQUIRE(lru_cache.has(two_key) == false);
  REQUIRE(lru_cache.has(one_key) == false);

  lru_cache.insert(one_key, one_value);
  REQUIRE(lru_cache.has(four_key) == true);
  REQUIRE(lru_cache.has(three_key) == false);
  REQUIRE(lru_cache.has(two_key) == false);
  REQUIRE(lru_cache.has(one_key) == true);

  REQUIRE(lru_cache.get(four_key) == four_value);
  REQUIRE(lru_cache.has(four_key) == true);
  REQUIRE(lru_cache.has(three_key) == false);
  REQUIRE(lru_cache.has(two_key) == false);
  REQUIRE(lru_cache.has(one_key) == true);

  lru_cache.insert(two_key, two_value);
  REQUIRE(lru_cache.has(four_key) == true);
  REQUIRE(lru_cache.has(three_key) == false);
  REQUIRE(lru_cache.has(two_key) == true);
  REQUIRE(lru_cache.has(one_key) == false);
}
