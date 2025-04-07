from __future__ import annotations

from ._core import __doc__, __version__, YogaNode
from enum import Enum
from typing import Optional


class FlexDirection(str, Enum):
    ROW = "row"
    COLUMN = "column"
    ROW_REVERSE = "row-reverse"
    COLUMN_REVERSE = "column-reverse"

    @staticmethod
    def parse(value: Optional[str]) -> Optional[FlexDirection]:
        if value is None:
            return None

        try:
            return FlexDirection(value)
        except ValueError:
            raise ValueError(
                f"Invalid FlexDirection: {value}. Expected one of {list(FlexDirection)}"
            )


class Edge(str, Enum):
    LEFT = "left"
    TOP = "top]"
    RIGHT = "right"
    BOTTOM = "bottom"
    START = "start"
    END = "end"
    HORIZONTAL = "horizontal"
    VERTICAL = "vertical"
    ALL = "all"

    @staticmethod
    def parse(value: Optional[str]) -> Optional[Edge]:
        if value is None:
            return None
        try:
            return Edge(value)
        except ValueError:
            raise ValueError(f"Invalid Edge: {value}. Expected one of {list(Edge)}")


class JustifyContent(str, Enum):
    FLEX_START = "flex-start"
    CENTER = "center"
    FLEX_END = "flex-end"
    SPACE_BETWEEN = "space-between"
    SPACE_AROUND = "space-around"
    SPACE_EVENLY = "space-evenly"

    @staticmethod
    def parse(value: Optional[str]) -> Optional[JustifyContent]:
        if value is None:
            return None
        try:
            return JustifyContent(value)
        except ValueError:
            raise ValueError(
                f"Invalid JustifyContent: {value}. Expected one of {list(JustifyContent)}"
            )


class Align(str, Enum):
    AUTO = "auto"
    FLEX_START = "flex-start"
    CENTER = "center"
    FLEX_END = "flex-end"
    STRETCH = "stretch"
    BASELINE = "baseline"
    SPACE_BETWEEN = "space-between"
    SPACE_AROUND = "space-around"

    @staticmethod
    def parse(value: Optional[str]) -> Optional[Align]:
        if value is None:
            return None
        try:
            return Align(value)
        except ValueError:
            raise ValueError(f"Invalid Align: {value}. Expected one of {list(Align)}")


class PositionType(str, Enum):
    RELATIVE = "relative"
    ABSOLUTE = "absolute"

    @staticmethod
    def parse(value: Optional[str]) -> Optional[PositionType]:
        if value is None:
            return None
        try:
            return PositionType(value)
        except ValueError:
            raise ValueError(
                f"Invalid PositionType: {value}. Expected one of {list(PositionType)}"
            )


class Display(str, Enum):
    FLEX = "flex"
    NONE = "none"

    @staticmethod
    def parse(value: Optional[str]) -> Optional[Display]:
        if value is None:
            return None
        try:
            return Display(value)
        except ValueError:
            raise ValueError(
                f"Invalid Display: {value}. Expected one of {list(Display)}"
            )


__all__ = [
    "__doc__",
    "__version__",
    "YogaNode",
    "FlexDirection",
    "Edge",
    "JustifyContent",
    "Align",
    "PositionType",
    "Display",
]
