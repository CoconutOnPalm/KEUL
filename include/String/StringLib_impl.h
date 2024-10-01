#pragma once

#include <string>
#include <set>

namespace ke
{
	namespace _impl
	{
		/**
		 * @brief Converts a value to a string. If the conversion fails, returns error string.
		 *
		 * @tparam T			Type of the value to be converted to a string
		 *
		 * @param arg			Value to be converted to a string
		 * @param default_str	Default string to be returned if the conversion fails
		 *
		 * @return
		 */
		template <typename T>
		std::string tryToString_impl(const T& arg, const std::string& default_str = "???")
		{
			if constexpr (std::formattable<T, char>)
				return std::format("{}", arg);
			else
			{
				std::stringstream ss; ss << arg;
				T value{};

				ss >> value;

				if (ss.fail())
					return default_str;

				return ss.str();
			}
		}


		/**
		 * @brief removes specified whitespaces from the front and back of a string.
		 *
		 * @example
		 *  str = "  hello world  " aka "\t hello wordl \t\n"
		 *	trimString_impl(str, {' ', '\t', '\n'}): str -> "hello world"
		 *
		 * \param str			Input string. Lines are not trimmed.
		 * \param whitespaces
		 */
		inline void trimString_impl(std::string& str, std::initializer_list<char> whitespaces);

		/**
		 * @brief removes comments from a string. Comments are marked by "//" and end with a newline character.
		 *
		 * @example
		 *  str =
		 *	R""""(
		 *	int main()
		 *	{
		 *		// this is a comment
		 *		return 0;
		 *	}
		 *	)""""
		 * 	removeComments_impl(str): str ->
		 *	R""""(
		 *	int main()
		 *	{
		 *
		 *		return 0;
		 *	}
		 *	)""""
		 *
		 * \param str Input string. Can have multiple lines.
		 */
		inline void removeComments_impl(std::string& str);


		/**
		 * @brief Shortens a string to a specified length. If the string is shorter than the specified length, it is not modified.
		 *
		 * @example
		 *  str = "Hello, World!"
		 *	shortenString_impl(str, 10): str -> "Hello W..."
		 *
		 * \param str			Input string
		 * \param max_length	Maximum length of the string
		 */
		inline void shortenString_impl(std::string& str, size_t max_length)
		{
			if (max_length <= 3 && str.length() > max_length)
			{
				str.clear();
				str = std::string(max_length, '.');
				return;
			}

			if (str.length() > max_length)
			{
				str = str.substr(0, max_length - 3) + "...";
			}
		}


		// WARNING: works only with MSVC compiler
		/**
		 * @brief [MSVC ONLY!]	Cleans type information from a string. Removes "class ", "struct ", "enum ", "union ", "typedef " from the string.
		 *
		 * \param str
		 */
		inline void cleanTypeInfo_impl(std::string& str)
		{
			if (str.empty())
				return;

			size_t find_class = str.find("class ");
			while (find_class != str.npos)
			{
				str.replace(find_class, 6, "");
				find_class = str.find("class ");
			}

			size_t find_struct = str.find("struct ");
			while (find_struct != str.npos)
			{
				str.replace(find_struct, 7, "");
				find_struct = str.find("struct ");
			}

			size_t find_enum = str.find("enum ");
			while (find_enum != str.npos)
			{
				str.replace(find_enum, 5, "");
				find_enum = str.find("enum ");
			}

			size_t find_union = str.find("union ");
			while (find_union != str.npos)
			{
				str.replace(find_union, 6, "");
				find_union = str.find("union ");
			}

			size_t find_typedef = str.find("typedef ");
			while (find_typedef != str.npos)
			{
				str.replace(find_typedef, 8, "");
				find_typedef = str.find("typedef ");
			}
		}


		/**
		 * @brief dynamic_container<std::string>. Examples: std::vector<std::string>, std::list<std::string>
		 */
		template<class Container>
		concept _StringRangeTypeConcept = std::ranges::range<Container const> &&
			std::is_same_v<typename Container::value_type, std::string>&&
			requires(Container& c) {
				{ c.emplace_back("") };
				{ Container({ std::string() }) };
		};

