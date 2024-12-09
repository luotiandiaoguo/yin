#include "handsinput.h"
#include <QAxObject>
#include <QDebug>

handsInput::handsInput(QWidget *parent) : QWidget(parent)
{

}

handsInput::~handsInput()
{
    releaseUp();
}

void handsInput::inputInit(HWND hwnd)
{
    if(NULL == hwnd)
        return;
    kIInkCollector = NULL;
    kIInkDisp = NULL;
    kIInkRecoContext = NULL;
    // 初始化 COM 接口
    CoInitialize(NULL);
    HRESULT hr;

    // 使用默认的识别器创建一个识别上下文
    // 这个上下文会被所有的识别对象使用
    hr = CoCreateInstance(CLSID_InkRecognizerContext,NULL, CLSCTX_INPROC_SERVER,IID_IInkRecognizerContext,(void **) &kIInkRecoContext);
    if (FAILED(hr)) {
        qDebug() << "没有安装手写识别软件=";
        return ;
    }
    // 创建一个墨迹收集对象
    hr = CoCreateInstance(CLSID_InkCollector,NULL, CLSCTX_INPROC_SERVER,IID_IInkCollector,(void **) &kIInkCollector);
    if (FAILED(hr))
        return ;

    // 获取墨迹对象的指针
    hr = kIInkCollector->get_Ink(&kIInkDisp);
    if (FAILED(hr))
        return ;

    // 将墨迹对象关联一个 hWnd 的窗口
    hr = kIInkCollector->put_hWnd((long)hwnd);
    if (FAILED(hr))
        return ;

    // 设置颜色
    IInkDrawingAttributes* p;
    if (SUCCEEDED(kIInkCollector->get_DefaultDrawingAttributes(&p)))
    {
        p->put_Color(RGB(0,0,0));
        p->put_Width(100.0); //墨迹粗细
    }



    // 打开墨迹输入的开关
    hr = kIInkCollector->put_Enabled(VARIANT_TRUE);
    if (FAILED(hr))
        return ;

#if 1
    //设置手写只识别为一个字
    IInkRecognizerGuide *RecognizerGuide;
    hr = CoCreateInstance(CLSID_InkRecognizerGuide,NULL, CLSCTX_INPROC_SERVER,IID_IInkRecognizerGuide,(void **) &RecognizerGuide);
    if (FAILED(hr))
        return;
    InkRecoGuide recoguide;
    RECT rect;
    rect.bottom = 2;//不能为1
    rect.left = 0;
    rect.right = 2;//不能为1
    rect.top = 0;

    recoguide.rectWritingBox = rect;
    recoguide.rectDrawnBox = rect;
    recoguide.cRows = 3;//不要过大
    recoguide.cColumns = 3;
    recoguide.midline = -1;
    RecognizerGuide->put_GuideData(recoguide);
    kIInkRecoContext->putref_Guide(RecognizerGuide);
#endif
}

