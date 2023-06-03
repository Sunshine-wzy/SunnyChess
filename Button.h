#ifndef SUNNYCHESS_BUTTON_H
#define SUNNYCHESS_BUTTON_H

#include <string>


// 按钮
class Button {
private:
    // 按钮名
    std::string name;
    
    // 按钮中心坐标
    int x;
    int y;

    // 按钮大小
    int width;
    int height;
    
    // 是否可见
    bool visible;

public:
    Button(std::string name, int x, int y, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT);

    virtual ~Button();

    // 绘制按钮
    virtual void draw() = 0;

    // 判断(x, y)是否在按钮区域内
    virtual bool isInside(int x, int y);

    const std::string &getName() const;

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    bool isVisible() const;

    void setVisible(bool isVisible);


    // 按钮默认大小
    static const int BUTTON_WIDTH = 300;
    static const int BUTTON_HEIGHT = 100;
};


#endif //SUNNYCHESS_BUTTON_H
