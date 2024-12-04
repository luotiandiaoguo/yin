#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>

namespace Ui {
class DlgSettings;
}

class DlgSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSettings(QWidget *parent = nullptr);
    ~DlgSettings();

private slots:
    void on_resetButton_clicked();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();



signals:
    void kInkChanged(QColor color,int thickness);  // 新增信号，用于传递颜色信息



private:
    Ui::DlgSettings *ui;

    // 默认设置
    QColor defaultColor = Qt::black;
    int defaultThickness = 2;
    int defaultFontSize = 12;

    void loadSettings(); // 加载当前设置
    void resetSettings(); // 恢复默认设置
};

#endif // DLGSETTINGS_H
