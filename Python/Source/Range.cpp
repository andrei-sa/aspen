#include "Aspen/Python/Range.hpp"
#include "Aspen/Python/Box.hpp"
#include "Aspen/Python/Constant.hpp"
#include "Aspen/Python/Object.hpp"

using namespace Aspen;
using namespace pybind11;

void Aspen::export_range(pybind11::module& module) {
  module.def("range",
    [] (object start, object stop) {
      return Box(range(PythonBox<object>(start), PythonBox<object>(stop),
        constant(cast(1))));
    });
}
