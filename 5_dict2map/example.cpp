#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;
namespace py = pybind11;

map<string, vector<py::object> > group_by(vector<pair<string, py::object> > data) {
    map<string, vector<py::object> > ret_map;
    for (pair<string, py::object> d : data) {
        string key = d.first;
        py::object value = d.second;
        ret_map[key].push_back(value);
    }
    return ret_map;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "simple groupby";
    m.def("group_by", &group_by, 
          "simple groupby: (str, object) -> dict(str, list[object])");
}