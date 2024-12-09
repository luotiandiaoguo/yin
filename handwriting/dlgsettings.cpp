#include "DlgSettings.h"
#include "ui_DlgSettings.h"
#include "mainwindow.h"
#include "qtimer.h"
DlgSettings::DlgSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSettings)
{
    ui->setupUi(this);

    // 手动连接按钮信号到槽函数
    connect(ui->resetButton, &QPushButton::clicked, this, &DlgSettings::on_resetButton_clicked);
    connect(ui->cancelButton,&QPushButton::clicked, this, &DlgSettings::on_cancelButton_clicked);
    connect(ui->confirmButton, &QPushButton::clicked, this, &DlgSettings::on_confirmButton_clicked);


    // 初始化颜色选择
//    ui->colorGroupBox->addButton(ui->radioButtonRed, 0);
//    ui->colorGroupBox->addButton(ui->radioButtonGreen, 1);
//    ui->colorGroupBox->addButton(ui->radioButtonBlue, 2);
//    ui->colorGroupBox->addButton(ui->radioButtonYellow, 3);
//    ui->colorGroupBox->addButton(ui->radioButtonBlack, 4);

    // 加载设置
    loadSettings();

    // 使用 qobject_cast 转换 parent 为 MainWindow* 类型
       MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
       if (mainWindow) {
           // 连接信号到 MainWindow 的槽函数
           connect(this, &DlgSettings::kInkChanged, mainWindow, &MainWindow::on_kInkChanged);
       } else {
           qDebug() << "Parent widget is not of type MainWindow";
       }
}

DlgSettings::~DlgSettings()
{
    delete ui;
}

//加载默认设置
void DlgSettings::loadSettings()
{
    // 加载默认或当前设置
    ui->radioButtonBlack->setChecked(true); // 默认黑色
    ui->thicknessComboBox->setCurrentIndex(1); // 默认粗细
    ui->fontSizeComboBox->setCurrentIndex(1); // 默认字号


}

void DlgSettings::resetSettings()
{
    // 恢复默认设置
    ui->radioButtonBlack->setChecked(true);  //默认墨迹黑色
    ui->thicknessComboBox->setCurrentIndex(1); //默认墨迹粗细为中
    ui->fontSizeComboBox->setCurrentIndex(1); //默认候选字体大小为中等
}

void DlgSettings::on_resetButton_clicked()
{
    resetSettings();
}

void DlgSettings::on_confirmButton_clicked()
{
    QColor selectedColor;

    // 判断哪个单选按钮被选中，并设置颜色
    if (ui->radioButtonRed->isChecked()) {
        selectedColor = QColor(Qt::red);  // 红色
    } else if (ui->radioButtonGreen->isChecked()) {
        selectedColor = QColor(Qt::green);  // 绿色
    } else if (ui->radioButtonBlue->isChecked()) {
        selectedColor = QColor(Qt::blue);  // 蓝色
    } else if (ui->radioButtonYellow->isChecked()) {
        selectedColor = QColor(Qt::yellow);  // 黄色
    } else if (ui->radioButtonBlack->isChecked()) {
        selectedColor = QColor(Qt::black);  // 黑色
    }

    // 获取粗细选择
    int thicknessIndex = ui->thicknessComboBox->currentIndex();  // 0: 细, 1: 中, 2: 粗

    // 根据索引设置墨迹粗细
    int thickness = 100;  // 默认中等粗细
    if (thicknessIndex == 0) {
        thickness = 10;  // 细
    } else if (thicknessIndex == 1) {
        thickness = 100;  // 中
    } else if (thicknessIndex == 2) {
        thickness = 300;  // 粗
    }

    // 发出信号，将颜色传递出去
    emit kInkChanged(selectedColor, thickness);


    // 获取字体大小
    int fontSizeIndex = ui->fontSizeComboBox->currentIndex();
    // 根据索引设置字体粗细
    int fontSize = 14;  // 默认中等粗细
    if (fontSizeIndex == 0) {
        fontSize = 10;  // 细
    } else if (fontSizeIndex == 1) {
        fontSize = 14;  // 中
    } else if (fontSizeIndex == 2) {
        fontSize = 20;  // 粗
    }
    // 发出字体大小改变信号
    emit fontSizeChanged(fontSize);


    // 关闭设置对话框
    accept();

}






void DlgSettings::on_cancelButton_clicked()
{
    reject();
}
