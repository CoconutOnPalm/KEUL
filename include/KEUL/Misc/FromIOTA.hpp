#pragma once

#include <vector>
#include <ranges>


#include "Assert.hpp"


namespace ke
{
	/**
	 * @brief returns a vector containing std::iota(a, b) elements
	 */
	template <typename valT>
	inline std::vector<valT> iota_to_vec(const size_t a, const size_t b)
	{
		const size_t size = (b > a) ? (b - a) : 0;
		if (size == 0)
			return {};

		std::vector<valT> vec; vec.resize(size);
		const auto iota = std::views::iota(a, b);
		KE_ASSERT(iota.size() == vec.size());
		for (size_t i = 0; i < iota.size(); i++)
		{
			vec[i] = iota[i];
		}
		
		return vec;
	}
}