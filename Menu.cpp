#include "Menu.h"

Menu::Menu() = default;

void Menu::addButton(Button &button, ButtonAction action) {
    buttons.emplace_back(button, action);
}

void Menu::drawButtons() const {
    for (auto pair : buttons) {
        
    }
}
