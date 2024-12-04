#ifndef HANDSINPUT_H
#define HANDSINPUT_H

#include <QWidget>
#include <msinkaut_i.c>  // COM 接口定义头文件，包含手写识别相关接口
#include <msinkaut.h>   // COM 接口头文件，包含 IInkCollector、IInkRecognizerContext 等接口定义
//#include <inkobj.h>  // 包含 IInkStroke 定义
//#include <InkObj.h>  // 包含 IInkStroke 等相关接口
#include <vector>
#include <stack>

using namespace std;

typedef struct tag_InputRlt
{
    char rlt[256];
}InputRlt;

typedef vector <InputRlt> InPutRltS;

class handsInput : public QWidget
{
    Q_OBJECT
public:
    explicit handsInput(QWidget *parent = 0);
    ~handsInput();

    IInkCollector *     kIInkCollector;   //指向 IInkCollector 接口的指针，负责采集手写输入的墨迹数据
    IInkDisp *          kIInkDisp;   //指向 IInkDisp 接口的指针，表示手写输入的墨迹数据对象
    IInkRecognizerContext *   kIInkRecoContext;  //指向 IInkRecognizerContext 接口的指针，负责与手写识别引擎交互，进行手写识别
    void inputInit( HWND hwnd );
    void RegDataEx( InPutRltS & Rlts );
    void releaseUp();
    void clear();
    void setInkColor(const QColor& color); //设置墨迹颜色
    void undoLastStroke();  // 退一笔功能
    void setInkThickness(int thickness);  // 设置墨迹粗细

private:
    std::stack<IInkStrokes*> strokeHistory;  // 用来保存笔画的历史栈
};

#endif // HANDSINPUT_H
