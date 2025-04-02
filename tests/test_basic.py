from __future__ import annotations

from pyyoga import YogaNode, __version__


def test_layout():
    node = YogaNode()
    node.set_width(100)
    node.set_height(100)
    node.calculate_layout()
    (left, top, wdith, height) = node.get_layout()

    assert left == 0
    assert top == 0
    assert wdith == 100
    assert height == 100


def test_version():
    assert __version__ == "0.1.0"
