#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

using std::vector; 

vector<int> list_double(vector<int>& list) {
    vector<int> v;
    v.clear();    
    v.reserve(list.size());    
    for (size_t i = 0; i < list.size(); ++i) {
        int n = list[i];        
        v.push_back(2*n);    
    }    
    return v;
} 
PYBIND11_MODULE(example, m) {    
    m.doc() = "pass and return a list";    
    m.def("list_double", &list_double, "example function");
}