void handsInput::RegDataEx(InPutRltS &Rlts)
{
    // 清空结果
    if (!Rlts.empty()) {
        Rlts.clear();
    }
     // 保存当前的笔画状态到历史栈
    IInkStrokes* pIInkStrokes = NULL;
    HRESULT hr = kIInkDisp->get_Strokes(&pIInkStrokes);

    if (FAILED(hr)) {
        // 错误处理
        qDebug() << "Failed to get strokes";
        return;
    }

    strokeHistory.push(pIInkStrokes);  // 保存到栈中

    // 将笔触收集器传递给识别器
    hr = kIInkRecoContext->putref_Strokes(pIInkStrokes);
    if (FAILED(hr)) {
        pIInkStrokes->Release();
        qDebug() << "Failed to set strokes to recognizer";
        return;
    }

    // 识别
    IInkRecognitionResult* pIInkRecoResult = NULL;
    InkRecognitionStatus RecognitionStatus = IRS_NoError;

    hr = kIInkRecoContext->Recognize(&RecognitionStatus, &pIInkRecoResult);
    if (FAILED(hr) || pIInkRecoResult == NULL) {
        pIInkStrokes->Release();
        qDebug() << "Recognition failed";
        return;
    }

    // 获取可能的所有识别结果
    IInkRecognitionAlternates* spIInkRecoAlternates = NULL;
    hr = pIInkRecoResult->AlternatesFromSelection(0, -1, 10, &spIInkRecoAlternates);
    pIInkRecoResult->Release();

    if (FAILED(hr) || spIInkRecoAlternates == NULL) {
        pIInkStrokes->Release();
        qDebug() << "Failed to get alternates";
        return;
    }

    long lCount = 0;
    hr = spIInkRecoAlternates->get_Count(&lCount);
    if (FAILED(hr) || lCount == 0) {
        spIInkRecoAlternates->Release();
        pIInkStrokes->Release();
        qDebug() << "No recognition alternates available";
        return;
    }

    // 获取所有识别结果
    IInkRecognitionAlternate* pIInkRecoAlternate = NULL;
    for (LONG iItem = 0; iItem < lCount && iItem < 10; iItem++) {
        hr = spIInkRecoAlternates->Item(iItem, &pIInkRecoAlternate);
        if (FAILED(hr)) {
            continue;
        }

        BSTR bstr = NULL;
        hr = pIInkRecoAlternate->get_String(&bstr);
        if (SUCCEEDED(hr) && bstr != NULL) {
            InputRlt temp = {0};
            QString str = QString::fromWCharArray(bstr);
            strcpy(temp.rlt, str.toUtf8().data());
            Rlts.push_back(temp);
            SysFreeString(bstr);  // 释放BSTR
        }
        pIInkRecoAlternate->Release();
    }

    spIInkRecoAlternates->Release();
    pIInkStrokes->Release();
}


void handsInput::releaseUp()
{
    if (kIInkRecoContext != NULL)
    {
        kIInkRecoContext->Release();
        kIInkRecoContext = NULL;
    }

    if (kIInkDisp != NULL)
    {
        kIInkDisp->Release();
        kIInkDisp = NULL;
    }

    if (kIInkCollector != NULL)
    {
        kIInkCollector->Release();
        kIInkCollector = NULL;
    }
    CoUninitialize();
}

void handsInput::clear()
{
    // 清除所有的笔触
    kIInkDisp->DeleteStrokes(0);
    // 清除文字
    //	m_ctrListShow.ResetContent();
    // 重绘画板
    //Invalidate();
}

// 设置墨迹的颜色
void handsInput::setInkColor(const QColor &color)
{
    IInkDrawingAttributes* p = NULL;
    if (SUCCEEDED(kIInkCollector->get_DefaultDrawingAttributes(&p)))
    {
        // 设置墨迹的颜色
        p->put_Color(RGB(color.red(), color.green(), color.blue()));
    }
}

//设置墨迹粗细函数实现
void handsInput::setInkThickness(int thickness)
{
    IInkDrawingAttributes* p = NULL;
    if (SUCCEEDED(kIInkCollector->get_DefaultDrawingAttributes(&p)))
    {
        // 设置墨迹的粗细
            p->put_Width(thickness);

    }
}




// 退一笔功能实现
void handsInput::undoLastStroke()
{
    if (strokeHistory.empty()) {
        qDebug() << "No strokes to undo";
        return;
    }

    // 获取栈顶的笔画
    IInkStrokes* pIInkStrokes = strokeHistory.top();
    strokeHistory.pop();  // 移除栈顶的笔画



    // 删除最后一笔
    HRESULT hr = kIInkDisp->DeleteStrokes(pIInkStrokes);
    if (FAILED(hr)) {
        qDebug() << "Failed to delete strokes";
        return;
    }

    // 重新清空手写区域并更新显示
    clear();
    pIInkStrokes->Release();  // 释放资源
}


