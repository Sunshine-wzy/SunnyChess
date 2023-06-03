#include "SelectionButton.h"
#include <utility>

SelectionButton::SelectionButton(std::string name, int x, int y, int width, int height)
        : Button(std::move(name), x, y, width, height), selected(false) {}

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
    if (!isVisible()) return;
    
    if (selected) drawSelected();
    else drawNormal();
}
