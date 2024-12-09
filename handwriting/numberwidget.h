#ifndef NUMBERWIDGET_H
#define NUMBERWIDGET_H

#include <QWidget>

class NumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumberWidget(QWidget *parent = nullptr);

signals:
    // 定义一个信号，用于将点击的字符传递到主界面
    void numberClicked(const QString &numberChar);

public slots:
    // 按钮点击槽函数
    void onNumberBtnClicked();
};

#endif // NUMBERWIDGET_H
