#include "model/vehicle.hpp"

namespace model
{

float Vehicle::cost_per_kg() { return cost / weight; }

string Vehicle::to_string()
{
    string str = "<Vehicle " + brand + " cost: " + ::to_string(cost) + ">";
    return str;
}

} // namespace model
