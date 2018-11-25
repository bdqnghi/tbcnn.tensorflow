#include "levenshtein.hpp"

#include <vector>
#include <memory>




int levenshtein(const std::string& string1, const std::string& string2, int w, int s, int a, int d)
{
	const std::size_t len1 = string1.size();
	const std::size_t len2 = string2.size();
	
	using array_t = std::vector<int>;
	using array_ptr_t = std::shared_ptr<array_t>;

	array_ptr_t guard0 = std::make_shared<array_t>(len2 + 1);
	auto row0 = &(*guard0)[0];
	array_ptr_t guard1 = std::make_shared<array_t>(len2 + 1);
	auto row1 = &(*guard1)[0];
	array_ptr_t guard2 = std::make_shared<array_t>(len2 + 1);
	auto row2 = &(*guard2)[0];

	for (auto j = 0u; j <= len2; j++)
	{
		row1[j] = j * a;
	}

	for (auto i = 0u; i < len1; i++)
	{
		row2[0] = (i + 1) * d;
		for (auto j = 0u; j < len2; j++)
		{
			
			row2[j + 1] = row1[j] + s * (string1[i] != string2[j]);

			
			if (i > 0 && j > 0 && string1[i - 1] == string2[j]
				&& string1[i] == string2[j - 1]
				&& row2[j + 1] > row0[j - 1] + w)
			{
				row2[j + 1] = row0[j - 1] + w;
			}

			
			if (row2[j + 1] > row1[j + 1] + d)
			{
				row2[j + 1] = row1[j + 1] + d;
			}

			
			if (row2[j + 1] > row2[j] + a)
			{
				row2[j + 1] = row2[j] + a;
			}
		}

		const auto dummy = row0;
		row0 = row1;
		row1 = row2;
		row2 = dummy;
	}

	const auto result = row1[len2];

	return result;
}


