#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <type_traits>
#include <string_view>
#include <sstream>
#include <expected>
#include <format>
#include <initializer_list>
#include <algorithm>

#include "../Error/ErrorDef.h"
#include "StringLibImpl/StringLib_impl.h"


namespace ke::type_traits
{
	// yoinked from: https://stackoverflow.com/a/22759544/13091070
	// by: jrok

	template<typename S, typename T>
	class is_streamable
	{
		template<typename SS, typename TT>
		static auto test(int)
			-> decltype(std::declval<SS&>() << std::declval<TT>(), std::true_type());

		template<typename, typename>
		static auto test(...) -> std::false_type;

	public:
		static const bool value = decltype(test<S, T>(0))::value;
	};


	//// yoinked from https://stackoverflow.com/a/72430675

	//template<typename T>
	//concept formattable = requires(T & v, std::format_context ctx)
	//{
	//	std::formatter<std::remove_cvref<T>>().format(v, ctx);
	//} || std::is_fundamental<T>().value || std::formattable<T, std::format_context> || std::is_same_v<T, char*> || std::is_same_v<T, const char*>;
}


namespace ke
{

	template <typename T>
	concept _StringFormattableConcept = requires(const T& a)
	{
		//std::formattable<T, std::format_context>;
		{ std::format("{}", a) };
	};

	template <typename T> 
	concept _StringStreamableFromTConcept = requires (const T& arg)
	{
		//{ std::stringstream{} >> arg } -> std::convertible_to<std::stringstream&>;
		type_traits::is_streamable<std::stringstream, T>::value;
	};


	/**
	 * @brief Converts any FORMATTABLE type to string.
	 * 
	 * @param arg
	 * @return 
	 */
	template <typename T> //requires std::is_convertible_v<T, std::string> || std::formattable<T, std::format_context>
	inline std::string toString(const T& arg) noexcept
	{
		return std::format("{}", arg);
	}

	/**
	 * @brief Converts any FORMATTABLE type to string. Gives error if type is not formattable.
	 * 
	 * @param arg
	 * @return 
	 */
	template <typename T>
	inline auto tryToStringOrError(const T& arg) noexcept -> std::expected<std::string, Error>
	{
		if constexpr (std::formattable<T, char>)
			return toString(arg);
		else
			return std::unexpected(Error::InvalidArgument);
	}

	/**
	 * @brief Converts any type to string. If type is not convertible to string, returns default string.
	 * 
	 * @param arg
	 * @param default_str
	 * @return 
	 */
	template <typename T>
	inline std::string tryToString(const T& arg, const std::string& default_str = "???")
	{
		if constexpr (std::formattable<T, char>)
			return _impl::tryToString_impl(arg, default_str);
		else
			return default_str;
	}



	/**
	 * @brief Converts string to any STREAMABLE type. Uses std::stringstream to convert.
	 * 
	 * @param arg
	 * @return 
	 */
	template <_StringStreamableFromTConcept T>
	inline auto fromString(std::string_view arg) -> std::expected<T, Error>
	{
		//static_assert(_StringStreamableFromTConcept<T>, "Type must be streamable from std::stringstream");

		std::stringstream ss; ss << arg;
		T value{};

		ss >> value;

		if (ss.fail() || ss.bad())
			return std::unexpected(Error::InvalidArgument);

		return value;
	}


	template <>
	inline auto fromString<uint8_t>(std::string_view arg) -> std::expected<uint8_t, Error>
	{
		auto value = fromString<int>(arg);

		if (!value)
			return std::unexpected(value.error());

		if (*value < 0 || *value > std::numeric_limits<uint8_t>::max())
			return std::unexpected(Error::DomainError);

		uint8_t result = value.value();
		return result;
	}


	/**
	 * @brief Converts string to lowercase.
	 * 
	 * @param arg
	 * @param default_value
	 * @return 
	 */
	inline std::string toLower(std::string_view str)
	{
		std::string resoult(str);
		for (char& c : resoult)
			c = std::tolower(c);
		return resoult;
	}

	/**
	 * @brief Converts string reference to lowercase.
	 * 
	 * @param arg
	 * @param default_value
	 * @return 
	 */
	inline std::string toLowerRef(std::string& str)
	{
		for (char& c : str)
			c = std::tolower(c);
		return str;
	}

