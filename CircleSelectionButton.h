#ifndef SUNNYCHESS_CIRCLESELECTIONBUTTON_H
#define SUNNYCHESS_CIRCLESELECTIONBUTTON_H

#include "SelectionButton.h"
#include <graphics.h>
#include <string>


class CircleSelectionButton : public SelectionButton {
private:
    int radius;
    RECT relativeRect;
    RECT realRect;
    IMAGE *image;
    std::string text;

public:
    CircleSelectionButton(std::string name, int x, int y, int radius, RECT relativeRect = {0, 0, 0, 0}, IMAGE *image = nullptr, std::string text = "");

    ~CircleSelectionButton() override;


    bool isInside(int x, int y) override;

    void drawNormal() override;

    void drawSelected() override;

};


#endif //SUNNYCHESS_CIRCLESELECTIONBUTTON_H
