#include "punctuationwidget.h"
#include <QPushButton>
PunctuationWidget::PunctuationWidget(QWidget *parent) : QWidget(parent)
{

}
void PunctuationWidget::onPunctuationBtnClicked()
{
    // 获取发送信号的按钮的文本
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        emit punctuationClicked(button->text());  // 发射信号，将按钮文本传递给MainWindow
    }
}
