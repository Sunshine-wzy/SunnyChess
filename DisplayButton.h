#ifndef SUNNYCHESS_DISPLAYBUTTON_H
#define SUNNYCHESS_DISPLAYBUTTON_H

#include "Button.h"
#include "Player.h"


// 显示按钮
// 只有显示功能，点击反馈被忽略
class DisplayButton : public Button {
public:
    DisplayButton(int x, int y);

private:
    bool isInside(int x, int y) override;

};


// 显示按键提示
class DisplayKeyButton : public DisplayButton {
private:
    const KeySettings *keySettings;
    
public:
    DisplayKeyButton(int x, int y);

    void draw() override;
    
    void setKeySettings(const KeySettings *settings);

};


#endif //SUNNYCHESS_DISPLAYBUTTON_H
