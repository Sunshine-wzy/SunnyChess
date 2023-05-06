#ifndef SUNNYCHESS_BUTTON_H
#define SUNNYCHESS_BUTTON_H

// 按钮
class Button {
private:
    // 按钮中心坐标
    int x;
    int y;
    
    // 按钮大小
    int width;
    int height;
    
public:
    Button(int x, int y, int width = BUTTON_WIDTH, int height = BUTTON_HEIGHT);
    virtual ~Button();
    
    // 绘制按钮
    virtual void draw() = 0;
    // 判断(x, y)是否在按钮区域内
    virtual bool isInside(int x, int y) = 0;

    int getX() const;
    int getY() const;

    int getWidth() const;
    int getHeight() const;


    // 按钮默认大小
    static const int BUTTON_WIDTH = 300;
    static const int BUTTON_HEIGHT = 100;
};


#endif //SUNNYCHESS_BUTTON_H
