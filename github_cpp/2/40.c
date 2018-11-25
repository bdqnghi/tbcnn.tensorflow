

#include <thread>

#include <catch.hpp>

#include <cpp-cache/lru-cache.h>
#include <cpp-cache/ttl-cache.h>

TEST_CASE("llru-ttl", "[llru-ttl]")
{
  using key_type = int;
  using value_type = std::string;
  const size_t cache_size = 2;
  const size_t ttl_max_age_ms = 200;

  const key_type one_key = 1;
  const value_type one_value = "one";
  const key_type two_key = 2;
  const value_type two_value = "two";
  const key_type three_key = 3;
  const value_type three_value = "three";
  const key_type four_key = 4;
  const value_type four_value = "four";

  using lru_ttl_cache_t = cpp_cache::cache<key_type, value_type, cpp_cache::policy::lru<key_type, cache_size, cpp_cache::policy::ttl<key_type, ttl_max_age_ms>>, cpp_cache::storage::map<key_type, value_type>>;
  lru_ttl_cache_t lru_ttl_cache;

  REQUIRE(lru_ttl_cache.max_size() == cache_size);
  REQUIRE(lru_ttl_cache.default_max_age() == ttl_max_age_ms);
  REQUIRE(lru_ttl_cache.size() == 0);
  REQUIRE(lru_ttl_cache.empty() == true);

  REQUIRE(lru_ttl_cache.has(one_key) == false);
  REQUIRE(lru_ttl_cache.has(two_key) == false);
  REQUIRE(lru_ttl_cache.has(three_key) == false);
  REQUIRE(lru_ttl_cache.has(four_key) == false);

  value_type tmp;
  REQUIRE(lru_ttl_cache.try_get(one_key, tmp) == false);
  REQUIRE(lru_ttl_cache.try_get(two_key, tmp) == false);
  REQUIRE(lru_ttl_cache.try_get(three_key, tmp) == false);
  REQUIRE(lru_ttl_cache.try_get(four_key, tmp) == false);

  try
  {
    lru_ttl_cache.get(one_key);
    REQUIRE(false);
  }
  catch (std::out_of_range&) { REQUIRE(true); }
  catch (...) { REQUIRE(false); }

  lru_ttl_cache.insert(one_key, one_value);
  REQUIRE(lru_ttl_cache.has(one_key) == true);
  REQUIRE(lru_ttl_cache.try_get(one_key, tmp) == true);
  REQUIRE(lru_ttl_cache.get(one_key) == one_value);
  REQUIRE(lru_ttl_cache.size() == 1);
  REQUIRE(lru_ttl_cache.empty() == false);

  lru_ttl_cache.insert(two_key, two_value);
  REQUIRE(lru_ttl_cache.has(two_key) == true);
  REQUIRE(lru_ttl_cache.try_get(two_key, tmp) == true);
  REQUIRE(lru_ttl_cache.get(two_key) == two_value);
  REQUIRE(lru_ttl_cache.size() == 2);
  REQUIRE(lru_ttl_cache.empty() == false);
  REQUIRE(lru_ttl_cache.has(one_key) == true);
  REQUIRE(lru_ttl_cache.try_get(one_key, tmp) == true);
  REQUIRE(lru_ttl_cache.get(one_key) == one_value);

  lru_ttl_cache.erase(three_key);
  REQUIRE(lru_ttl_cache.size() == 2);
  REQUIRE(lru_ttl_cache.empty() == false);
  REQUIRE(lru_ttl_cache.has(one_key) == true);
  REQUIRE(lru_ttl_cache.has(two_key) == true);

  lru_ttl_cache.erase(one_key);
  REQUIRE(lru_ttl_cache.size() == 1);
  REQUIRE(lru_ttl_cache.empty() == false);
  REQUIRE(lru_ttl_cache.has(one_key) == false);
  REQUIRE(lru_ttl_cache.has(two_key) == true);

  lru_ttl_cache.clear();
  REQUIRE(lru_ttl_cache.size() == 0);
  REQUIRE(lru_ttl_cache.empty() == true);
  REQUIRE(lru_ttl_cache.has(one_key) == false);
  REQUIRE(lru_ttl_cache.has(two_key) == false);

  lru_ttl_cache.insert(one_key, one_value);
  REQUIRE(lru_ttl_cache.has(one_key) == true);

  lru_ttl_cache.insert(two_key, two_value);
  REQUIRE(lru_ttl_cache.has(two_key) == true);
  REQUIRE(lru_ttl_cache.has(one_key) == true);

  lru_ttl_cache.insert(three_key, three_value);
  REQUIRE(lru_ttl_cache.has(three_key) == true);
  REQUIRE(lru_ttl_cache.has(two_key) == true);
  REQUIRE(lru_ttl_cache.has(one_key) == false);

  lru_ttl_cache.insert(four_key, four_value);
  REQUIRE(lru_ttl_cache.has(four_key) == true);
  REQUIRE(lru_ttl_cache.has(three_key) == true);
  REQUIRE(lru_ttl_cache.has(two_key) == false);
  REQUIRE(lru_ttl_cache.has(one_key) == false);

  std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(2 * ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(four_key) == false);
  REQUIRE(lru_ttl_cache.has(three_key) == false);
  REQUIRE(lru_ttl_cache.has(two_key) == false);
  REQUIRE(lru_ttl_cache.has(one_key) == false);

  lru_ttl_cache.insert(one_key, one_value);
  REQUIRE(lru_ttl_cache.has(one_key) == true);

  lru_ttl_cache.insert(two_key, two_value);
  REQUIRE(lru_ttl_cache.has(two_key) == true);
  REQUIRE(lru_ttl_cache.has(one_key) == true);

  std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(0.5 * ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(one_key) == true);
  REQUIRE(lru_ttl_cache.has(two_key) == true);

  REQUIRE(lru_ttl_cache.get(one_key) == one_value);

  std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(0.7 * ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(one_key) == true);
  REQUIRE(lru_ttl_cache.has(two_key) == false);

  lru_ttl_cache.touch(one_key);

  std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(0.5 * ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(one_key) == true);

  std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(one_key) == false);

  lru_ttl_cache.insert(one_key, one_value, lru_ttl_cache_t::duration_type(2 * ttl_max_age_ms));
  REQUIRE(lru_ttl_cache.has(one_key) == true);

  std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1.5 * ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(one_key) == true);

  std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(ttl_max_age_ms));

  REQUIRE(lru_ttl_cache.has(one_key) == false);
}
