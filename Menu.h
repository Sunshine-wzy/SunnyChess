#ifndef SUNNYCHESS_MENU_H
#define SUNNYCHESS_MENU_H

#include <vector>
#include <utility>
#include "Button.h"

typedef void (*ButtonAction)();

class Menu {
private:
    std::vector< std::pair<Button&, ButtonAction> > buttons;
    
    
public:
    Menu();
    
    void addButton(Button &button, ButtonAction action);
    
    void drawButtons() const;
    
};


#endif //SUNNYCHESS_MENU_H
