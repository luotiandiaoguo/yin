#ifndef ENGLISHWIDGET_H
#define ENGLISHWIDGET_H

#include <QWidget>
#include <QPushButton>

class EnglishWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnglishWidget(QWidget *parent = nullptr);

signals:
    // 定义一个信号，用于将点击的字符传递到主界面
    void englishClicked(const QString &englishChar);

public slots:
    // 按钮点击槽函数
    void onEnglishBtnClicked();


};

#endif // ENGLISHWIDGET_H
