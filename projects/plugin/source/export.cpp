#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

#include <qluacpp/qlua>

#include "market/market.hpp"

#include "../../shared/source/logger/logger.hpp"

namespace solution
{
	namespace plugin
	{
		using Logger = shared::Logger;

		static std::unique_ptr < Market > market_ptr;

		int main(lua_State * state) 
		{
			RUN_LOGGER(logger);

			try
			{
                lua::State s(state);

				Market::api_t api(s);

				market_ptr = std::make_unique < Market > (api);

				market_ptr->run();

                return EXIT_SUCCESS;
			}
			catch (const std::exception & exception)
			{
				logger.write(Logger::Severity::fatal, exception.what());

                return EXIT_FAILURE;
			}
			catch (...)
			{
				logger.write(Logger::Severity::fatal, "unknown exception");

                return EXIT_FAILURE;
			}
		}

	} // namespace plugin

} // namespace solution

extern "C" 
{
	LUALIB_API int luaopen_plugin(lua_State * state_ptr) 
	{
		lua::State state(state_ptr);

        state.register_function("main", solution::plugin::main);

		state.set_global("plugin");

		return EXIT_SUCCESS;
	}
}