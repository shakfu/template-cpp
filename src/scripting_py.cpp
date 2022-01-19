#include <pybind11/pybind11.h>

#include "core/process.hpp"
#include "model/vehicle.hpp"

namespace py = pybind11;

PYBIND11_MODULE(app, m)
{
    py::class_<model::Vehicle>(m, "Vehicle")
        .def(py::init<>())
        .def_readwrite("brand", &model::Vehicle::brand)
        .def_readwrite("cost", &model::Vehicle::cost)
        .def_readwrite("weight", &model::Vehicle::weight)
        .def("cost_per_kg", &model::Vehicle::cost_per_kg)
        .def("to_string", &model::Vehicle::to_string);

    py::class_<core::Process>(m, "Process")
        .def(py::init<>())
        .def("report", &core::Process::report);
}
