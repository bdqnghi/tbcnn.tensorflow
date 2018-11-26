#include "stdafx.h"
#include "CppUnitTest.h"
#include <cassert>
#include <vector>
#include "AVL.h"
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVL
{
	template<class T>
	void do_lineage_test(ds::bin_tree::avl<T> &avl)
	{
		avl.inorder([](ds::bin_tree::node<T> *n)
		{
			const auto &ancestor = n->ancestor;
			switch (n->node_type)
			{
			case ds::bin_tree::node_type::k_left_child:
				Assert::AreEqual(n->data, ancestor->left_child->data);
				break;

			case ds::bin_tree::node_type::k_right_child:
				Assert::AreEqual(n->data, ancestor->right_child->data);
				break;

			case ds::bin_tree::node_type::k_root:
				break;

			default:
				// Not handled for this node_type
				assert(false);
			}

			const auto &left_child = n->left_child;
			if (left_child != nullptr)
			{
				Assert::AreEqual(n->data, left_child->ancestor->data);
			}

			const auto &right_child = n->right_child;
			if (right_child != nullptr)
			{
				Assert::AreEqual(n->data, right_child->ancestor->data);
			}
		});
	}

	template<class T>
	void do_remove_test(ds::bin_tree::avl<T> &avl, T key, std::vector<T> data)
	{
		avl.remove(key);

		std::vector<T> inorder;
		avl.inorder([&inorder](ds::bin_tree::node<T> * n) {inorder.push_back(n->data); });

		std::vector<T> expected(data.begin(), data.end());
		expected.erase(remove(expected.begin(), expected.end(), key), expected.end());
		sort(expected.begin(), expected.end());

		Assert::AreEqual(expected.size(), inorder.size());

		for (decltype(inorder.size()) i = 0; i < inorder.size(); ++i)
		{
			auto msg = "Expected: " + std::to_string(expected[i]) + "\tActual: " + std::to_string(inorder[i]) + "\n";
			Logger::WriteMessage(msg.c_str());
			Assert::AreEqual(expected[i], inorder[i]);
		}
	}

	template<class T>
	void do_inorder_test(ds::bin_tree::avl<T> &avl, std::vector<T> &data)
	{
		// Expected values
		auto expected = data;
		sort(expected.begin(), expected.end());

		// Output
		std::vector<T> output;
		avl.inorder([&output](ds::bin_tree::node<T> * n)
		{
			output.push_back(n->data);
		});

		Assert::AreEqual(expected.size(), output.size(), L"Sizes of expected and output vectors must be same");
		for (std::size_t i = 0; i < expected.size(); ++i)
		{
			Assert::AreEqual(expected[i], output[i], L"Elements must be equal");
		}
	}

	TEST_CLASS(avl)
	{
	public:
		TEST_METHOD(search_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			Assert::AreEqual(true, avl.search(0));
			Assert::AreEqual(true, avl.search(6));
			Assert::AreEqual(false, avl.search(-6));
			Assert::AreEqual(false, avl.search(7));
		}

		TEST_METHOD(successor_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			for (std::size_t i = 0; i < data.size() - 1; ++i)
			{
				const auto successor_node = avl.successor(i);
				Assert::AreEqual(static_cast<int>(i + 1), successor_node->data);
			}

			if (avl.successor(data[data.size() - 1]) != nullptr)
			{
				Assert::Fail(L"Successor of the greatest element exists");
			}
		}

		TEST_METHOD(predecessor_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			for (int i = data.size() - 1; i > 0; --i)
			{
				const auto predecessor_node = avl.predecessor(i);
				Assert::AreEqual(i - 1, predecessor_node->data);
			}

			if (avl.predecessor(data[data.size() >> 1]) != nullptr)
			{
				Assert::Fail(L"Predecessor of the least element exists");
			}
		}

		TEST_METHOD(lineage_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };
			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
				do_lineage_test(avl);
			}
		}
	};

	TEST_CLASS(avl_node_removal)
	{
		TEST_METHOD(lineage_test_remove_node)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			for (auto item : data)
			{
				do_lineage_test(avl);
				avl.remove(item);
			}
		}

		TEST_METHOD(remove_left_leaf_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const auto key = 4;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_node_with_2_children_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::avl<float> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const float key = 5;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_internal_node_with_successor_as_leaf_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6, 5.5 };

			ds::bin_tree::avl<float> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const float key = 5;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_internal_node_with_immediate_successor_test)
		{
			std::vector<float> data{ 3, 1, 5, 0, 2, 4, 6, 7 };

			ds::bin_tree::avl<float> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const float key = 5;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_internal_node_with_successor_having_subtree_test)
		{
			std::vector<double> data{ 3, 1, 5, 0, 2, 4, 6, 5.5, 5.9 };

			ds::bin_tree::avl<double> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const double key = 5;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_right_leaf_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const auto key = 6;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_root_node_test)
		{
			std::vector<int> data{ 3, 1, 5, 0, 2, 4, 6 };

			ds::bin_tree::avl<int> avl;
			for (auto item : data)
			{
				avl.insert(item);
			}

			const auto key = 3;
			do_remove_test(avl, key, data);
			do_lineage_test(avl);
		}
	};

	TEST_CLASS(sequence)
	{
		TEST_METHOD(remove_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (std::size_t j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::avl<int> avl;
				for (auto item : data)
				{
					avl.insert(item);
				}

				const auto key = data_queue[j];
				do_remove_test(avl, key, data);
			}
		}

		TEST_METHOD(find_min_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (std::size_t j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::avl<int> avl;
				for (auto item : data)
				{
					avl.insert(item);
				}

				Assert::AreEqual(*min_element(data.begin(), data.end()), avl.find_min()->data);
			}
		}

		TEST_METHOD(find_max_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (std::size_t j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::avl<int> avl;
				for (auto item : data)
				{
					avl.insert(item);
				}

				Assert::AreEqual(*max_element(data.begin(), data.end()), avl.find_max()->data);
			}
		}

		TEST_METHOD(search_sequence_test)
		{
			std::vector<int> data_queue{ 3, 1, 5, 0, 2, 4, 6 };
			for (std::size_t j = 0; j < data_queue.size(); ++j)
			{
				std::vector<int> data(data_queue.begin() + j, data_queue.end());
				ds::bin_tree::avl<int> avl;
				for (auto item : data)
				{
					avl.insert(item);
				}

				for (const auto& item : data)
				{
					Assert::AreEqual(true, avl.search(item));
				}
			}
		}
	};

	TEST_CLASS(random_data)
	{
		TEST_METHOD(benchmark_insertion)
		{
			const auto data_size = 1000000;
			const auto seed = static_cast<unsigned>(time(nullptr));

			// Log the seed
			auto msg = "Seed: " + std::to_string(seed);
			Logger::WriteMessage(msg.c_str());

			srand(seed);
			ds::bin_tree::avl<int> avl;
			std::set<int> avl_set;
			for (std::size_t i = 0; i < data_size; ++i)
			{
				auto x = rand();
				avl.insert(x);
				//avl_set.insert(x);
			}
		}

		TEST_METHOD(inorder_test)
		{
			const auto data_size = 100000;
			const auto seed = static_cast<unsigned>(time(nullptr));

			// Log the seed
			auto msg = "Seed: " + std::to_string(seed);
			Logger::WriteMessage(msg.c_str());

			srand(seed);

			std::vector<int> data;
			for (std::size_t i = 0; i < data_size; ++i)
			{
				data.push_back(rand());
			}

			ds::bin_tree::avl<int> avl;
			for (auto& item : data)
			{
				avl.insert(item);
			}

			do_inorder_test(avl, data);
			do_lineage_test(avl);
		}

		TEST_METHOD(remove_random_test)
		{
			const auto data_size = 1000;
			const auto seed = static_cast<unsigned>(time(nullptr));

			// Log the seed
			auto msg = "Seed: " + std::to_string(seed);
			Logger::WriteMessage(msg.c_str());

			srand(seed);

			std::vector<int> data;
			for (std::size_t i = 0; i < data_size; ++i)
			{
				data.push_back(rand());
			}

			ds::bin_tree::avl<int> avl;
			for (auto& item : data)
			{
				avl.insert(item);
			}

			// Remove random nodes until the tree is empty
			while (!data.empty())
			{
				const auto rand_idx = rand() % data.size();
				Assert::IsTrue(avl.remove(data[rand_idx]), L"Element must be present in the tree");
				data.erase(data.begin() + rand_idx);
				do_inorder_test(avl, data);
				do_lineage_test(avl);
			}
		}
	};
}