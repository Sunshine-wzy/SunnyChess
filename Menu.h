#ifndef SUNNYCHESS_MENU_H
#define SUNNYCHESS_MENU_H

#include <vector>
#include <utility>
#include "Button.h"


class Menu;

typedef void (*ButtonAction)(Menu &menu, Button &button, int x, int y);

// 菜单
class Menu {
private:
    // 所有按钮及其回调
    std::vector< std::pair<Button *, ButtonAction> > buttons;


public:
    Menu();

    ~Menu();

    // 打开菜单
    virtual void open();

    // 重新打开菜单（不初始化按钮）
    virtual void reopen();
    
    // 首次打开菜单初始化
    virtual void onOpenInit();

    // 初始化菜单（在初始化、绘制按钮之前）
    virtual void onInit();

    // 初始化按钮（在绘制按钮之前，初始化菜单之后）
    virtual void initButtons();

    // 启动菜单（在绘制按钮之后）
    virtual void onEnable();
    
    virtual void redraw();

    // 添加按钮
    void addButton(Button *button, ButtonAction action);

    // 绘制所有按钮
    void drawButtons() const;

    // 点击(x, y) 若该坐标位于某个按钮的区域内，则触发其回调
    void clickButton(int x, int y);

};


#endif //SUNNYCHESS_MENU_H
