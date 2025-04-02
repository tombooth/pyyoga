#include <pybind11/pybind11.h>
#include "yoga/Yoga.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

class YogaNode
{
public:
    YogaNode() : node(YGNodeNew()) {}
    ~YogaNode() { YGNodeFree(node); }

    void set_width(float width) { YGNodeStyleSetWidth(node, width); }
    void set_height(float height) { YGNodeStyleSetHeight(node, height); }
    void calculate_layout()
    {
        YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionLTR);
    }
    std::tuple<float, float, float, float> get_layout() const
    {
        return std::make_tuple(
            YGNodeLayoutGetLeft(node),
            YGNodeLayoutGetTop(node),
            YGNodeLayoutGetWidth(node),
            YGNodeLayoutGetHeight(node));
    }

private:
    YGNodeRef node;
};

PYBIND11_MODULE(_core, m)
{
    m.doc() = "Python bindings for Facebook's Yoga layout engine";

    py::class_<YogaNode>(m, "YogaNode")
        .def(py::init<>())
        .def("set_width", &YogaNode::set_width)
        .def("set_height", &YogaNode::set_height)
        .def("calculate_layout", &YogaNode::calculate_layout)
        .def("get_layout", &YogaNode::get_layout);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}