#ifndef SUNNYCHESS_SELECTIONBUTTONGROUP_H
#define SUNNYCHESS_SELECTIONBUTTONGROUP_H

#include <vector>
#include "SelectionButton.h"


class SelectionButtonGroup {
private:
    std::vector<SelectionButton *> buttons;
    
public:
    SelectionButtonGroup();
    
    // 选中一个按钮
    void select(SelectionButton *button) const;
    
    // 清除所有按钮
    void clear();
    
    // 添加一个按钮
    SelectionButtonGroup& addButton(SelectionButton *button);
    
};


#endif //SUNNYCHESS_SELECTIONBUTTONGROUP_H
