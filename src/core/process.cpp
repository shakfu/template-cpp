#include "core/process.hpp"

#include <iostream>

namespace core
{

void Process::report(model::Vehicle v)
{
    std::cout << "Vehicle report:" << std::endl;
    std::cout << v.cost_per_kg() << std::endl;
    std::cout << v.to_string() << std::endl;
}

} // namespace core