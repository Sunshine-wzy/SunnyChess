#ifndef SUNNYCHESS_MENU_H
#define SUNNYCHESS_MENU_H

#include <vector>
#include <utility>
#include "Button.h"

typedef void (*ButtonAction)();

// 菜单
class Menu {
private:
    // 所有按钮及其回调
    std::vector< std::pair<Button*, ButtonAction> > buttons;
    
    
public:
    Menu();
    ~Menu();
    
    // 打开菜单
    virtual void open();
    // 初始化菜单
    virtual void onInit() = 0;
    // 启动菜单
    virtual void onEnable() = 0;
    
    // 添加按钮
    void addButton(Button *button, ButtonAction action);
    // 绘制所有按钮
    void drawButtons() const;
    // 点击(x, y) 若该坐标位于某个按钮的区域内，则触发其回调
    void clickButton(int x, int y) const;
    
};


#endif //SUNNYCHESS_MENU_H
