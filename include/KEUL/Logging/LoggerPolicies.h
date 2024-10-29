#pragma once

#include "LoggerDef.h"
#include <chrono>

#include "../String/Format.h"



namespace ke
{

	namespace policies
	{
		/**
		 * @brief Logging policy base class.
		 * @details Log message structure: [prefix] [header] <message> <additional_info> [suffix]
		 */
		struct LoggingPolicyBase
		{
			virtual std::string prefix(LogLayer layer, std::string_view location = "") const = 0;
			virtual std::string header(LogLayer layer, std::string_view location = "") const = 0;
			virtual std::string suffix(LogLayer layer, std::string_view location = "") const = 0;
		};


		template <FormatAllowAnsiCodes AllowAnsiCodes = FormatAllowAnsiCodes::On>
		struct DefaultLoggingPolicy : public LoggingPolicyBase
		{
			std::string prefix(LogLayer layer, std::string_view location = "") const override
			{
				const auto time = std::chrono::system_clock::now();
				return ke::format<AllowAnsiCodes>("[f]{:%Y-%m-%d %X} {}\n", time, location);
			}

			std::string header(LogLayer layer, std::string_view location = "") const override
			{
				std::string layerColorFmt;
				switch (layer)
				{
				case ke::LogLayer::Info:
					layerColorFmt = "[bold;cyan]";
					break;
				case ke::LogLayer::Debug:
					layerColorFmt = "[bold;blue]";
					break;
				case ke::LogLayer::Warning:
					layerColorFmt = "[bold;yellow]";
					break;
				case ke::LogLayer::Error:
					layerColorFmt = "[bold;red]";
					break;
				case ke::LogLayer::Critical:
					layerColorFmt = "[bold;magenta]";
					break;
				default:
					break;
				}

				return ke::format<AllowAnsiCodes>("{}[[{}]]: ", layerColorFmt, layer);
			}

			std::string suffix(LogLayer layer, std::string_view location = "") const override
			{
				return "";
			}
		};

		template <FormatAllowAnsiCodes AllowAnsiCodes = FormatAllowAnsiCodes::On>
		struct CompactLoggingPolicy : public LoggingPolicyBase
		{
			std::string prefix(LogLayer layer, std::string_view location = "") const override
			{
				return "";
			}

			std::string header(LogLayer layer, std::string_view location = "") const override
			{
				std::string layerColorFmt;
				switch (layer)
				{
				case ke::LogLayer::Info:
					layerColorFmt = "[bold;cyan]";
					break;
				case ke::LogLayer::Debug:
					layerColorFmt = "[bold;blue]";
					break;
				case ke::LogLayer::Warning:
					layerColorFmt = "[bold;yellow]";
					break;
				case ke::LogLayer::Error:
					layerColorFmt = "[bold;red]";
					break;
				case ke::LogLayer::Critical:
					layerColorFmt = "[bold;magenta]";
					break;
				default:
					break;
				}

				return ke::format<AllowAnsiCodes>("{}[[{}]]: ", layerColorFmt, layer);
			}

			std::string suffix(LogLayer layer, std::string_view location = "") const override
			{
				return "";
			}
		};

		template <FormatAllowAnsiCodes AllowAnsiCodes = FormatAllowAnsiCodes::On>
		struct BareLoggingPolicy : public LoggingPolicyBase
		{
			std::string prefix(LogLayer layer, std::string_view location = "") const override
			{
				return "";
			}

			std::string header(LogLayer layer, std::string_view location = "") const override
			{
				return "";
			}

			std::string suffix(LogLayer layer, std::string_view location = "") const override
			{
				return "";
			}
		};
	}
}
