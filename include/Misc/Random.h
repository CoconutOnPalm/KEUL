#pragma once

#include <random>
#include <vector>
#include "Range.h"


namespace ke
{
	/**
	 * @brief Class for easy and simple random number generation.
	 */
	class Random
	{
	public:

		
        /**
		* @brief Default constructor for the Random class. Generates a random seed using std::random_device.
        */
        Random() { m_engine.seed(m_seed_generator()); };

        /**
        * @brief Constructor for the Random class with a custom seed.
        *
        * @param seed The seed value for the random number generator.
        */
        Random(unsigned int seed) { m_engine.seed(seed); };

        /**
        * @brief Copies std::default_random_engine from the other generator.
        *
        * @param other The Random object to be copied.
        */
        Random(const Random& other) { m_engine = other.m_engine; };

        /**
        * @brief Copies std::default_random_engine from the other generator.
        *
        * @param other The Random object to be assigned.
        * @return A reference to the assigned Random object.
        */
        Random& operator=(const Random& other) 
		{ 
			m_engine = other.m_engine; 
			return *this; 
		};

		~Random() = default;

		/**
		 * @brief Returns random integer within [lowerb, upperb] range.
		 *
		 * @details
		 * This function utilizes std::uniform_int_distribution<int> with std::default_random_engine to produce output
		 * 
		 * \param lowerb	lower bound
		 * \param upperb	upper bound
		 * \return Random integer within [lowerb, upperb] range.
		 */
		int32_t Int32(int32_t lowerb, int32_t upperb)
		{
			std::uniform_int_distribution<int32_t> integer_distributor(lowerb, upperb);
			return integer_distributor(m_engine);
		}

		/**
		 * @brief Returns random 64-bit integer within [lowerb, upperb] range.
		 *
		 * @details
		 * This function utilizes std::uniform_int_distribution<int64_t> with std::default_random_engine to produce output
		 * 
		 * \param lowerb	lower bound
		 * \param upperb	upper bound
		 * \return Random 64-bit integer within [lowerb, upperb] range.
		 */
		int64_t Int64(int64_t lowerb, int64_t upperb)
		{
			std::uniform_int_distribution<int64_t> integer_distributor(lowerb, upperb);
			return integer_distributor(m_engine);
		}

		/**
		 * @brief Returns random uint64_t integer within [lowerb, upperb] range.
		 *
		 * @details
		 * This function utilizes std::uniform_int_distribution<uint64_t> with std::default_random_engine to produce output
		 * 
		 * \param lowerb	lower bound
		 * \param upperb	upper bound
		 * \return Random uint64_t integer within [lowerb, upperb] range.
		 */
		uint64_t UInt64(uint64_t lowerb, uint64_t upperb)
		{
			std::uniform_int_distribution<uint64_t> integer_distributor(lowerb, upperb);
			return integer_distributor(m_engine);
		}

		/**
		 * @brief Returns random character within [lowerb, upperb] range.
		 *
		 * @details
		 * This function utilizes std::uniform_int_distribution<short> with std::default_random_engine to produce output
		 * Example: ke::Random::Char(a, z) gives random character from a to z
		 * 
		 * \param lowerb	lower bound
		 * \param upperb	upper bound
		 * \return Random character within [lowerb, upperb] range.
		*/
		char Char(char lowerb, char upperb)
		{
			std::uniform_int_distribution<short> integer_distributor(static_cast<short>(lowerb), static_cast<short>(upperb));
			return static_cast<char>(integer_distributor(m_engine));
		}

		/**
		 * @brief Returns random double within [lowerb, upperb] range.
		 *
		 * @details
		 * This function utilizes std::uniform_real_distribution<double> with std::default_random_engine to produce output
		 * 
		 * \param lowerb	lower bound
		 * \param upperb	upper bound
		 * \return Random double within [lowerb, upperb] range.
		 */
		double Double(double lowerb, double upperb)
		{
			std::uniform_real_distribution<double> double_distributor(lowerb, upperb);
			return double_distributor(m_engine);
		}

		/**
		 * @brief Returns random float within [lowerb, upperb] range.
		 *
		 * @details
		 * This function utilizes std::uniform_real_distribution<float> with std::default_random_engine to produce output
		 *
		 * \param lowerb	lower bound
		 * \param upperb	upper bound
		 * \return Random double within [lowerb, upperb] range.
		 */
		float Float(float lowerb, float upperb)
		{
			std::uniform_real_distribution<float> double_distributor(lowerb, upperb);
			return double_distributor(m_engine);
		}

		/**
		 * @brief Genrates string of random characters within defined range(s).
		 * 
		 * \param lenght		Length of the string
		 * \param ...ranges		ke::ClosedRange<char>. Every character is generated from 
		 * \return 
		 */
		template<typename... ke_ranges>
		std::string String(size_t lenght, ke_ranges... ranges)
		{
			std::vector<ClosedRange<char>> pairs = { static_cast<ClosedRange<char>>(ranges)... };

			// if no arguments provided, generate text from all printable characters (from ! to ~)
			if (pairs.empty())
				pairs.emplace_back(ClosedRange('!', '~'));

			std::string output;
			output.reserve(lenght);

			for (int i = 0; i < lenght; i++)
			{
				int selected_range = Int32(0, static_cast<int>(pairs.size()) - 1);
				output += Char(pairs[selected_range].a, pairs[selected_range].b);
			}

			return output;
		}


		/**
 		* @brief Returns true by chance, base on <percentage>. See details to know how it works
 		* 
 		* @details
 		* draws a number between 0 and 1 (treat it as %) and if value is below the <percent>, returns true.
 		* Example:
 		*	Imagine you want to toss a coin. Then, you can simulate that by calling ke::Chance(0.5), so it returns true 50% of the time
 		* 
 		* \param percent
 		* \return 
 		*/
		bool Chance(float percent)
		{
			return ClosedRange(0.f, percent).contains(Float(0, 1));
		}


		/**
		 * @brief Sets custom seed for random number generator
		 * 
		 * \param seed
		 */
		void SetSeed(unsigned int seed)
		{
			m_engine.seed(seed);
		}


	private:

		std::random_device m_seed_generator;
		std::default_random_engine m_engine;
	};

} // namespace ke
