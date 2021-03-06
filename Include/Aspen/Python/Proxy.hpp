#ifndef ASPEN_PYTHON_PROXY_HPP
#define ASPEN_PYTHON_PROXY_HPP
#include <string>
#include <type_traits>
#include <pybind11/pybind11.h>
#include "Aspen/Proxy.hpp"
#include "Aspen/Python/Reactor.hpp"

namespace Aspen {

  /** Exports a Proxy evaluating to a Python object. */
  void export_proxy(pybind11::module& module);

  /**
   * Exports the generic Proxy reactor.
   * @param module The module to export to.
   * @param prefix The prefix to use when forming the type name.
   */
  template<typename T>
  void export_proxy(pybind11::module& module, const std::string& prefix) {
    auto name = prefix + "Proxy";
    if(pybind11::hasattr(module, name.c_str())) {
      return;
    }
    export_reactor<Proxy<T>>(module, name)
      .def(pybind11::init<>())
      .def("set_reactor", [] (Proxy<T>& self, T& reactor) {
        self.set_reactor(reactor);
      });
    if constexpr(!std::is_same_v<T, SharedBox<pybind11::object>>) {
      pybind11::implicitly_convertible<Proxy<T>,
        Proxy<SharedBox<pybind11::object>>>();
    }
  }
}

#endif
