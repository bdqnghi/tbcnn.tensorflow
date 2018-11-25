#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>

#include "sort.h"

#include "hello.h"

namespace py = pybind11;
using namespace lcc;

PYBIND11_MODULE(_lcclib, m) {
    m.doc() = R"pbdoc(
        Python module wrapper for LCC C++ library.
    )pbdoc";

    m.def("test", &lcc::hello);

    m.def("selectionSort", &selectionSort<long>);
    m.def("selectionSort", &lcc::selectionSort<int>);
    m.def("selectionSort", &lcc::selectionSort<char>);
    m.def("selectionSort", &lcc::selectionSort<double>);
    m.def("selectionSort", &lcc::selectionSort<float>);
    m.def("insertionSort", &lcc::insertionSort<long>);
    m.def("insertionSort", &lcc::insertionSort<int>);
    m.def("insertionSort", &lcc::insertionSort<char>);
    m.def("insertionSort", &lcc::insertionSort<double>);
    m.def("insertionSort", &lcc::insertionSort<float>);
    
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

}
