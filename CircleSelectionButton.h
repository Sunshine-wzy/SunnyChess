#ifndef SUNNYCHESS_CIRCLESELECTIONBUTTON_H
#define SUNNYCHESS_CIRCLESELECTIONBUTTON_H

#include "SelectionButton.h"


class CircleSelectionButton : public SelectionButton {
private:
    int radius;

public:
    CircleSelectionButton(int x, int y, int radius);


    bool isInside(int x, int y) override;

    void drawNormal() override;

    void drawSelected() override;

};


#endif //SUNNYCHESS_CIRCLESELECTIONBUTTON_H
