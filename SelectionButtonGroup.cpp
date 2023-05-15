#include "SelectionButtonGroup.h"

SelectionButtonGroup::SelectionButtonGroup() = default;

void SelectionButtonGroup::select(SelectionButton *button) const {
    for (auto b : buttons) {
        if (b == button) {
            b->setSelected(true);
        } else b->setSelected(false);
    }
}

void SelectionButtonGroup::clear() {
    buttons.clear();
}

SelectionButtonGroup& SelectionButtonGroup::addButton(SelectionButton *button) {
    buttons.push_back(button);
    return *this;
}
