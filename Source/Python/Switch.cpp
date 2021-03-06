#include "Aspen/Python/Switch.hpp"
#include "Aspen/Python/Box.hpp"

using namespace Aspen;
using namespace pybind11;

void Aspen::export_switch(pybind11::module& module) {
  export_box<bool>(module, "Bool");
  export_switch<SharedBox<bool>, SharedBox<object>>(module, "");
  module.def("switch",
    [] (SharedBox<bool> toggle, SharedBox<object> series) {
      return switch_(std::move(toggle), std::move(series));
    });
}
