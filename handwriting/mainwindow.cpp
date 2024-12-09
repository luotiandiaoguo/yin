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


    // 获取 QStackedWidget 和按钮
    QStackedWidget *stackedWidget = ui->stackedWidget;

    // 连接按钮与槽函数
    connect(ui->chineseButton, &QPushButton::clicked, this, [=]() {
        // 点击中文按钮时，隐藏 QStackedWidget，并显示 MainWindow 的默认内容
        stackedWidget->hide();  // 隐藏 QStackedWidget
        // 其他操作可以设置为默认显示内容，比如清空某些输入框等
    });

    connect(ui->englishButton, &QPushButton::clicked, this, [=]() {
        // 点击英文按钮时，显示 QStackedWidget，并切换到英文页面
        stackedWidget->show();  // 显示 QStackedWidget
        stackedWidget->setCurrentWidget(ui->englishPage);  // 切换到英文页面
    });

    connect(ui->numberButton, &QPushButton::clicked, this, [=]() {
        // 点击数字按钮时，显示 QStackedWidget，并切换到数字页面
        stackedWidget->show();  // 显示 QStackedWidget
        stackedWidget->setCurrentWidget(ui->numberPage);  // 切换到数字页面
    });

    connect(ui->punctuationButton, &QPushButton::clicked, this, [=]() {
        // 点击标点按钮时，显示 QStackedWidget，并切换到标点页面
        stackedWidget->show();  // 显示 QStackedWidget
        stackedWidget->setCurrentWidget(ui->punctuationPage);  // 切换到标点页面
    });

    // 默认情况下隐藏 QStackedWidget
    stackedWidget->hide();



    // 创建 EnglishWidget 实例
    englishWidget = new EnglishWidget(this);

    // 连接Btn_a到Btn_z和Btn_A到Btn_Z的点击信号到onBtnClicked槽函数
    // 创建按钮数组，按字母顺序排列,避免相同代码重复执行
    QList<QPushButton*> englishButtons = {
        ui->Btn_a, ui->Btn_b, ui->Btn_c, ui->Btn_d, ui->Btn_e, ui->Btn_f,
        ui->Btn_g, ui->Btn_h, ui->Btn_i, ui->Btn_j, ui->Btn_k, ui->Btn_l,
        ui->Btn_m, ui->Btn_n, ui->Btn_o, ui->Btn_p, ui->Btn_q, ui->Btn_r,
        ui->Btn_s, ui->Btn_t, ui->Btn_u, ui->Btn_v, ui->Btn_w, ui->Btn_x,
        ui->Btn_y, ui->Btn_z,
        ui->Btn_A, ui->Btn_B, ui->Btn_C, ui->Btn_D, ui->Btn_E, ui->Btn_F,
        ui->Btn_G, ui->Btn_H, ui->Btn_I, ui->Btn_J, ui->Btn_K, ui->Btn_L,
        ui->Btn_M, ui->Btn_N, ui->Btn_O, ui->Btn_P, ui->Btn_Q, ui->Btn_R,
        ui->Btn_S, ui->Btn_T, ui->Btn_U, ui->Btn_V, ui->Btn_W, ui->Btn_X,
        ui->Btn_Y, ui->Btn_Z
   };

   // 遍历所有按钮，并连接信号
    for (QPushButton* button : englishButtons) {
        connect(button, &QPushButton::clicked, englishWidget, &EnglishWidget::onEnglishBtnClicked);
   }
