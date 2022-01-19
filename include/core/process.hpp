#ifndef PROLOG_CORE_PROCESS_H
#define PROLOG_CORE_PROCESS_H

#include <string>

#include "model/vehicle.hpp"

using namespace std;


namespace core {

class Process {
    public:
        void report(model::Vehicle v);
};

} // namespace core

#endif // PROLOG_CORE_PROCESS_H
