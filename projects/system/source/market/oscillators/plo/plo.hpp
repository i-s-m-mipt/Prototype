#ifndef SOLUTION_SYSTEM_MARKET_OSCILLATORS_PLO_HPP
#define SOLUTION_SYSTEM_MARKET_OSCILLATORS_PLO_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#  pragma once
#endif // #ifdef BOOST_HAS_PRAGMA_ONCE

#include "../oscillators.hpp"

namespace solution
{
	namespace system
	{
		namespace market
		{
			namespace oscillators
			{
				class PLO
				{
				public:

					explicit PLO(std::size_t timesteps) : m_timesteps(timesteps)
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

			} // namespace oscillators

		} // namespace market

	} // namespace system

} // namespace solution

#endif // #ifndef SOLUTION_SYSTEM_MARKET_OSCILLATORS_PLO_HPP