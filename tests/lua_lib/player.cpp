#include "sol/sol.hpp"
#include <iostream>

struct player
{
    player() { std::cout << "test" << std::endl; }
};

extern "C" int luaopen_player(lua_State *L)
{
    sol::state_view lua(L);
    lua.new_usertype<player>("player", sol::constructors<sol::types<>>());
    return (0);
}
