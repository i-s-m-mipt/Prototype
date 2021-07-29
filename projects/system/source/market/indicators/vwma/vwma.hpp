#ifndef SOLUTION_SYSTEM_MARKET_INDICATORS_VWMA_HPP
#define SOLUTION_SYSTEM_MARKET_INDICATORS_VWMA_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#  pragma once
#endif // #ifdef BOOST_HAS_PRAGMA_ONCE

#include "../indicators.hpp"

namespace solution
{
	namespace system
	{
		namespace market
		{
			namespace indicators
			{
				class VWMA
				{
				public:

					explicit VWMA(std::size_t timesteps) : m_timesteps(timesteps)
					{
						initialize();
					}

				private:

					void initialize() const;

				public:

					void operator()(candles_container_t & candles) const;

				private:

					std::size_t m_timesteps;
				};

			} // namespace indicators

		} // namespace market

	} // namespace system

} // namespace solution

#endif // #ifndef SOLUTION_SYSTEM_MARKET_INDICATORS_VWMA_HPP