#pragma once

#include "../Logging/SimpleLogger.hpp"

namespace ke
{
	namespace _internal
	{
		struct EngineLog
		{
			template <typename... Args>
			inline static void debug(const std::format_string<Args...> format_str, Args&&... args)
			{
				ke::SimpleLogger::_engine_log(ke::LogLayer::Debug, format_str, std::forward<Args>(args)...);
			}

			template <typename... Args>
			inline static void info(const std::format_string<Args...> format_str, Args&&... args)
			{
				ke::SimpleLogger::_engine_log(ke::LogLayer::Info, format_str, std::forward<Args>(args)...);
			}

			template <typename... Args>
			inline static void warning(const std::format_string<Args...> format_str, Args&&... args)
			{
				ke::SimpleLogger::_engine_log(ke::LogLayer::Warning, format_str, std::forward<Args>(args)...);
			}

			template <typename... Args>
			inline static void error(const std::format_string<Args...> format_str, Args&&... args)
			{
				ke::SimpleLogger::_engine_log(ke::LogLayer::Error, format_str, std::forward<Args>(args)...);
			}

			template <typename... Args>
			inline static void critical(const std::format_string<Args...> format_str, Args&&... args)
			{
				ke::SimpleLogger::_engine_log(ke::LogLayer::Critical, format_str, std::forward<Args>(args)...);
			}
		};
	}
}

