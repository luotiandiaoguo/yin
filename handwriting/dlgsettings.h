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
    void kInkChanged(QColor color,int thickness);  // 改变墨迹的颜色和粗细
    void fontSizeChanged(int fontSize); //改变候选字体颜色


private:
    Ui::DlgSettings *ui;



    void loadSettings(); // 加载当前设置
    void resetSettings(); // 恢复默认设置
};

#endif // DLGSETTINGS_H
