#include <pybind11/pybind11.h>

namespace py = pybind11;

class Matrix {
public:
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
        m_data = new float[rows*cols];
    }
    float operator()(py::ssize_t i, py::ssize_t j) const {
            return m_data[(size_t) (i*m_cols + j)];
        }
    float &operator()(py::ssize_t i, py::ssize_t j) {
            return m_data[(size_t) (i*m_cols + j)];
        }
    float *data() { return m_data; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }
    Matrix add(Matrix &m){
        auto r = Matrix(m.rows(), m.cols());
        for (size_t i = 0; i < m.rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++){
                r.m_data[i*m_cols + j] = this->m_data[i*m_cols + j] + m.m_data[i*m_cols + j];
            }
        }
        return r;
    }
private:
    size_t m_rows, m_cols;
    float *m_data;
};

PYBIND11_MODULE(example, m) {
py::class_<Matrix>(m, "Matrix", py::buffer_protocol())
   .def(py::init<py::ssize_t, py::ssize_t>())
   .def_buffer([](Matrix &m) -> py::buffer_info {
        return py::buffer_info(
            m.data(),                               /* Pointer to buffer */
            sizeof(float),                          /* Size of one scalar */
            py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
            2,                                      /* Number of dimensions */
            { m.rows(), m.cols() },                 /* Buffer dimensions */
            { sizeof(float) * m.cols(),             /* Strides (in bytes) for each index */
              sizeof(float) }
        );
    })
    .def("__getitem__", [](const Matrix &m, std::pair<py::ssize_t, py::ssize_t> i) {
            if (i.first >= m.rows() || i.second >= m.cols())
                throw py::index_error();
            return m(i.first, i.second);
        })
    .def("__setitem__", [](Matrix &m, std::pair<py::ssize_t, py::ssize_t> i, float v) {
            if (i.first >= m.rows() || i.second >= m.cols())
                throw py::index_error();
            m(i.first, i.second) = v;
        })
    .def("rows", &Matrix::rows)
    .def("cols", &Matrix::cols)
    .def("add", &Matrix::add);

}