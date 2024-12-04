#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgsettings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    WId hShow = ui->label->winId();
    inputs.inputInit((HWND)hShow);

    autoinput = false;
    ui->textEdit->setPlaceholderText("姓名");
    ui->textEdit->document()->setMaximumBlockCount(1);
    // 连接设置按钮的点击信号到槽函数
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::on_settingsButton_clicked);
    // 退一笔连接信号与槽函数
    connect(ui->Btn_undo, &QPushButton::clicked, this, &MainWindow::on_Btn_undo_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_kInkChanged(QColor color,int thickness)
{

    // 将新颜色传递给handsInput类，更新墨迹颜色
    inputs.setInkColor(color);



    // 传递给handsInput设置粗细
    inputs.setInkThickness(thickness);
}



//设置按钮实现
void MainWindow::on_settingsButton_clicked()
{
    // 创建并显示 DlgSettings 对话框
    DlgSettings settingsDialog(this);  // 传递父窗口

    settingsDialog.exec();  // 调用exec()使其成为模态对话框
}



void MainWindow::input_word(QString new_word)
{
    ui->textEdit->setFocus();//获取焦点
    if(ui->Btn_word1->text() == "")
        return;

    if(autoinput == true)//如果已经自动输入，则删掉自动输入的，然后输入点击选择的
        on_Btn_delete_clicked();

    QString str = ui->textEdit->toPlainText();

    int pos = ui->textEdit->textCursor().position();
    QString str_input = str.left(pos);
    str_input = str_input + new_word + str.right(str.length() - pos);

    ui->textEdit->clear();
    ui->textEdit->setFontUnderline(false);
    ui->textEdit->setText(str_input);

    QTextCursor cur = ui->textEdit->textCursor();
    cur.setPosition(pos + 1);
    ui->textEdit->setTextCursor(cur);

    on_Btn_clear_clicked();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    autoinput = false;
//    timer->start(2000);
    tempRlt.clear();
    inputs.RegDataEx(tempRlt);  // 获取候选词
//    qDebug() << tempRlt.size();

    // 填充 9 个候选词按钮
    for (int i = 0; i < 9; i++) {
        if (i < tempRlt.size()) {
            QString word = QString::fromUtf8(QByteArray(tempRlt[i].rlt));
            // 根据 i 设置不同的按钮文本
            if (i == 0) ui->Btn_word1->setText(word);
            if (i == 1) ui->Btn_word2->setText(word);
            if (i == 2) ui->Btn_word3->setText(word);
            if (i == 3) ui->Btn_word4->setText(word);
            if (i == 4) ui->Btn_word5->setText(word);
            if (i == 5) ui->Btn_word6->setText(word);
            if (i == 6) ui->Btn_word7->setText(word);
            if (i == 7) ui->Btn_word8->setText(word);
            if (i == 8) ui->Btn_word9->setText(word);
        } else {
            // 如果候选词数量不够 9 个，清空剩余按钮
            if (i == 0) ui->Btn_word1->setText("");
            if (i == 1) ui->Btn_word2->setText("");
            if (i == 2) ui->Btn_word3->setText("");
            if (i == 3) ui->Btn_word4->setText("");
            if (i == 4) ui->Btn_word5->setText("");
            if (i == 5) ui->Btn_word6->setText("");
            if (i == 6) ui->Btn_word7->setText("");
            if (i == 7) ui->Btn_word8->setText("");
            if (i == 8) ui->Btn_word9->setText("");
        }
    }
}


void MainWindow::on_Btn_delete_clicked()
{
    ui->textEdit->setFocus();//获取焦点
    int pos = ui->textEdit->textCursor().position();
    if(pos==0)
        return;

    QString str_old = ui->textEdit->toPlainText();
    QString str_new = "";
    if(!str_old.isEmpty())
    {
        str_new = str_old.left(pos-1) + str_old.right(str_old.length() - pos);
        ui->textEdit->setFontUnderline(false);
        ui->textEdit->setText(str_new);
        QTextCursor cur = ui->textEdit->textCursor();
        cur.setPosition(pos-1);
        ui->textEdit->setTextCursor(cur);
    }
}

void MainWindow::on_Btn_word1_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[0].rlt)));
}

void MainWindow::on_Btn_word2_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[1].rlt)));
}

void MainWindow::on_Btn_word3_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[2].rlt)));
}

void MainWindow::on_Btn_word4_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[3].rlt)));
}

void MainWindow::on_Btn_word5_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[4].rlt)));
}

void MainWindow::on_Btn_word6_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[5].rlt)));
}

void MainWindow::on_Btn_word7_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[6].rlt)));
}

void MainWindow::on_Btn_word8_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[7].rlt)));
}

void MainWindow::on_Btn_word9_clicked()
{
    input_word(QString::fromUtf8(QByteArray(tempRlt[8].rlt)));
}

void MainWindow::on_Btn_clear_clicked()
{
    ui->textEdit->setFocus();//获取焦点
    inputs.clear();// Only 删除笔触
    ui->label->clear();

    ui->Btn_word1->setText("");
    ui->Btn_word2->setText("");
    ui->Btn_word3->setText("");
    ui->Btn_word4->setText("");
    ui->Btn_word5->setText("");
    ui->Btn_word6->setText("");
    ui->Btn_word7->setText("");
    ui->Btn_word8->setText("");
    ui->Btn_word9->setText("");

    tempRlt.clear();
}


void MainWindow::on_Btn_undo_clicked()
{
    qDebug() << "退一笔按钮被点击了";  // 调用handsInput类中的退一笔方法
    inputs.undoLastStroke();  // 调用 handsInput 类中的 undoLastStroke 方法

    // 清除候选词按钮的文本
    ui->Btn_word1->setText("");
    ui->Btn_word2->setText("");
    ui->Btn_word3->setText("");
    ui->Btn_word4->setText("");
    ui->Btn_word5->setText("");
    ui->Btn_word6->setText("");
    ui->Btn_word7->setText("");
    ui->Btn_word8->setText("");
    ui->Btn_word9->setText("");

    // 更新候选词（调用你之前的代码来填充候选词按钮）
    tempRlt.clear();
    inputs.RegDataEx(tempRlt);  // 获取候选词

    // 填充候选词按钮
    for (int i = 0; i < 9; i++) {
        if (i < tempRlt.size()) {
            QString word = QString::fromUtf8(QByteArray(tempRlt[i].rlt));
            if (i == 0) ui->Btn_word1->setText(word);
            if (i == 1) ui->Btn_word2->setText(word);
            if (i == 2) ui->Btn_word3->setText(word);
            if (i == 3) ui->Btn_word4->setText(word);
            if (i == 4) ui->Btn_word5->setText(word);
            if (i == 5) ui->Btn_word6->setText(word);
            if (i == 6) ui->Btn_word7->setText(word);
            if (i == 7) ui->Btn_word8->setText(word);
            if (i == 8) ui->Btn_word9->setText(word);
        } else {
            // 清空剩余按钮
            if (i == 0) ui->Btn_word1->setText("");
            if (i == 1) ui->Btn_word2->setText("");
            if (i == 2) ui->Btn_word3->setText("");
            if (i == 3) ui->Btn_word4->setText("");
            if (i == 4) ui->Btn_word5->setText("");
            if (i == 5) ui->Btn_word6->setText("");
            if (i == 6) ui->Btn_word7->setText("");
            if (i == 7) ui->Btn_word8->setText("");
            if (i == 8) ui->Btn_word9->setText("");
        }
    }
}

