#include "doctest.h"

#include "model/vehicle.hpp"



TEST_CASE("testing vehicle") {
	model::Vehicle v;
	v.brand = "x";
    v.cost = 10.0;
    v.weight = 5.0;
    CHECK(v.cost_per_kg() == 2.0);
}
