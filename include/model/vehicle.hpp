#ifndef PROLOG_MODEL_VEHICLE_H
#define PROLOG_MODEL_VEHICLE_H

#include <string>
using namespace std;

namespace model {

class Vehicle {
    public:

        string brand;
        float cost;
        float weight;
    
        float cost_per_kg();

        string to_string();
};

} // namespace model

#endif // PROLOG_MODEL_VEHICLE_H