		/**
		 * @brief dynamic_container<std::string>. Examples: std::set<std::string>, std::queue<std::string>
		 */
		template<class Container>
		concept _StringContainerTypeConcept =
			std::is_same_v<typename Container::value_type, std::string>&&
			requires(Container& c) {
				{ c.emplace("") };
				{ Container({ std::string() }) };
		};


		/**
		 * @brief Splits a string into a container based on specified delimiters.
		 *
		 * @details
		 * Example:
		 *	text:		"apple,banana,grape;orange | strawberry,"
		 *	delimiters: ",;"
		 *	output is {"apple", "banana", "grape", "orange | strawberry"} // '|' is not a delimiter, so orange and strawberry have not been split
		 * Notice that ' ' (space) is not considered a delimiter.
		 *
		 *	for single delimiter use ke::splitString(std::string_view, char) function
		 *
		 * @tparam ContainerType	Container type. Must be a dynamic range of std::string (std::vector, std::list, etc.)
		 *
		 * @param text			text to be split
		 * @param delimiters	delimiters - must be single character, not separated by anything. Example: for '.', ';', '|' write ".;|"
		 *
		 * @return ContainerType<std::string> of separated text. Does not include empty strings
		 */
		template<_StringRangeTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, std::string_view delimiters);

		/**
		 * @brief Splits a string into a container based on specified delimiters.
		 *
		 * @details
		 * Example:
		 *	text:		"apple,banana,grape;orange | strawberry,"
		 *	delimiters: ",;"
		 *	output is {"apple", "banana", "grape", "orange | strawberry"} // '|' is not a delimiter, so orange and strawberry have not been split
		 * Notice that ' ' (space) is not considered a delimiter.
		 *
		 *	for single delimiter use ke::splitString(std::string_view, char) function
		 *
		 * @tparam ContainerType	Container type. Must be a dynamic container of std::string (std::set, std::queue, etc.)
		 *
		 * @param text			text to be split
		 * @param delimiters	delimiters - must be single character, not separated by anything. Example: for '.', ';', '|' write ".;|"
		 *
		 * @return ContainerType<std::string> of separated text. Does not include empty strings
		 */
		template<_StringContainerTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, std::string_view delimiters);

		/**
		 * Splits a string into a container based on specified delimiters.
		 *
		 * @details
		 * Example:
		 *	text:		"apple,banana,grape; onion'
		 *	delimiter: ','
		 *	output is {"apple", "banana", "grape; onion"} // Neither ';' nor ' ' (space) are delimiters, so "grape; onion" has not been split
		 *
		 *	for multiple delimiters use ke::splitString(std::string_view, std::string_view) function
		 *
		 * @tparam ContainerType	Container type. Must be a dynamic range of std::string (std::vector, std::list, etc.)
		 *
		 * @param text			text to be split
		 * @param delimiter		delimiter - must be single character
		 *
		 * @return ContainerType<std::string> of separated text. Does not include empty strings
		 */
		template<_StringRangeTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, const char delimiter);

		/**
		 * @brief Generalization of other splitTo... functions. Splits a string into a container based on specified delimiters.
		 *
		 * @details
		 * Example:
		 *	text:		"apple,banana,grape; onion'
		 *	delimiter: ','
		 *	output is {"apple", "banana", "grape; onion"} // Neither ';' nor ' ' (space) are delimiters, so "grape; onion" has not been split
		 *
		 *	for multiple delimiters use ke::splitString(std::string_view, std::string_view) function
		 *
		 * @tparam ContainerType	Container type. Must be a dynamic container of std::string (std::set, std::queue, etc.)
		 *
		 * @param text			text to be split
		 * @param delimiter		delimiter - must be single character
		 *
		 * @return ContainerType<std::string> of separated text. Does not include empty strings
		 */
		template<_StringContainerTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, const char delimiter);



		/**
		 * @brief removes specified whitespaces from the front and back of a string.
		 *
		 * \param str
		 * \param whitespaces
		 */
		inline void trimString_impl(std::string& str, std::initializer_list<char> whitespaces)
		{
			if (str.size() > static_cast<size_t>(std::numeric_limits<int64_t>::max()))
			{
				return;
			}

			int64_t start = 0;
			int64_t count = str.length();

			std::set<char> wsp = whitespaces;

			for (int64_t i = 0; i < static_cast<int64_t>(str.length()); ++i)
			{
				if (wsp.find(str[i]) == wsp.end()) // not a whitespace
				{
					start = i;
					break;
				}
			}

			for (int64_t i = static_cast<int64_t>(str.length() - 1); i > 0; --i)
			{
				if (wsp.find(str[i]) == wsp.end()) // not a whitespace
				{
					count = i + 1 - start;
					break;
				}
			}

			str = str.substr(start, count);
		}

		/**
		 * @brief removes comments from a string. Comments are marked by "//" and end with a newline character.
		 *
		 * \param str
		 */
		inline void removeComments_impl(std::string& str)
		{
			bool is_comment = false;
			size_t comment_start = 0;

			for (size_t i = 0; i < str.length() - 1; ++i)
			{
				if (str[i] == '\n')
				{
					if (is_comment)
					{
						str.erase(comment_start, i - comment_start);
						i = comment_start;
					}
					is_comment = false;
					continue;
				}

				if (is_comment)
					continue;

				if (str[i] == '/' && str[i + 1] == '/') // i + 1 is safe because of the loop condition
				{
					comment_start = i;
					is_comment = true;
					continue;
				}
			}

			if (is_comment)
				str.erase(comment_start, str.length() - comment_start);
		}



		// definitions: 

		template<_StringRangeTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, std::string_view delimiters)
		{
			if (text.empty() || delimiters.empty())
				return ContainerType({ std::string(text) });

			ContainerType output{};

			int start = 0, i = 0;
			for (; i < text.size(); i++)
			{
				// index i hit delimiter
				if (delimiters.find(text[i]) != delimiters.npos)
				{
					if (start != i)
					{
						output.emplace_back(text.begin() + start, text.begin() + i);
					}

					start = i + 1;
				}
			}

			if (start != i)
			{
				output.emplace_back(text.begin() + start, text.begin() + i);
			}

			return output;
		}


		template<_StringContainerTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, std::string_view delimiters)
		{
			if (text.empty() || delimiters.empty())
				return ContainerType({ std::string(text) });

			ContainerType output{};

			int start = 0, i = 0;
			for (; i < text.size(); i++)
			{
				// index i hit delimiter
				if (delimiters.find(text[i]) != delimiters.npos)
				{
					if (start != i)
					{
						output.emplace(text.begin() + start, text.begin() + i);
					}

					start = i + 1;
				}
			}

			if (start != i)
			{
				output.emplace(text.begin() + start, text.begin() + i);
			}

			return output;
		}


		template<_StringRangeTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, const char delimiter)
		{
			if (text.empty())
				return ContainerType({ std::string(text) });

			ContainerType output{};

			int start = 0, i = 0;
			for (; i < text.size(); i++)
			{
				// index i hit delimiter
				if (text[i] == delimiter)
				{
					if (start != i)
					{
						output.emplace_back(text.begin() + start, text.begin() + i);
					}

					start = i + 1;
				}
			}

			if (start != i)
			{
				output.emplace_back(text.begin() + start, text.begin() + i);
			}

			return output;
		}


		template<_StringContainerTypeConcept ContainerType>
		inline auto splitString_impl(std::string_view text, const char delimiter)
		{
			if (text.empty())
				return ContainerType({ std::string(text) });

			ContainerType output{};

			int start = 0, i = 0;
			for (; i < text.size(); i++)
			{
				// index i hit delimiter
				if (text[i] == delimiter)
				{
					if (start != i)
					{
						output.emplace(text.begin() + start, text.begin() + i);
					}

					start = i + 1;
				}
			}

			if (start != i)
			{
				output.emplace(text.begin() + start, text.begin() + i);
			}

			return output;
		}


	} // namespace _impl

} // namespace ke
