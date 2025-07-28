#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "yoga/Yoga.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

class YogaNode
{
public:
    YogaNode() : node(YGNodeNew()) {}
    explicit YogaNode(YGConfigRef config) : node(YGNodeNewWithConfig(config)) {}
    explicit YogaNode(YGNodeRef nodeRef) : node(nodeRef) {}
    ~YogaNode() { YGNodeFree(node); }

    void set_width(float width) { YGNodeStyleSetWidth(node, width); }
    void set_width_percent(float percent) { YGNodeStyleSetWidthPercent(node, percent); }
    void set_width_auto() { YGNodeStyleSetWidthAuto(node); }

    void set_height(float height) { YGNodeStyleSetHeight(node, height); }
    void set_height_percent(float percent) { YGNodeStyleSetHeightPercent(node, percent); }
    void set_height_auto() { YGNodeStyleSetHeightAuto(node); }

    void set_flex(float flex) { YGNodeStyleSetFlex(node, flex); }
    void set_flex_grow(float flex_grow) { YGNodeStyleSetFlexGrow(node, flex_grow); }
    void set_flex_shrink(float flex_shrink) { YGNodeStyleSetFlexShrink(node, flex_shrink); }

    void set_margin(const char *edge, float margin)
    {
        YGNodeStyleSetMargin(node, string_to_edge(edge), margin);
    }

    void set_margin_percent(const char *edge, float percent)
    {
        YGNodeStyleSetMarginPercent(node, string_to_edge(edge), percent);
    }

    void set_margin_auto(const char *edge)
    {
        YGNodeStyleSetMarginAuto(node, string_to_edge(edge));
    }

    void set_padding(const char *edge, float padding)
    {
        YGNodeStyleSetPadding(node, string_to_edge(edge), padding);
    }

    void set_padding_percent(const char *edge, float percent)
    {
        YGNodeStyleSetPaddingPercent(node, string_to_edge(edge), percent);
    }

    void set_border(const char *edge, float border)
    {
        YGNodeStyleSetBorder(node, string_to_edge(edge), border);
    }

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

    void insert_child(YogaNode &child, size_t index) { YGNodeInsertChild(node, child.node, index); }
    void remove_child(YogaNode &child) { YGNodeRemoveChild(node, child.node); }
    void remove_all_children() { YGNodeRemoveAllChildren(node); }

    size_t get_child_count() const { return YGNodeGetChildCount(node); }
    std::shared_ptr<YogaNode> get_child(size_t index) const
    {
        YGNodeRef childNode = YGNodeGetChild(node, index);
        if (!childNode)
            throw std::out_of_range("Child index out of range");
        return std::make_shared<YogaNode>(childNode);
    }

    void set_flex_wrap(const char *name)
    {
        if (strcmp(name, "nowrap") == 0)
            YGNodeStyleSetFlexWrap(node, YGWrapNoWrap);
        else if (strcmp(name, "wrap") == 0)
            YGNodeStyleSetFlexWrap(node, YGWrapWrap);
        else if (strcmp(name, "wrap-reverse") == 0)
            YGNodeStyleSetFlexWrap(node, YGWrapWrapReverse);
        else
            throw std::invalid_argument("Invalid flex wrap: " + std::string(name) + ". Expected 'nowrap', 'wrap', or 'wrap-reverse'.");
    }

