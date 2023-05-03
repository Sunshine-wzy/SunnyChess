#include <graphics.h>
#include <conio.h>

int main() {
    // 初始化图形模式
    initgraph(640, 480);

    circle(320, 240, 100);
    _getch();
    
    // 关闭图形模式
    closegraph();
    
    return 0;
}
