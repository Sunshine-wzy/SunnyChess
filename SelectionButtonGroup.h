#ifndef SUNNYCHESS_SELECTIONBUTTONGROUP_H
#define SUNNYCHESS_SELECTIONBUTTONGROUP_H

#include <map>
#include <string>
#include "SelectionButton.h"


// 选择按钮组
class SelectionButtonGroup {
private:
    // 按钮映射
    std::map<std::string, SelectionButton *> buttons;
    // 选中按钮的按钮名
    std::string selectedKey;

public:
    SelectionButtonGroup();

    // 选中一个按钮
    void select(SelectionButton *button);

    // 清除所有按钮
    void clear();

    // 添加一个按钮
    SelectionButtonGroup &addButton(SelectionButton *button);

    // 获取选中按钮的按钮名
    const std::string &getSelectedKey() const;

    // 获取选中按钮
    SelectionButton *getSelectedButton();
    
    // 根据按钮名获取按钮
    SelectionButton *getButton(const std::string &key);
    
    // 判断名为key的按钮是否被选中
    bool isKeySelected(const std::string &key) const;
    
    // 设置所有按钮的可见性
    void setVisible(bool isVisible);
    
};


#endif //SUNNYCHESS_SELECTIONBUTTONGROUP_H
