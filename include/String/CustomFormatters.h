#pragma once

#include <format>
#include <vector>
#include <array>

// TODO: Remove this when range formatting is supported

// std::vector<T> formatter (until range formatting is supported)
template <typename T, typename CharT>
struct std::formatter<std::vector<T>, CharT>
{
	constexpr auto parse(std::basic_format_parse_context<CharT>& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const std::vector<T>& range, FormatContext& ctx) const
	{
		std::string elements;
		for (const auto& itr : range)
			elements += std::format("{}, ", itr);

		if (range.size() > 0)
		{
			elements.pop_back();
			elements.pop_back();
		}

		return std::format_to(ctx.out(), "({})", elements);
	}
};


// std::array<T, _Size> formatter (until range formatting is supported)
template <typename T, size_t _Size, typename CharT>
struct std::formatter<std::array<T, _Size>, CharT>
{
	constexpr auto parse(std::basic_format_parse_context<CharT>& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const std::array<T, _Size>& range, FormatContext& ctx) const
	{
		std::string elements;
		for (const auto& itr : range)
			elements += std::format("{}, ", itr);

		if (range.size() > 0)
		{
			elements.pop_back();
			elements.pop_back();
		}

		return std::format_to(ctx.out(), "({})", elements);
	}
};
