#include <salgo/hash-table.hpp>
#include <gtest/gtest.h>


using namespace salgo;

TEST(Hash_Table, iterate) {
	Hash_Table<int> ht;
	ht.emplace(3);
	ht.emplace(30);
	ht.emplace(300);
	ht.emplace(3000);
	ht.emplace(30000);
	ht.emplace(300000);

	int sum = 0;
	for(auto& e : ht) {
		sum += e;
	}
	EXPECT_EQ(333333, sum);
}

TEST(Hash_Table, iterate_empty) {
	Hash_Table<int> ht;
	int sum = 0;
	for(auto& e : ht) sum += e;
	EXPECT_EQ(0, sum);
}

TEST(Hash_Table, iterate_empty_2) {
	Hash_Table<int> ht;
	ht.emplace(123);

	if(!ht(12).exists()) ht(123).erase();

	int sum = 0;
	for(auto& e : ht) sum += e;
	EXPECT_EQ(0, sum);
}

TEST(Hash_Table, erase) {
	Hash_Table<int> ht;
	ht.emplace(3);
	ht.emplace(30);
	ht.emplace(300);
	ht.emplace(3000);
	ht.emplace(30000);
	ht.emplace(300000);

	ht(30).erase();
	ht(3000).erase();
	ht(300000).erase();

	int sum = 0;
	for(auto& e : ht) {
		sum += e;
	}

	EXPECT_EQ(30303, sum);
}


TEST(Hash_Table, initializer_list) {
	Hash_Table<int> ht = {1, 10, 10000, 1000, 100};
	int sum = 0;
	for(auto& e : ht) sum += e;
	EXPECT_EQ(11111, sum);
}


TEST(Hash_Table, key_val) {
	Hash_Table<int, std::string> m = {{12,"twelve"}, {6,"six"}, {3,"three"}, {20,"twenty"}};
	std::map<int,std::string> test;
	for(auto& e : m) {
		test.emplace(std::pair(e.key(), e.val()));
	}
	EXPECT_EQ(4, (int)test.size());
	EXPECT_EQ("twelve", test[12]);
	EXPECT_EQ("six", test[6]);
	EXPECT_EQ("three", test[3]);
	EXPECT_EQ("twenty", test[20]);

}

