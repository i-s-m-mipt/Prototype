#include "cc.hpp"

namespace solution
{
	namespace system
	{
		namespace market
		{
			namespace oscillators
			{
				void CC::initialize() const
				{
					RUN_LOGGER(logger);

					try
					{
						if (m_timesteps == 0U)
						{
							throw std::domain_error("invalid timesteps value");
						}

						if (m_timesteps_long == 0U)
						{
							throw std::domain_error("invalid timesteps long value");
						}

						if (m_timesteps_short == 0U)
						{
							throw std::domain_error("invalid timesteps short value");
						}

						if (m_timesteps_long < m_timesteps_short)
						{
							throw std::domain_error("invalid timesteps long and short values");
						}
					}
					catch (const std::exception & exception)
					{
						shared::catch_handler < oscillator_exception > (logger, exception);
					}
				}

				void CC::operator()(candles_container_t & candles) const
				{
					RUN_LOGGER(logger);

					try
					{
						std::vector < double > rocs;

						rocs.reserve(std::size(candles) - m_timesteps_long);

						for (auto i = m_timesteps_long; i < std::size(candles); ++i)
						{
							rocs.push_back(
								(100.0 * candles[i].price_close / candles[i - m_timesteps_long ].price_close) +
								(100.0 * candles[i].price_close / candles[i - m_timesteps_short].price_close));
						}

						for (auto i = m_timesteps - 1U; i < std::size(rocs); ++i)
						{
							auto value = 0.0;

							for (std::size_t j = i + 1U - m_timesteps, k = 1U; j <= i; ++j, ++k)
							{
								value += rocs[j] * k;
							}

							value /= (m_timesteps * (m_timesteps + 1.0) / 2.0);

							candles[m_timesteps_long + i].indicators.push_back(value);
						}
					}
					catch (const std::exception & exception)
					{
						shared::catch_handler < oscillator_exception > (logger, exception);
					}
				}

			} // namespace oscillators

		} // namespace market

	} // namespace system

} // namespace solution