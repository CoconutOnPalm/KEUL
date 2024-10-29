#pragma once

#include "Clock.h"


namespace ke
{
	/**
	 * @brief Class for simple and fast real-time benchmarking based on std::chrono library.
	 */
	class Benchmark
	{
	public:

		Benchmark(Clock::TimeUnit unit = Clock::TimeUnit::microseconds)
			: m_isRunning(true), m_clock(unit), m_name("Benchmark")
		{
			m_clock.start();
		}

		/**
		 * @brief WARNING: Starts benchmark automatically
		 * @param name	Name of the instance. Useful for printing resolts. 
		 */
		Benchmark(const std::string& name, Clock::TimeUnit unit = Clock::TimeUnit::microseconds)
			: m_isRunning(true), m_clock(unit), m_name(name)
		{
			m_clock.start();
		}


		virtual ~Benchmark()
		{
			if (!m_isRunning)
				return;

			auto val = m_clock.stop();

			std::print("{0}: ", m_name);
			m_clock.print(Clock::TimeUnit::microseconds, 3);
		}

		/**
		 * @brief Starts benchmarking clock. If the clock is already running, it overrides the previous time
		 */
		void start()
		{
			m_isRunning = true;
			m_clock.start();
		}

		/**
		 * @brief Stops the measurement.
		 * 
		 * @param print		true -> the results are printed (in microseconds)
		 * @return Elapsed time (in microseconds)
		 */
		long double stop(bool print = true)
		{
			auto val = m_clock.stop();
			m_isRunning = false;

			if (print)
			{
				std::print("{0}: ", m_name);
				m_clock.print(Clock::TimeUnit::microseconds, 3);
			}

			return val;
		}


	protected:

		std::string m_name;

		bool m_isRunning;
		Clock m_clock;
	};


} // namespace ke


