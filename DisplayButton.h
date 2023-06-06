#ifndef SUNNYCHESS_DISPLAYBUTTON_H
#define SUNNYCHESS_DISPLAYBUTTON_H

#include "Button.h"
#include "Player.h"


class DisplayButton : public Button {
public:
    DisplayButton(int x, int y);

private:
    bool isInside(int x, int y) override;

};


class DisplayKeyButton : public DisplayButton {
private:
    const KeySettings *keySettings;
    
public:
    DisplayKeyButton(int x, int y);

    void draw() override;
    
    void setKeySettings(const KeySettings *settings);

};


#endif //SUNNYCHESS_DISPLAYBUTTON_H