	/**
	 * @brief Converts string to uppercase.
	 * 
	 * @param arg
	 * @param default_value
	 * @return 
	 */
	inline std::string toUpper(std::string_view str)
	{
		std::string resoult(str);
		for (char& c : resoult)
			c = std::toupper(c);
		return resoult;
	}

	/**
	 * @brief Converts string reference to uppercase.
	 * 
	 * @param arg
	 * @param default_value
	 * @return 
	 */
	inline void toUpperRef(std::string& str)
	{
		for (char& c : str)
			c = std::toupper(c);
	}


	/**
	 * @brief [MSVC ONLY] Cleans type name from type information.
	 * 
	 * @param type_name
	 * @return 
	 */
	inline std::string cleanTypeName(std::string_view type_name)
	{
		std::string resoult(type_name);
		_impl::cleanTypeInfo_impl(resoult);
		return resoult;
	}

	/**
	 * @brief [MSVC ONLY] Cleans type name from type information.
	 * 
	 * @param type_name
	 * @return 
	 */
	inline std::string cleanTypeNameRef(std::string& type_name)
	{
		_impl::cleanTypeInfo_impl(type_name);
		return type_name;
	}

	/**
	 * @brief Shortens string to to specified length adding "..." at the end.
	 * @example: 
	 * "Hello World!", 10 -> "Hello W..."
	 * 
	 * 
	 * @param str
	 * @param length
	 * @return 
	 */
	inline std::string shortenString(std::string_view str, size_t length)
	{
		std::string resoult(str);
		_impl::shortenString_impl(resoult, length);
		return resoult;
	}

	/**
	 * @brief Shortens string to to specified length adding "..." at the end.
	 * @example: 
	 * "Hello World!", 10 -> "Hello W..."
	 * 
	 * 
	 * @param str
	 * @param length
	 * @return 
	 */
	inline std::string shortenStringRef(std::string& str, size_t length)
	{
		_impl::shortenString_impl(str, length);
		return str;
	}


	/**
	 * @brief Splits a string into a vector based on specified delimiters.
	 *
	 * @details
	 * Example:
	 *	text:		"apple,banana,grape;orange | strawberry,"
	 *	delimiters: ",", ";", "|"
	 *	output is {"apple", "banana", "grape", "orange ", " strawberry"}
	 * Notice that ' ' (space) is not considered a delimiter.
	 *
	 * @param str			text to be split
	 * @param delimiters	a set of std::string delimiters. Can be any length
	 *
	 * @return ContainerType<std::string> of separated text. Does not include empty strings
	 */
	template <template <class> class ContainerType, typename... Delims>
	inline auto splitString(std::string_view str, const Delims&... delimiters)
	{
		static_assert((std::is_convertible_v<Delims, std::string> && ...), "All delimiters must be convertible to std::string");

		std::unordered_set<std::string> delims{ std::string(delimiters)... };
		return _impl::splitString_impl<ContainerType<std::string>>(str, delims);
	}


	// template <class ContainterType, typename T>
	// inline auto split(std::ranges::range<T> str, std::initializer_list<T> delimiters)
	// {
	// 	return _impl::splitString_impl<ContainerType>(str, delimiters);
	// }

	template <typename T>
	inline std::vector<T> splitString(std::string_view str, std::initializer_list<std::string> delimiters, std::function<T(std::string)> transformer)
	{
		std::unordered_set<std::string> delimiter_set(delimiters);
		std::vector<std::string> split_result = _impl::splitString_impl<std::vector<std::string>>(str, delimiter_set);
		std::vector<T> output; output.reserve(split_result.size());
		std::ranges::transform(split_result, std::back_inserter(output), transformer);
		return output;
	}


	/**
	 * @brief Splits a string into a vector based on a specified delimiter.
	 *
	 * @details
	 * Example:
	 *	text:		"apple,banana,grape; onion'
	 *	delimiter: ','
	 *	output is {"apple", "banana", "grape; onion"} // Neither ';' nor ' ' (space) are delimiters, so "grape; onion" has not been split
	 *
	 * @param str			text to be split
	 * @param delimiter		delimiter - must be single character
	 *
	 * @return ContainerType<std::string> of separated text. Does not include empty strings
	 */
	template <template <class> class ContainerType>
	inline auto splitString(std::string_view str, char delimiter)
	{
		return _impl::splitString_impl<ContainerType<std::string>>(str, delimiter);
	}

