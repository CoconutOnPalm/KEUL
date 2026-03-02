#pragma once

#include <print>
#include <map>
#include <memory>
#include <format>
#include <mutex>


#include "LoggerPolicies.hpp"


namespace ke
{
	namespace _internal
	{
		struct EngineLog;
	}

	class SimpleLogger
	{
	private:

		LogLayer m_layer = LogLayer::Debug;
		std::unique_ptr<policies::LoggingPolicyBase> m_logging_policy = std::make_unique<policies::DefaultLoggingPolicy>();

		inline static std::mutex m_io_mutex;


	public:

		/**
		 * @brief Logs a message to the stderr (std::clog).
		 *
		 * @param layer			LogLayer -> will only log if the layer is above or at the current layer
		 * @param filename		name of the file that called the log function
		 * @param line			number of the line that called the log function
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		static void log_detailed(LogLayer layer, std::string_view filename, std::string_view line, const std::format_string<Args...> format_str, Args&&... args)
		{
			std::lock_guard lock(m_io_mutex);

			if (layer < get_instance().m_layer) return; // if the layer is below the current layer, do not log

			std::string location = (!(filename.empty() || line.empty()) ? std::string(filename) + ":" + std::string(line) : std::string(filename) + std::string(line)); // if filename and line are empty, only one of them is present
			auto& logging_policy = get_instance().m_logging_policy;

			std::println(std::clog, "{0}{1}{2}{3}",
				logging_policy->prefix(layer, location),
				logging_policy->header(layer, location),
				ke::format(format_str, std::forward<Args>(args)...),
				logging_policy->suffix(layer, location));
		}

		/**
		 * @brief Logs a message to the stderr (std::clog).
		 *
		 * @param layer			LogLayer -> will only log if the layer is above or at the current layer
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		static void log(LogLayer layer, const std::format_string<Args...> format_str, Args&&... args)
		{
			std::lock_guard lock(m_io_mutex);

			if (layer < get_instance().m_layer) return; // if the layer is below the current layer, do not log

			std::string location; // leave empty
			auto& logging_policy = get_instance().m_logging_policy;

			std::println(std::clog, "{0}{1}{2}{3}",
				logging_policy->prefix(layer, location),
				logging_policy->header(layer, location),
				ke::format(format_str, std::forward<Args>(args)...),
				logging_policy->suffix(layer, location));
			/*std::clog <<
				logging_policy->prefix(layer, location) <<
				logging_policy->header(layer, location) << ke::format(format_str, std::forward<Args>(args)...) <<
				logging_policy->suffix(layer, location) << '\n';*/
		}


		/**
		 * @brief Logs an info message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void log_info(const std::format_string<Args...> format_str, Args&&... args)
		{
			log(LogLayer::Info, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs a debug message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void log_debug(const std::format_string<Args...> format_str, Args&&... args)
		{
			log(LogLayer::Debug, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs a warning message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void log_warning(const std::format_string<Args...> format_str, Args&&... args)
		{
			log(LogLayer::Warning, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs an error message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void log_error(const std::format_string<Args...> format_str, Args&&... args)
		{
			log(LogLayer::Error, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Logs a critical message to the std::clog.
		 *
		 * @param format_str	std::format string
		 * @param ...args		std::format args
		 */
		template <typename... Args>
		inline static void log_critical(const std::format_string<Args...> format_str, Args&&... args)
		{
			log(LogLayer::Critical, format_str, std::forward<Args>(args)...);
		}

		/**
		 * @brief Sets the layer of the logger.
		 *
		 * @param layer	LogLayer
		 */
		static void set_layer(LogLayer layer)
		{
			std::lock_guard lock(m_io_mutex);
			get_instance().m_layer = layer;
		}


		/**
		 * @brief Sets the logging policy of the logger.
		 *
		 * @tparam LoggingPolicy	policies::LoggingPolicyBase
		 */
		template <class LoggingPolicy>
		static void set_logging_policy()
		{
			std::lock_guard lock(m_io_mutex);
			get_instance().m_logging_policy = std::make_unique<LoggingPolicy>();
		}


	private:


		template <typename... Args>
		static void _engine_log(LogLayer layer, const std::format_string<Args...> format_str, Args&&... args)
		{
			std::lock_guard lock(m_io_mutex);

			if (layer < get_instance().m_layer) return; // if the layer is below the current layer, do not log

			std::string layerColorFmt;
			layerColorFmt = _internal::_layer_to_color_fmt(layer);

			std::println(std::clog, "{}{}", ke::format("[bold;green][[KENGINE]] {}[[{}]]: ", layerColorFmt, layer), std::format(format_str, std::forward<Args>(args)...));
		}



		// singleton functionality:

		SimpleLogger()
		{
		}

		~SimpleLogger() { m_destroyed = true; }

		SimpleLogger(const SimpleLogger&) = delete;
		SimpleLogger& operator=(const SimpleLogger&) = delete;

		static SimpleLogger& get_instance()
		{
			static SimpleLogger instance;

			if (instance.m_destroyed)
			{
				on_dead_reference();
				new (&instance) SimpleLogger;
			}

			return instance;
		}

		static void on_dead_reference()
		{
			std::println("[CRITICAL ENGINE ERROR]: dead reference in Logger - Logger is destroyed");
		}

		bool m_destroyed = false; // dead reference check

		friend struct _internal::EngineLog;
	};


#define KE_LOGINFO(format_str, ...) ke::SimpleLogger::log_detailed(ke::LogLayer::Info, __FILE__, ke::to_string(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGDEBUG(format_str, ...) ke::SimpleLogger::log_detailed(ke::LogLayer::Debug, __FILE__, ke::to_string(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGWARNING(format_str, ...) ke::SimpleLogger::log_detailed(ke::LogLayer::Warning, __FILE__, ke::to_string(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGERROR(format_str, ...) ke::SimpleLogger::log_detailed(ke::LogLayer::Error, __FILE__, ke::to_string(__LINE__), format_str, ## __VA_ARGS__);
#define KE_LOGCRITICAL(format_str, ...) ke::SimpleLogger::log_detailed(ke::LogLayer::Critical, __FILE__, ke::to_string(__LINE__), format_str, ## __VA_ARGS__);

#define KE_SETLOGLATER(loglayer) ke::SimpleLogger::set_layer(loglayer);


} // namespace ke

