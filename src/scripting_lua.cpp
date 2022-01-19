#include "sol/sol.hpp"
#include <iostream>

#include "core/process.hpp"
#include "model/vehicle.hpp"

struct player
{
    player() { std::cout << "test" << std::endl; }
};

extern "C" int luaopen_app(lua_State *L)
{
    sol::state_view lua(L);

    // vehicle class
    sol::usertype<model::Vehicle> vehicle_type =
        lua.new_usertype<model::Vehicle>("Vehicle",
                                         sol::constructors<sol::types<>>());

    vehicle_type["cost_per_kg"] = &model::Vehicle::cost_per_kg;
    vehicle_type["to_string"] = &model::Vehicle::to_string;
    vehicle_type["cost"] = &model::Vehicle::cost;
    vehicle_type["weight"] = &model::Vehicle::weight;

    // process class
    sol::usertype<core::Process> process_type = lua.new_usertype<core::Process>(
        "Process", sol::constructors<sol::types<>>());

    process_type["report"] = &core::Process::report;

    return (0);
}
