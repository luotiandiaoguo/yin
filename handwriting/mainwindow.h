#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QRect>
#include <QTextCursor>
#include <QDebug>
#include "handsinput.h"
#include "dlgsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /////
    handsInput inputs;
    InPutRltS tempRlt;
    QTimer *timer;      //自动输入定时器
    bool autoinput;     //是否自动输入
    void input_word(QString new_word);  //输入文字
    ////////////
protected:
    void mouseReleaseEvent(QMouseEvent *e);
private slots:
    void on_Btn_delete_clicked();
    void on_Btn_word1_clicked();
    void on_Btn_word2_clicked();
    void on_Btn_word3_clicked();
    void on_Btn_word4_clicked();
    void on_Btn_word5_clicked();
    void on_Btn_word6_clicked();
    void on_Btn_word7_clicked();
    void on_Btn_word8_clicked();
    void on_Btn_word9_clicked();
    //重写
    void on_Btn_clear_clicked();




private slots:
    void on_settingsButton_clicked(); // 设置按钮槽函数
    void on_Btn_undo_clicked();  // 声明退一笔按钮的槽函数
public slots:
    void on_kInkChanged(QColor color, int thickness); //改变墨迹颜色




private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
