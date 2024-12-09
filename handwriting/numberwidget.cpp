#include "numberwidget.h"
#include <QPushButton>;

NumberWidget::NumberWidget(QWidget *parent) : QWidget(parent)
{

}
void NumberWidget::onNumberBtnClicked()
{
    // 获取发送信号的按钮的文本
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        emit numberClicked(button->text());  // 发射信号，将按钮文本传递给MainWindow
    }
}
