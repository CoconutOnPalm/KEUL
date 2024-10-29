#pragma once

#include <print>
#include <map>
#include <memory>
#include <format>
#include <mutex>


#include "LoggerPolicies.h"


namespace ke
{
	namespace _internal
	{
		struct EngineLog;
	}

	class SimpleLogger
	{
	public:

		/**
		 * @brief Logs a message to the std::clog.
		 *
		 * @param layer			LogLayer -> will only log if the layer is above or at the current layer
		 * @param filename		name of the file that called the log function
		 * @param line			number of the line that called the log function
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		static void LogDetailed(LogLayer layer, std::string_view filename, std::string_view line, const std::format_string<Args...> format_str, Args&&... args)
		{
			std::lock_guard lock(m_io_mutex);

			if (layer < GetInstance().m_layer) return; // if the layer is below the current layer, do not log

			std::string location = (!(filename.empty() || line.empty()) ? std::string(filename) + ":" + std::string(line) : std::string(filename) + std::string(line)); // if filename and line are empty, only one of them is present
			auto& logging_policy = GetInstance().m_loggingPolicy;

			std::clog <<
				logging_policy->prefix(layer, location) <<
				logging_policy->header(layer, location) << ke::format(format_str, std::forward<Args>(args)...) <<
				logging_policy->suffix(layer, location) << '\n';
		}

		/**
		 * @brief Logs a message to the std::clog.
		 *
		 * @param layer			LogLayer -> will only log if the layer is above or at the current layer
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		static void Log(LogLayer layer, const std::format_string<Args...> format_str, Args&&... args)
		{
			std::lock_guard lock(m_io_mutex);

			if (layer < GetInstance().m_layer) return; // if the layer is below the current layer, do not log

			std::string location; // leave empty
			auto& logging_policy = GetInstance().m_loggingPolicy;

			std::clog <<
				logging_policy->prefix(layer, location) <<
				logging_policy->header(layer, location) << ke::format(format_str, std::forward<Args>(args)...) <<
				logging_policy->suffix(layer, location) << '\n';
		}


		/**
		 * @brief Logs an info message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void LogInfo(const std::format_string<Args...> format_str, Args&&... args)
		{
			Log(LogLayer::Info, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs a debug message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void LogDebug(const std::format_string<Args...> format_str, Args&&... args)
		{
			Log(LogLayer::Debug, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs a warning message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void LogWarning(const std::format_string<Args...> format_str, Args&&... args)
		{
			Log(LogLayer::Warning, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs an error message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void LogError(const std::format_string<Args...> format_str, Args&&... args)
		{
			Log(LogLayer::Error, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs a critical message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void LogCritical(const std::format_string<Args...> format_str, Args&&... args)
		{
			Log(LogLayer::Critical, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Sets the layer of the logger.
		 *
		 * @param layer	LogLayer
		 */
		static void SetLayer(LogLayer layer)
		{
			std::lock_guard lock(m_io_mutex);
			GetInstance().m_layer = layer;
		}


		/**
		 * @brief Sets the logging policy of the logger.
		 *
		 * @tparam LoggingPolicy	policies::LoggingPolicyBase
		 */
		template <class LoggingPolicy>
		static void SetLoggingPolicy()
		{
			std::lock_guard lock(m_io_mutex);
			GetInstance().m_loggingPolicy = std::make_unique<LoggingPolicy>();
		}


	private:


		// data:

		// std::clog is the default output stream
		LogLayer m_layer = LogLayer::Debug;
		std::unique_ptr<policies::LoggingPolicyBase> m_loggingPolicy = std::make_unique<policies::DefaultLoggingPolicy<FormatAllowAnsiCodes::On>>();

		inline static std::mutex m_io_mutex;


		template <typename... Args>
		static void _EngineLog(LogLayer layer, const std::format_string<Args...> format_str, Args&&... args)
		{
			std::lock_guard lock(m_io_mutex);

			if (layer < GetInstance().m_layer) return; // if the layer is below the current layer, do not log

			auto& logging_policy = GetInstance().m_loggingPolicy;

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

			std::println(std::clog, "{}{}", ke::format("[bold;green][[KENGINE]] {}[[{}]]: ", layerColorFmt, layer), std::format(format_str, std::forward<Args>(args)...));
		}



		// singleton functionality:

		SimpleLogger()
		{
		}

		~SimpleLogger() { m_destroyed = true; }

		SimpleLogger(const SimpleLogger&) = delete;
		SimpleLogger& operator=(const SimpleLogger&) = delete;

		static SimpleLogger& GetInstance()
		{
			static SimpleLogger instance;

			if (instance.m_destroyed)
			{
				OnDeadReference();
				new (&instance) SimpleLogger;
			}

			return instance;
		}

		static void OnDeadReference()
		{
			std::println("[CRITICAL ENGINE ERROR]: dead reference in Logger - Logger is destroyed");
		}

		bool m_destroyed = false; // dead reference check

		friend struct _internal::EngineLog;
	};


	using SLog = SimpleLogger;


#define KE_LOGINFO(format_str, ...) ke::SimpleLogger::LogDetailed(ke::LogLayer::Info, __FILE__, ke::toString(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGDEBUG(format_str, ...) ke::SimpleLogger::LogDetailed(ke::LogLayer::Debug, __FILE__, ke::toString(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGWARNING(format_str, ...) ke::SimpleLogger::LogDetailed(ke::LogLayer::Warning, __FILE__, ke::toString(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGERROR(format_str, ...) ke::SimpleLogger::LogDetailed(ke::LogLayer::Error, __FILE__, ke::toString(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGCRITICAL(format_str, ...) ke::SimpleLogger::LogDetailed(ke::LogLayer::Critical, __FILE__, ke::toString(__LINE__), format_str, ## __VA_ARGS__);


} // namespace ke

