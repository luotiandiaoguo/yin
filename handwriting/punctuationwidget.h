#ifndef PUNCTUATIONWIDGET_H
#define PUNCTUATIONWIDGET_H

#include <QWidget>

class PunctuationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PunctuationWidget(QWidget *parent = nullptr);

signals:
    // 定义一个信号，用于将点击的字符传递到主界面
    void punctuationClicked(const QString &punctuationChar);

public slots:
    // 按钮点击槽函数
    void onPunctuationBtnClicked();
};

#endif // PUNCTUATIONWIDGET_H
