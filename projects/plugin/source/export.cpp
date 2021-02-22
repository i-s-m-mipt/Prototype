//#define LUA_LIB

//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
//#  define LUA_BUILD_AS_DLL
//#endif // #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>

#include <qluacpp/qlua>

#include "market/market.hpp"

#include "../../shared/source/logger/logger.hpp"

namespace solution
{
	namespace plugin
	{
		using Logger = shared::Logger;

		static struct luaL_Reg functions[] = 
		{
			{ nullptr, nullptr }
		};

		static std::unique_ptr < Market > market_ptr;

		void main(lua::state & state) 
		{
			RUN_LOGGER(logger);

			try
			{
				Market::api_t api(state);

				market_ptr = std::make_unique < Market > (api);

				market_ptr->run();
			}
			catch (const std::exception & exception)
			{
				logger.write(Logger::Severity::fatal, exception.what());
			}
			catch (...)
			{
				logger.write(Logger::Severity::fatal, "unknown exception");
			}
		}

		std::tuple < int > stop(const lua::state & state, lua::entity < lua::type_policy < int > > signal)
		{
			market_ptr.reset();

			return std::make_tuple(int(1));
		}

	} // namespace plugin

} // namespace solution

LUACPP_STATIC_FUNCTION2(main,    solution::plugin::main)
LUACPP_STATIC_FUNCTION3(OnStop,  solution::plugin::stop, int)

extern "C" 
{
	LUALIB_API int luaopen_plugin(lua_State * state_ptr) 
	{
		lua::state state(state_ptr);

		lua::function::main   ().register_in_lua(state, solution::plugin::main);
		lua::function::OnStop ().register_in_lua(state, solution::plugin::stop);

#ifdef LUA53
		lua_newtable(state_ptr);
		luaL_setfuncs(state_ptr, solution::plugin::functions, 0);
		lua_setglobal(state_ptr, "plugin");
#else
		luaL_openlib(state_ptr, "plugin", solution::plugin::functions, 0);
#endif

		return 0;
	}
}