    void set_flex_direction(const char *name)
    {
        if (strcmp(name, "column") == 0)
            YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
        else if (strcmp(name, "column-reverse") == 0)
            YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumnReverse);
        else if (strcmp(name, "row") == 0)
            YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
        else if (strcmp(name, "row-reverse") == 0)
            YGNodeStyleSetFlexDirection(node, YGFlexDirectionRowReverse);
        else
            throw std::invalid_argument("Invalid flex direction: " + std::string(name) + ". Expected 'column', 'column-reverse', 'row', or 'row-reverse'.");
    }

    void set_justify_content(const char *name)
    {
        if (strcmp(name, "flex-start") == 0)
            YGNodeStyleSetJustifyContent(node, YGJustifyFlexStart);
        else if (strcmp(name, "center") == 0)
            YGNodeStyleSetJustifyContent(node, YGJustifyCenter);
        else if (strcmp(name, "flex-end") == 0)
            YGNodeStyleSetJustifyContent(node, YGJustifyFlexEnd);
        else if (strcmp(name, "space-between") == 0)
            YGNodeStyleSetJustifyContent(node, YGJustifySpaceBetween);
        else if (strcmp(name, "space-around") == 0)
            YGNodeStyleSetJustifyContent(node, YGJustifySpaceAround);
        else if (strcmp(name, "space-evenly") == 0)
            YGNodeStyleSetJustifyContent(node, YGJustifySpaceEvenly);
        else
            throw std::invalid_argument("Invalid justify content: " + std::string(name) + ". Expected 'flex-start', 'center', 'flex-end', 'space-between', 'space-around', or 'space-evenly'.");
    }

    void set_align_items(const char *name)
    {
        if (strcmp(name, "auto") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignAuto);
        else if (strcmp(name, "flex-start") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignFlexStart);
        else if (strcmp(name, "center") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignCenter);
        else if (strcmp(name, "flex-end") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignFlexEnd);
        else if (strcmp(name, "stretch") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignStretch);
        else if (strcmp(name, "baseline") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignBaseline);
        else if (strcmp(name, "space-between") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignSpaceBetween);
        else if (strcmp(name, "space-around") == 0)
            YGNodeStyleSetAlignItems(node, YGAlignSpaceAround);
        else
            throw std::invalid_argument("Invalid align items: " + std::string(name) + ". Expected 'auto', 'flex-start', 'center', 'flex-end', 'stretch', 'baseline', 'space-between', or 'space-around'.");
    }

    void set_align_self(const char *name)
    {
        if (strcmp(name, "auto") == 0)
            YGNodeStyleSetAlignSelf(node, YGAlignAuto);
        else if (strcmp(name, "flex-start") == 0)
            YGNodeStyleSetAlignSelf(node, YGAlignFlexStart);
        else if (strcmp(name, "center") == 0)
            YGNodeStyleSetAlignSelf(node, YGAlignCenter);
        else if (strcmp(name, "flex-end") == 0)
            YGNodeStyleSetAlignSelf(node, YGAlignFlexEnd);
        else if (strcmp(name, "stretch") == 0)
            YGNodeStyleSetAlignSelf(node, YGAlignStretch);
        else if (strcmp(name, "baseline") == 0)
            YGNodeStyleSetAlignSelf(node, YGAlignBaseline);
        else
            throw std::invalid_argument("Invalid align self: " + std::string(name) + ". Expected 'auto', 'flex-start', 'center', 'flex-end', 'stretch', or 'baseline'.");
    }

    void set_align_content(const char *name)
    {
        if (strcmp(name, "flex-start") == 0)
            YGNodeStyleSetAlignContent(node, YGAlignFlexStart);
        else if (strcmp(name, "center") == 0)
            YGNodeStyleSetAlignContent(node, YGAlignCenter);
        else if (strcmp(name, "flex-end") == 0)
            YGNodeStyleSetAlignContent(node, YGAlignFlexEnd);
        else if (strcmp(name, "stretch") == 0)
            YGNodeStyleSetAlignContent(node, YGAlignStretch);
        else if (strcmp(name, "space-between") == 0)
            YGNodeStyleSetAlignContent(node, YGAlignSpaceBetween);
        else if (strcmp(name, "space-around") == 0)
            YGNodeStyleSetAlignContent(node, YGAlignSpaceAround);
        else
            throw std::invalid_argument("Invalid align content: " + std::string(name) + ". Expected 'flex-start', 'center', 'flex-end', 'stretch', 'space-between', or 'space-around'.");
    }

    void set_position_type(const char *name)
    {
        if (strcmp(name, "relative") == 0)
            YGNodeStyleSetPositionType(node, YGPositionTypeRelative);
        else if (strcmp(name, "absolute") == 0)
            YGNodeStyleSetPositionType(node, YGPositionTypeAbsolute);
        else
            throw std::invalid_argument("Invalid position type: " + std::string(name) + ". Expected 'relative' or 'absolute'.");
    }

    void set_display(const char *name)
    {
        if (strcmp(name, "flex") == 0)
            YGNodeStyleSetDisplay(node, YGDisplayFlex);
        else if (strcmp(name, "none") == 0)
            YGNodeStyleSetDisplay(node, YGDisplayNone);
        else
            throw std::invalid_argument("Invalid display: " + std::string(name) + ". Expected 'flex' or 'none'.");
    }

    void set_gap(const char *gutter, float gap)
    {
        YGNodeStyleSetGap(node, string_to_gutter(gutter), gap);
    }

