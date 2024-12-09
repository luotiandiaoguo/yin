#include "englishwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

EnglishWidget::EnglishWidget(QWidget *parent)
    : QWidget(parent)
{

}

void EnglishWidget::onEnglishBtnClicked()
{
    // 获取发送信号的按钮的文本
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        emit englishClicked(button->text());  // 发射信号，将按钮文本传递给MainWindow
    }
}