//    connect(ui->Btn_a, &QPushButton::clicked, englishWidget, &EnglishWidget::onBtnClicked);

    // 连接 EnglishWidget 的信号到主窗口的槽函数
    connect(englishWidget, &EnglishWidget::englishClicked, this, &MainWindow::onCharacterClicked);


    // 创建 NumberWidget 实例
    numberWidget = new NumberWidget(this);
    QList<QPushButton*> numberButtons = {
        ui->Btn_0, ui->Btn_1, ui->Btn_2, ui->Btn_3, ui->Btn_4, ui->Btn_5,ui->Btn_6, ui->Btn_7, ui->Btn_8, ui->Btn_9,
        ui->Btn_one, ui->Btn_two, ui->Btn_three ,ui->Btn_four , ui->Btn_five, ui->Btn_six, ui->Btn_seven, ui->Btn_eight,
        ui->Btn_nine, ui->Btn_ten, ui->Btn_zero,
        ui->Btn_One, ui->Btn_Two, ui->Btn_Three , ui->Btn_Four , ui->Btn_Five, ui->Btn_Six, ui->Btn_Seven, ui->Btn_Eight,
        ui->Btn_Nine, ui->Btn_Ten, ui->Btn_Hundred, ui->Btn_Thousand, ui->Btn_TenThousand
   };

   // 遍历所有按钮，并连接信号
    for (QPushButton* button : numberButtons) {
        connect(button, &QPushButton::clicked, englishWidget, &EnglishWidget::onEnglishBtnClicked);
   }

    // 连接 NumberWidget 的信号到主窗口的槽函数
    connect(numberWidget, &NumberWidget::numberClicked, this, &MainWindow::onCharacterClicked);



    // 创建 PunctuationWidget 实例
    punctuationWidget = new PunctuationWidget(this);
    QList<QPushButton*> punctuationButtons = {
        ui->Btn_comma, ui->Btn_period, ui->Btn_dash, ui->Btn_semicolon, ui->Btn_EqualsSign, ui->Btn_SquareBracketsLeft,
        ui->Btn_SquareBracketsRight, ui->Btn_asterisk, ui->Btn_backslash, ui->Btn_bookTitleMarksLeft, ui->Btn_bookTitleMarksRight,
        ui->Btn_bracesLeft, ui->Btn_bracesRight, ui->Btn_colon, ui->Btn_doubleQuotationLeft, ui->Btn_doubleQuotationRight,
        ui->Btn_ellipsis, ui->Btn_emDash, ui->Btn_emphasisMark, ui->Btn_exclamationMark, ui->Btn_greaterThanSign, ui->Btn_tilde,
        ui->Btn_lessThanSign, ui->Btn_minusSign, ui->Btn_or, ui->Btn_parenthesesLeft, ui->Btn_parenthesesRight,ui->Btn_percentSign,
        ui->Btn_plusSign, ui->Btn_poundSign, ui->Btn_questionMark, ui->Btn_singleQuotationLeft, ui->Btn_slash, ui->Btn_singleQuotationRight
   };

   // 遍历所有按钮，并连接信号
    for (QPushButton* button : punctuationButtons) {
        connect(button, &QPushButton::clicked, englishWidget, &EnglishWidget::onEnglishBtnClicked);
   }

    // 连接 NumberWidget 的信号到主窗口的槽函数
    connect(punctuationWidget, &PunctuationWidget::punctuationClicked, this, &MainWindow::onCharacterClicked);


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

//候选字体颜色改变实现
void MainWindow::updateButtonFontSize(int fontSize)
{
    QFont font;
    font.setPointSize(fontSize);

    // 更新所有候选框按钮的字体大小
    ui->Btn_word1->setFont(font);
    ui->Btn_word2->setFont(font);
    ui->Btn_word3->setFont(font);
    ui->Btn_word4->setFont(font);
    ui->Btn_word5->setFont(font);
    ui->Btn_word6->setFont(font);
    ui->Btn_word7->setFont(font);
    ui->Btn_word8->setFont(font);
    ui->Btn_word9->setFont(font);
}


//设置按钮实现
void MainWindow::on_settingsButton_clicked()
{
    // 创建并显示 DlgSettings 对话框
    DlgSettings settingsDialog(this);  // 传递父窗口

    // 连接字体大小改变信号到槽函数
   connect(&settingsDialog, &DlgSettings::fontSizeChanged, this, &MainWindow::updateButtonFontSize);
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


void MainWindow::onCharacterClicked(const QString &character)
{
    ui->textEdit->setFocus();//获取焦点
    // 在 textEdit 中插入点击的字符
    ui->textEdit->insertPlainText(character);
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

