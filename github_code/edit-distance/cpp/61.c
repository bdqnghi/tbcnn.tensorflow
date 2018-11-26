// http://www.spoj.com/problems/EDIST/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	int EditDistance(const string& first, const string& second)
	{
		const string& shorter = (first.length() <= second.length()) ? first : second;
		const string& longer = (first.length() <= second.length()) ? second : first;

		if (shorter.empty()) return longer.length();

		vector<int> prev_i(shorter.length(), 0);
		for (int k = 0; k < prev_i.size(); k++) prev_i[k] = k + 1;

		for (int i = 0; i < longer.length(); i++)
		{
			vector<int> prev_j(shorter.length(), 0);
			prev_j[0] = (shorter[0] == longer[i]) ? i : min(1 + i, 1+prev_i[0]);

			for (int j = 1; j < shorter.length(); j++)
			{
				int cand = 1 + prev_i[j]; // delete char in longer
				cand = min(cand, 1 + prev_j[j-1]); // delete char in shorter

				if (shorter[j] == longer[i]) cand = min(cand, prev_i[j - 1]);
				else cand = min(cand, 1 + prev_i[j - 1]);

				prev_j[j] = cand;
			}
			prev_i = prev_j;
		}
		return prev_i.back();
	}

#if 0
	int main()
	{
		int tests;
		cin >> tests;
		vector<int> results;
		for (int i = 0; i < tests; i++)
		{
			string first, second;
			cin >> first;
			cin >> second;
			results.push_back(EditDistance(first, second));
		}

		for (auto r : results)
			cout << r << endl;

		char q;
		cin >> q;
		return 0;
	}
#endif

	TEST_CLASS(EDIST)
	{
	public:
		TEST_METHOD(BaseCases)
		{
			Assert::AreEqual(0, EditDistance("", ""), L"both empty");
			Assert::AreEqual(0, EditDistance("a", "a"), L"Equal strings");
			Assert::AreEqual(1, EditDistance("a", "b"), L"Different");
		}

		TEST_METHOD(OneStringEmpty)
		{
			Assert::AreEqual(1, EditDistance("a", ""));
			Assert::AreEqual(2, EditDistance("ab", ""));
			Assert::AreEqual(3, EditDistance("", "abc"));
		}

		TEST_METHOD(SameLength_DifferInLastChar)
		{
			Assert::AreEqual(1, EditDistance("abc", "abd"));
		}

		TEST_METHOD(Postfix)
		{
			Assert::AreEqual(2, EditDistance("a", "abd"));
			Assert::AreEqual(4, EditDistance("abd", "abdefgh"));
			Assert::AreEqual(5, EditDistance("abdefghi", "abd"));
		}

		TEST_METHOD(Prefix)
		{
			Assert::AreEqual(2, EditDistance("d", "abd"));
			Assert::AreEqual(3, EditDistance("de", "abcde"));
		}

		TEST_METHOD(Circumfix)
		{
			Assert::AreEqual(2, EditDistance("b", "abd"));
			Assert::AreEqual(5, EditDistance("b", "axbdyz"));
		}

		TEST_METHOD(AllDifferent)
		{
			Assert::AreEqual(7, EditDistance("abcd", "prqstuv"));
		}

		TEST_METHOD(SameStrings)
		{
			Assert::AreEqual(0, EditDistance("prqstuv", "prqstuv"));
		}

		TEST_METHOD(FromSpoj)
		{
			Assert::AreEqual(4, EditDistance("MONEY", "FOOD"));
		}

		TEST_METHOD(ShiftedBlocks)
		{
			Assert::AreEqual(6 + 3, EditDistance("abcdefabcdef", "xyzabcxyzabc"));
			Assert::AreEqual(6 + 3 * 3, EditDistance("abcdefabcdefabcdefabcdef", "xyzabcxyzabcxyzabcxyzabc"));
			Assert::AreEqual(6 + 3 * 4, EditDistance("abcdefabcdefabcdefabcdefabcdef", "xyzabcxyzabcxyzabcxyzabcxyzabc"));
		}

		TEST_METHOD(Cycle)
		{
			Assert::AreEqual(2, EditDistance("ab", "ba"));
			Assert::AreEqual(4, EditDistance("abcd", "cdab"));
			Assert::AreEqual(6, EditDistance("abcdefghijk", "defghijkabc"));
		}

		TEST_METHOD(LongStrings)
		{
			string first = "";
			for (int i = 0; i < 200; i++) first.append("abcdefghij");

			string second = "";
			for (int i = 0; i < 200; i++) second.append("vwxyzabcde");

			Assert::AreEqual(0, EditDistance(first, first));
			Assert::AreEqual(10 + 5*199, EditDistance(first, second));
		}

	};
}
#endif