private:
    YGNodeRef node; // Ensure this remains private and inaccessible from Python or external code.

    YGEdge string_to_edge(const char *edge) const
    {
        if (strcmp(edge, "left") == 0)
            return YGEdgeLeft;
        else if (strcmp(edge, "top") == 0)
            return YGEdgeTop;
        else if (strcmp(edge, "right") == 0)
            return YGEdgeRight;
        else if (strcmp(edge, "bottom") == 0)
            return YGEdgeBottom;
        else if (strcmp(edge, "start") == 0)
            return YGEdgeStart;
        else if (strcmp(edge, "end") == 0)
            return YGEdgeEnd;
        else if (strcmp(edge, "horizontal") == 0)
            return YGEdgeHorizontal;
        else if (strcmp(edge, "vertical") == 0)
            return YGEdgeVertical;
        else if (strcmp(edge, "all") == 0)
            return YGEdgeAll;
        else
            throw std::invalid_argument("Invalid edge: " + std::string(edge) + ". Expected 'left', 'top', 'right', 'bottom', 'start', 'end', 'horizontal', 'vertical', or 'all'.");
    }

    YGGutter string_to_gutter(const char *gutter) const
    {
        if (strcmp(gutter, "column") == 0)
            return YGGutterColumn;
        else if (strcmp(gutter, "row") == 0)
            return YGGutterRow;
        else if (strcmp(gutter, "all") == 0)
            return YGGutterAll;
        else
            throw std::invalid_argument("Invalid gutter: " + std::string(gutter) + ". Expected 'column', 'row', or 'all'.");
    }
};

PYBIND11_MODULE(_core, m)
{
    m.doc() = "Python bindings for Facebook's Yoga layout engine";

    py::class_<YogaNode>(m, "YogaNode")
        .def(py::init<>())
        .def("set_width", &YogaNode::set_width)
        .def("set_width_percent", &YogaNode::set_width_percent)
        .def("set_width_auto", &YogaNode::set_width_auto)
        .def("set_height", &YogaNode::set_height)
        .def("set_height_percent", &YogaNode::set_height_percent)
        .def("set_height_auto", &YogaNode::set_height_auto)
        .def("set_flex", &YogaNode::set_flex)
        .def("set_flex_grow", &YogaNode::set_flex_grow)
        .def("set_flex_shrink", &YogaNode::set_flex_shrink)
        .def("set_margin", &YogaNode::set_margin)
        .def("set_margin_percent", &YogaNode::set_margin_percent)
        .def("set_margin_auto", &YogaNode::set_margin_auto)
        .def("set_padding", &YogaNode::set_padding)
        .def("set_padding_percent", &YogaNode::set_padding_percent)
        .def("set_border", &YogaNode::set_border)
        .def("calculate_layout", &YogaNode::calculate_layout)
        .def("get_layout", &YogaNode::get_layout)
        .def("insert_child", &YogaNode::insert_child)
        .def("remove_child", &YogaNode::remove_child)
        .def("remove_all_children", &YogaNode::remove_all_children)
        .def("get_child_count", &YogaNode::get_child_count)
        .def("get_child", &YogaNode::get_child)
        .def("set_flex_direction", &YogaNode::set_flex_direction)
        .def("set_flex_wrap", &YogaNode::set_flex_wrap)
        .def("set_justify_content", &YogaNode::set_justify_content)
        .def("set_align_items", &YogaNode::set_align_items)
        .def("set_align_self", &YogaNode::set_align_self)
        .def("set_align_content", &YogaNode::set_align_content)
        .def("set_position_type", &YogaNode::set_position_type)
        .def("set_display", &YogaNode::set_display)
        .def("set_gap", &YogaNode::set_gap);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}