#pragma once

#include "Clock.hpp"

#ifdef _MSC_VER
#pragma execution_character_set( "utf-8" )
#endif

namespace ke
{
	/**
	 * @brief Class for simple and fast real-time benchmarking based on std::chrono library.
	 */
	class Benchmark
	{
	protected:

		Clock m_clock;

		std::string m_name;
		bool m_is_running;


	public:

		Benchmark(TimeUnit unit = TimeUnit::microseconds)
			: m_clock(unit)
			, m_name("Benchmark")
			, m_is_running(true)
		{
			m_clock.start();
		}

		/**
		 * @brief WARNING: Starts benchmark automatically
		 * @param name	Name of the instance. Useful for printing resolts.
		 */
		Benchmark(const std::string& name, TimeUnit unit = TimeUnit::microseconds)
			: m_clock(unit)
			, m_name(name)
			, m_is_running(true)
		{
			m_clock.start();
		}


		virtual ~Benchmark()
		{
			if (!m_is_running)
				return;

			auto val = m_clock.stop();

			std::println("{}: {}", m_name, m_clock);
		}

		/**
		 * @brief Starts benchmarking clock. If the clock is already running, it overrides the previous time
		 */
		void start()
		{
			m_is_running = true;
			m_clock.start();
		}

		/**
		 * @brief Stops the measurement.
		 *
		 * @param print		true -> the results are printed (in microseconds)
		 * @return Elapsed time (in microseconds)
		 */
		long double stop(bool print = false)
		{
			auto val = m_clock.stop();
			m_is_running = false;

			if (print)
			{
				std::println("{}: {}", m_name, m_clock);
			}

			return val;
		}
	};


} // namespace ke


