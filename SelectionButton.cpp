#include "SelectionButton.h"

SelectionButton::SelectionButton(int x, int y, int width, int height)
        : Button(x, y, width, height), selected(false) {}

bool SelectionButton::isSelected() const {
    return selected;
}

void SelectionButton::setSelected(bool isSelected) {
    selected = isSelected;
}

bool SelectionButton::switchSelected() {
    selected = !selected;
    return selected;
}

void SelectionButton::draw() {
    if (selected) drawSelected();
    else drawNormal();
}
