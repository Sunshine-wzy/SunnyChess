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

    const std::string &getSelectedKey() const;

    SelectionButton *getSelectedButton();
    
    SelectionButton *getButton(const std::string &key);
    
    bool isKeySelected(const std::string &key) const;
    
    void setVisible(bool isVisible);
    
};


#endif //SUNNYCHESS_SELECTIONBUTTONGROUP_H
