#ifndef SUNNYCHESS_ROUNDRECTANGLEBUTTON_H
#define SUNNYCHESS_ROUNDRECTANGLEBUTTON_H

#include "Button.h"


class RoundRectangleButton : public Button {
private:
    int ellipseWidth;
    int ellipseHeight;
    
public:
    RoundRectangleButton(int x, int y, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT, int ellipseWidth = ELLIPSE_WIDTH, int ellipseHeight = ELLIPSE_HEIGHT);

    void draw() override;

    
    // 圆角矩形的圆角的椭圆的默认大小
    static const int ELLIPSE_WIDTH = 50;
    static const int ELLIPSE_HEIGHT = 50;
};


#endif //SUNNYCHESS_ROUNDRECTANGLEBUTTON_H
