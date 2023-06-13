#ifndef SUNNYCHESS_CIRCLESELECTIONBUTTON_H
#define SUNNYCHESS_CIRCLESELECTIONBUTTON_H

#include "SelectionButton.h"
#include <graphics.h>
#include <string>


// 圆形选择按钮
class CircleSelectionButton : public SelectionButton {
private:
    int radius;                 // 半径
    RECT relativeRect;          // 显示范围（相对坐标）
    RECT realRect;              // 显示范围（绝对坐标）
    IMAGE *image;               // 显示图片
    std::string text;           // 显示文字

public:
    CircleSelectionButton(std::string name, int x, int y, int radius, RECT relativeRect = {0, 0, 0, 0}, IMAGE *image = nullptr, std::string text = "");

    ~CircleSelectionButton() override;


    bool isInside(int x, int y) override;

    void drawNormal() override;

    void drawSelected() override;

};


#endif //SUNNYCHESS_CIRCLESELECTIONBUTTON_H
