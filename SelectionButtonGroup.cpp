#include "SelectionButtonGroup.h"

SelectionButtonGroup::SelectionButtonGroup()
        : buttons(std::map<std::string, SelectionButton *>()) {}

void SelectionButtonGroup::select(SelectionButton *button) {
    selectedKey = button->getName();

    for (auto &pair: buttons) {
        if (pair.second == button) {
            pair.second->setSelected(true);
        } else pair.second->setSelected(false);
    }
}

void SelectionButtonGroup::clear() {
    buttons.clear();
}

SelectionButtonGroup &SelectionButtonGroup::addButton(SelectionButton *button) {
    if (button == nullptr) return *this;
    
    if (buttons.empty()) {
        selectedKey = button->getName();
        button->setSelected(true);
    }
    
    buttons[button->getName()] = button;
    return *this;
}

const std::string &SelectionButtonGroup::getSelectedKey() const {
    return selectedKey;
}

SelectionButton *SelectionButtonGroup::getSelectedButton() {
    return buttons[selectedKey];
}

SelectionButton *SelectionButtonGroup::getButton(const std::string &key) {
    return buttons[key];
}
