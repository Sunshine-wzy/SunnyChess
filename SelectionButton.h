#ifndef SUNNYCHESS_SELECTIONBUTTON_H
#define SUNNYCHESS_SELECTIONBUTTON_H

#include "Button.h"

// 选择按钮
class SelectionButton : public Button {
private:
    bool selected;
    
public:
    SelectionButton(int x, int y, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT);

    bool isSelected() const;

    void setSelected(bool isSelected);
    
    // 切换选择状态
    bool switchSelected();

    void draw() final;

    // 画出未选中状态的按钮
    virtual void drawNormal() = 0;
    
    // 画出选中状态的按钮
    virtual void drawSelected() = 0;
    
};


#endif //SUNNYCHESS_SELECTIONBUTTON_H
