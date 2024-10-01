#pragma once

#include <string>
#include <map>
#include <print>

#include "../Error/ErrorDef.h"
#include "StringLib.h"
//#include "../Range.h"


namespace ke
{
	enum class FormatAllowAnsiCodes
	{
		On,
		Off
	};

	namespace _impl
	{

		/**
		 * @brief ke::format implementation; formats a string with ANSI codes using [ ] format syntax.
		 */
		template <ke::FormatAllowAnsiCodes allow = ke::FormatAllowAnsiCodes::On, typename... Args>
		std::string format_impl(const std::format_string<Args...> format_str, Args&&... args);

		/**
		 * @brief Interprets ANSI codes from a string and returns the ANSI code string.
		 * 
		 * @param sequece ANSI code string
		 * @return std::expected<std::string, Error> ANSI code string
		 */
		inline auto interpret_ansi_codes(std::string_view sequece) -> std::expected<std::string, Error>;

		/**
		 * @brief Handles special format functions like rgb(a,b,c).
		 * 
		 * @param sequece ANSI code string
		 * @return std::expected<std::string, Error> ANSI code string
		 */
		inline auto handle_special_format_functions(std::string_view sequece) -> std::expected<std::string, Error>;


		inline auto interpret_ansi_codes(std::string_view sequece) -> std::expected<std::string, Error>
		{
			const static std::map<std::string, std::string> ansi_interpreter = {
				{ "reset", "0" },
				{ "0", "0" },

				// MODIFIERS

				{ "bold", "1" },
				{ "b", "1"},
				{ "1", "1" },

				{ "dim", "2" },
				{ "d", "2"},
				{ "faint", "2" },
				{ "f", "2"},
				{ "2", "2" },

				{ "italic", "3" },
				{ "i", "3"},
				{ "3", "3" },

				{ "underline", "4" },
				{ "u", "4"},
				{ "4", "4" },

				{ "blink", "5" },
				{ "5", "5" },

				{ "reverse", "7" },
				{ "rev", "7" },
				{ "7", "7" },

				{ "hidden", "8" },
				{ "hide", "8" },
				{ "8", "8" },

				{ "strikethrough", "9" },
				{ "strike", "9" },
				{ "9", "9"},

				// FOREGROUND COLORS

				{ "black", "30" },
				{ "k", "30"},
				{ "30", "30" },

				{ "red", "31" },
				{ "r", "31" },
				{ "31", "31" },

				{ "green", "32" },
				{ "g", "32" },
				{ "32", "32" },

				{ "yellow", "33" },
				{ "y", "33" },
				{ "33", "33" },

				{ "blue", "34" },
				{ "l", "34" },
				{ "34", "34" },

				{ "magenta", "35" },
				{ "m", "35" },
				{ "35", "35" },

				{ "cyan", "36" },
				{ "c", "36" },
				{ "36", "36" },

				{ "white", "37" },
				{ "w", "37" },
				{ "37", "37" },

				{ "default", "39" },
				{ "def", "39" },
				{ "39", "39"},

				// BRIGHT COLORS

				{ "bblack", "90" },
				{ "bk", "90" },
				{ "brightblack", "90" },
				{ "90", "90" },

				{ "bred", "91" },
				{ "br", "91"},
				{ "brightred", "91" },
				{ "91", "91" },

				{ "bgreen", "92" },
				{ "bg", "92" },
				{ "brightgreen", "92" },
				{ "92", "92" },

				{ "byellow", "93" },
				{ "by", "93" },
				{ "brightyellow", "93" },
				{ "93", "93" },

				{ "bblue", "94" },
				{ "bl", "94"},
				{ "brightblue", "94" },
				{ "94", "94" },

				{ "bmagenta", "95" },
				{ "bm", "95" },
				{ "brightmagenta", "95" },
				{ "95", "95" },

				{ "bcyan", "96" },
				{ "bc", "96" },
				{ "brightcyan", "96" },
				{ "96", "96" },

				{ "bwhite", "97" },
				{ "bw", "97" },
				{ "brightwhite", "97" },
				{ "97", "97" },

				// BACKGROUND COLORS

				{ "bg_black", "40" },
				{ "backblack", "40" },
				{ "40", "40" },

				{ "bg_red", "41" },
				{ "backred", "41"},
				{ "41", "41" },

				{ "bg_green", "42" },
				{ "backgreen", "42"},
				{ "42", "42" },

				{ "bg_yellow", "43" },
				{ "backyellow", "43"},
				{ "43", "43" },

				{ "bg_blue", "44" },
				{ "backblue", "44"},
				{ "44", "44" },

				{ "bg_magenta", "45" },
				{ "backmagenta", "45"},
				{ "45", "45" },

				{ "bg_cyan", "46" },
				{ "backcyan", "46"},
				{ "46", "46" },

				{ "bg_white", "47" },
				{ "backwhite", "47"},
				{ "47", "47"},

				{ "bg_default", "49" },
				{ "backdef", "49"},
				{ "49", "49" },

				// BRIGHT BACKGROUND COLORS

				{ "brightbackblack", "100" },
				{ "bbackblack", "100" },
				{ "bbackk", "100" },
				{ "100", "100" },

				{ "brightbackred", "101" },
				{ "bbackred", "101" },
				{ "bbackr", "101" },
				{ "101", "101" },

				{ "brightbackgreen", "102" },
				{ "bbackgreen", "102" },
				{ "bbackg", "102" },
				{ "102", "102" },

				{ "brightbackyellow", "103" },
				{ "bbackyellow", "103" },
				{ "bbacky", "103" },
				{ "103", "103" },

				{ "brightbackblue", "104" },
				{ "bbackblue", "104" },
				{ "bbackb", "104" },
				{ "104", "104" },

				{ "brightbackmagenta", "105" },
				{ "bbackmagenta", "105" },
				{ "bbackm", "105" },
				{ "105", "105" },

				{ "brightbackcyan", "106" },
				{ "bbackcyan", "106" },
				{ "bbackc", "106" },
				{ "106", "106" },

				{ "brightbackwhite", "107" },
				{ "bbackwhite", "107" },
				{ "bbackw", "107" },
				{ "107", "107" },
			};

			if (sequece.empty())
				return std::unexpected(ke::Error::EmptyArgument);

			if (sequece.front() != '[' || sequece.back() != ']')
			{
				// TODO: log error but without engine logging (circular dependency)
				return std::unexpected(ke::Error::FormatError);
			}

			if (sequece.size() == 2) // "[]"
				return std::unexpected(ke::Error::EmptyArgument);

			ke::Error encountered_error = ke::Error::None;

			std::vector<std::string> codes = ke::splitString<std::vector>(sequece, "[];");

			if (codes.size() == 0)
				return std::unexpected(ke::Error::EmptyArgument);

			for (auto& code : codes)
			{
				ke::toLowerRef(code);
			}

			std::string ansi_str = "\033[";

			for (const auto& code : codes)
			{
				auto it = ansi_interpreter.find(code);

				if (it != ansi_interpreter.end())
				{
					ansi_str += it->second + ";";
				}
				else // try rgb color
				{
					auto special_func = handle_special_format_functions(code);
					if (!special_func) // has error
					{
						encountered_error = special_func.error();
					}
					else
					{
						ansi_str += special_func.value() + ';';
					}
				}
			}

			switch (encountered_error)
			{
			case ke::Error::InvalidArgument:
				return std::unexpected(ke::Error::InvalidArgument);
				break;
			case ke::Error::FormatError:
				return std::unexpected(ke::Error::FormatError);
				break;
			case ke::Error::None:
				// no error
				break;
			default:
				return std::unexpected(ke::Error::UnexpectedError);
				break;
			}

			if (ansi_str.back() == ';')
				ansi_str.pop_back();

			ansi_str += "m";
			return ansi_str;
		}

