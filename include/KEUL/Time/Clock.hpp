#pragma once

#include <print>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip> 

#ifdef _MSC_VER
#pragma execution_character_set( "utf-8" )
#endif

namespace ke
{

	/**
	 * @brief Real-time automated clock based on std::chromo::high_resolution_clock.
	 */
	class Clock
	{
	public:

		/**
		 * @brief KEngine replacement for standard chrono time format.
		 */
		enum class TimeUnit
		{
			nanoseconds,
			microseconds,
			miliseconds,
			seconds,
			minutes
		};

		/**
		 * @brief Default constructor - does not start the clock.
		 *
		 * @param unit	time unit (ke::Clock::TimeUnit)
		 */
		Clock(TimeUnit unit = TimeUnit::microseconds)
			: m_unit(unit), m_total_time()
		{
		}

		/**
		 * @brief Starts the clock.
		 */
		void start()
		{
			m_start = std::chrono::high_resolution_clock::now();
		}

		/**
		 * @brief Stops the clock.
		 *
		 * @return Elapsed time
		 */
		long double stop()
		{
			m_stop = std::chrono::high_resolution_clock::now();
			m_total_time = m_stop - m_start;

			switch (m_unit)
			{
			case TimeUnit::nanoseconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count();
				break;
			case TimeUnit::microseconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000.;
				break;
			case TimeUnit::miliseconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000'000.; // I like them numbers
				break;
			case TimeUnit::seconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000'000'000.; // More zeros. The compiler will hold...
				break;
			case TimeUnit::minutes:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 60'000'000'000.; // Kekw (it works somehow)
				break;
			default:
				throw std::invalid_argument("TimeUnit is incorrect");
				break;
			}

			return m_total_time.count();
		}

		/**
		 * @brief Returns .
		 *
		 * @param unit	time format (ke::Clock::TimeUnit)
		 * @return
		 */
		long double getLatestMeasurement(TimeUnit unit = TimeUnit::microseconds) const
		{
			switch (unit)
			{
			case TimeUnit::nanoseconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count();
				break;
			case TimeUnit::microseconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000.;
				break;
			case TimeUnit::miliseconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000'000.;
				break;
			case TimeUnit::seconds:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000'000'000.;
				break;
			case TimeUnit::minutes:
				return std::chrono::duration<long double, std::nano>(m_total_time).count() / 60'000'000'000.;
				break;
			default:
				throw std::invalid_argument("TimeUnit: format is incorrect");
				break;
			}

			return m_total_time.count();
		}

		/**
		 * @brief Returns string representation ("<time> <unit>") of latest measurement. See details for additional info
		 *
		 * @details
		 * String in "<time> <unit>" format, where
		 *	<time> is a floating point converted to std::string with specified precision
		 *	<unit> is suffix based on specified format
		 *
		 * Example:
		 *	let time = 21.37420 miliseconds, precision = 2
		 *	the output string will be "21.37 ms"
		 *
		 * @param unit	time format (ke::Clock::TimeUnit)
		 * @param precision	integer in [0, 6] range - determines number precision
		 * @return ("<time> <unit>"). See details for additional info
		 */
		std::string toString(TimeUnit unit = TimeUnit::microseconds, uint8_t precision = 2) const
		{
			long double duration = 0;
			std::string suffix;

			switch (unit)
			{
			case TimeUnit::nanoseconds:
				duration = std::chrono::duration<long double, std::nano>(m_total_time).count();
				suffix = " ns";
				break;
			case TimeUnit::microseconds:
				duration = std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000.;
				suffix = " µs";
				break;
			case TimeUnit::miliseconds:
				duration = std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000'000.;
				suffix = " ms";
				break;
			case TimeUnit::seconds:
				duration = std::chrono::duration<long double, std::nano>(m_total_time).count() / 1'000'000'000.;
				suffix = " s";
				break;
			case TimeUnit::minutes:
				duration = std::chrono::duration<long double, std::nano>(m_total_time).count() / 60'000'000'000.;
				suffix = " min";
				break;
			default:
				throw std::invalid_argument("TimeUnit: format is incorrect");
				break;
			}

			std::stringstream ss;
			ss << std::fixed << std::setprecision(precision) << duration << suffix;

			return ss.str();
		}


		/**
		 * @brief Prints representation ("<time> <unit>") of latest measurement. See details for additional info.
		 *
		 * @details
		 * String in "<time> <unit>" format, where
		 *	<time> is a floating point converted to std::string with specified precision
		 *	<unit> is suffix based on specified format
		 *
		 * Example:
		 *	let time = 21.37420 miliseconds, precision = 2
		 *	the output will be "21.37 ms"
		 *
		 * @param unit	time format (ke::Clock::TimeUnit)
		 * @param precision	integer in [0, 6] range - determines number precision
		 * @param precision
		 */
		void print(TimeUnit unit = TimeUnit::microseconds, uint8_t precision = 2) const
		{
			std::println("{0}", toString(unit, precision));
		}

	private:

		TimeUnit m_unit;

		std::chrono::duration<long double, std::nano> m_total_time;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start, m_stop;

	};

} // namespace ke