	/**
	 * @brief Splits a string into a pair of strings based on a specified delimiter and delmiter relative position.
	 * 
	 * @tparam ContainerType 	Container with .first, .second members of type std::string. Preferably std::pair<std::string, std::string>
	 * @param str 				text to be split
	 * @param _n 				position of the delimiter. 0 is the first delimiter, 1 is the second, etc. Does nothing if _n is greater than the number of delimiters.
	 * @param delimiter 		delimiter - must be single character
	 * @return ContainerType<std::string, std::string> of separated text. Does not include delimiters.
	 */
	template <template <class, class> class ContainerType>
	inline auto splitStringToPair(std::string_view str, size_t _n, char delimiter)
	{
		return _impl::splitStringToPair_impl<ContainerType<std::string, std::string>>(str, delimiter, _n);
	} 


	template <template <class, class> class ContainerType, typename... Args>
	inline auto splitStringToPair(std::string_view text, size_t split_index = 0, Args&&... delimiters)
    {
		static_assert((std::is_convertible_v<Args, std::string> && ...), "All delimiters must be convertible to std::string");
		std::unordered_set<std::string> delims{ std::string(delimiters)... };

		return _impl::splitStringToPair_impl<ContainerType<std::string, std::string>>(text, delims, split_index);
	}



	/**
	 * @brief Assembles a string from a container of strings using a specified separator.
	 * 
	 * @tparam ContainerType 			Container of strings. Must be a dynamic container of std::string
	 * @param text_partitions 			container of strings
	 * @param separator 				separator between strings
	 * @param delete_last_separator 	true -> last separator is not added
	 * @return std::string 	assembled string. This function does not add any brackets or other characters.
	 */
	template <std::ranges::range ContainerType>
	inline std::string assembleString(const ContainerType& text_partitions, const std::string& separator, bool delete_last_separator = true)
	{
		return _impl::assembleString_impl(text_partitions, separator, delete_last_separator);
	}


	/**
	 * @brief Deletes whitespaces from both ends of a text.
	 *
	 * @details
	 * Example
	 *	"	cats with:	guns "
	 *    ^tab		        ^space and newline
	 *
	 * is trimmed into "cats with:	guns"
	 *
	 * @param str	text to be trimmed
	 * @return		new trimmed text
	 */
	inline std::string trimString(std::string_view str, std::initializer_list<char> whitespaces = { ' ', '\t', '\n' })
	{
		std::string resoult(str);
		_impl::trimString_impl(resoult, whitespaces);
		return resoult;
	}

	/**
	 * @brief Deletes whitespaces from both ends of a text.
	 *
	 * @details
	 * Example
	 *	"	cats with:	guns "
	 *    ^tab		        ^space and newline
	 *
	 * is trimmed into "cats with:	guns"
	 *
	 * @param str	text to be trimmed
	 */
	inline void trimStringByRef(std::string& str, std::initializer_list<char> whitespaces = { ' ', '\t', '\n' })
	{
		_impl::trimString_impl(str, whitespaces);
	}


	/**
	 * @brief Removes "//" comments from the text.
	 *
	 * @details
	 * Example 1:
	 *	for str:			"Hello There! // this is an iconic line"
	 *	is turned into		"Hello There! "
	 *
	 * Example 2:
	 *	for str:			"General Kenobi! \n"
	 *						"// ^ this is an iconic line\n"
	 *						"You are a bold one!"
	 *
	 *	is turned into		"General Kenobi! \n"
	 *						"\n"
	 *						"You are a bold one!"
	 *
	 * As you can see, removing comments leaves whitespaces. Consider using ke::trimString(str) function
	 *
	 *
	 * @param str
	 * @return		new string without comments
	 */
	inline std::string removeComments(std::string_view str)
	{
		std::string resoult(str);
		_impl::removeComments_impl(resoult);
		return resoult;
	}

	/**
	 * @brief Removes "//" comments from the text.
	 *
	 * @details
	 * Example 1:
	 *	for str:			"Hello There! // this is an iconic line"
	 *	is turned into		"Hello There! "
	 *
	 * Example 2:
	 *	for str:			"General Kenobi! \n"
	 *						"// ^ this is an iconic line\n"
	 *						"You are a bold one!"
	 *
	 *	is turned into		"General Kenobi! \n"
	 *						"\n"
	 *						"You are a bold one!"
	 *
	 * As you can see, removing comments leaves whitespaces. Consider using ke::trimString(str) function
	 *
	 * @param str	reference to oryginal string
	 */
	inline void removeCommentsByRef(std::string& str)
	{
		_impl::removeComments_impl(str);
	}


} // namespace ke