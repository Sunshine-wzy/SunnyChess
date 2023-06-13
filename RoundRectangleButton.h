#ifndef SUNNYCHESS_ROUNDRECTANGLEBUTTON_H
#define SUNNYCHESS_ROUNDRECTANGLEBUTTON_H

#include "Button.h"


// 圆角矩形选择按钮
class RoundRectangleButton : public Button {
private:
    // 圆角大小
    int ellipseWidth;
    int ellipseHeight;
    
    IMAGE *image;
    std::string text;
    
    // 图片和文字显示范围
    RECT rect;
    
public:
    RoundRectangleButton(std::string name, int x, int y, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT,
                         IMAGE *image = nullptr, std::string text = "",
                         int ellipseWidth = ELLIPSE_WIDTH, int ellipseHeight = ELLIPSE_HEIGHT);

    ~RoundRectangleButton() override;

    void draw() override;

    bool isInside(int x, int y) override;

    void setX(int x) override;

    void setY(int y) override;


    // 圆角矩形的圆角的椭圆的默认大小
    static const int ELLIPSE_WIDTH = 50;
    static const int ELLIPSE_HEIGHT = 50;
};


#endif //SUNNYCHESS_ROUNDRECTANGLEBUTTON_H