		inline auto handle_special_format_functions(std::string_view sequece) -> std::expected<std::string, Error>
		{
			if (sequece.empty())
				return std::unexpected(ke::Error::EmptyArgument);

			if (sequece.size() >= 10)
			{
				// try rgb(a,b,c)
				auto partitions = ke::splitString<std::vector>(sequece, "(), ");
				if (partitions.size() == 4) // "rgb", "a", "b", "c"
				{
					if (partitions.front() == "rgb")
					{
						auto r = ke::fromString<uint32_t>(partitions[1]);
						auto g = ke::fromString<uint32_t>(partitions[2]);
						auto b = ke::fromString<uint32_t>(partitions[3]);

						if (!(r && g && b))
							return std::unexpected(ke::Error::FormatError);

						if (*r > 255 || *g > 255 || *b > 255)
							return std::unexpected(ke::Error::DomainError);

						return std::format("38;2;{};{};{}", r.value(), g.value(), b.value());
					}
				}
			}

			return std::unexpected(ke::Error::InvalidArgument);
		}

		template <ke::FormatAllowAnsiCodes allow_ansi, typename... Args>
		std::string format_impl(const std::format_string<Args...> format_str, Args&&... args)
		{
			std::string str = std::format(format_str, std::forward<Args>(args)...);

			int bracket_tracker = 0;
			size_t double_bracket_count = 0;
			for (size_t i = 0; i < str.size(); i++)
			{
				if (str[i] == '[')
				{

					if (i + 1 >= str.size())
					{
						// don't log error: missing closing bracket may be user's format string argument
						return str;
					}

					else if (str[i + 1] == '[') // [[ -> treat as a single bracket
					{
						i++;
						double_bracket_count++;
						continue;
					}
					else
					{
						bracket_tracker++;
						size_t closing_bracket_index = 0;
						size_t internal_bracket_tracker = 0;

						// search for closing bracket
						for (size_t j = i + 1; j < str.size(); j++)
						{
							if (str[j] == '[')
							{
								internal_bracket_tracker++;
							}
							else if (str[j] == ']')
							{
								if (j + 1 >= str.size() && internal_bracket_tracker == 0)
								{
									closing_bracket_index = j;
									bracket_tracker--;
									//internal_bracket_tracker--;
									break;
								}
								else if (str[j + 1] == ']') // ]] -> treat as a single bracket
								{
									if (str.size() > j + 2 && str[j + 2] == ']') // ]]] -> treat the last two as a single bracket
									{
										closing_bracket_index = j;
										bracket_tracker--;
										break;
									}

									j++;
									double_bracket_count++;
									continue;
								}
								else if (internal_bracket_tracker == 0)
								{
									closing_bracket_index = j;
									bracket_tracker--;
									break;
								}
								else
								{
									// bracket missing -> possibly bracket inside bracket, but it works so I'll leave it
									continue;
								}
							}
						}

						if (closing_bracket_index != 0)
						{
							auto ansi_code = _impl::interpret_ansi_codes(str.substr(i, closing_bracket_index - i + 1));
							if (!ansi_code) // has error
							{
								switch (ansi_code.error())
								{
								case Error::FormatError:
									// TODO: log error because something is DEFINITELY broken (without engine logging - circular dependency)
									std::println("format(...): Format error on closing bracket search");
									break;
								case Error::InvalidArgument:
									// don't log error: invalid ansi code may be format string argument (without engine logging - circular dependency)
									break;
								case Error::EmptyArgument:
									// don't log error: empty ansi code may be format string argument (without engine logging - circular dependency)
									break;
								default:
									// panic
									std::println("format(...): Unexpected error on closing bracket search");
									break;
								}
								// don't log error: invalid ansi code may be format string argument
								i = closing_bracket_index;
								continue;
							}
							else
							{
								if (allow_ansi == FormatAllowAnsiCodes::On)
								{
									str.replace(i, closing_bracket_index - i + 1, ansi_code.value());
									i += ansi_code.value().size() - 1;
								}
								else
								{
									str.erase(i, closing_bracket_index - i + 1);
									i--; // erased -> don't increment
								}
								
							}
						}
						else if (closing_bracket_index == 0 && bracket_tracker != 0)
						{
							// don't log error: missing closing bracket may be user's format string argument
							break;
						}
					}
				}
				else if (str[i] == ']')
				{
					if (i + 1 < str.size() && str[i + 1] == ']')
					{
						i++;
						double_bracket_count++;
					}
					else
					{
						// TODO: log error: missing opening bracket
						continue;
					}
				}
			}

			if (bracket_tracker != 0)
			{
				// TODO: log error: invalid bracket count
				if (allow_ansi == FormatAllowAnsiCodes::On)
					str += "\033[0m"; // reset ansi codes
				return str;
			}

			// replace [[]] with []
			if (double_bracket_count > 0)
			{
				std::string new_str;
				new_str.reserve(str.size() - double_bracket_count);
				for (size_t i = 0; i < str.size(); i++)
				{
					if (str[i] == '[' && i + 1 < str.size() && str[i + 1] == '[')
					{
						new_str += '[';
						i++;
					}
					else if (str[i] == ']' && i + 1 < str.size() && str[i + 1] == ']')
					{
						new_str += ']';
						i++;
					}
					else
					{
						new_str += str[i];
					}
				}

				str = new_str;
			}

			if (allow_ansi == FormatAllowAnsiCodes::On)
				str += "\033[0m"; // reset ansi codes

			return str;
		}
	}
}
