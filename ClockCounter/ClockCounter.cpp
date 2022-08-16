#include "ClockCounter.h"

ClockCounter::ClockCounter(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    PreClickCount = 0;
    PreClickPosition = QPoint(0, 0);
    ui.SpliterHourMinute->Init(UDateTimeSpliter::Type::Time);
    ui.SpliterMinuteSecond->Init(UDateTimeSpliter::Type::Time);
    ui.SpliterSecondMS->Init(UDateTimeSpliter::Type::Dots);
    connect(ui.BtnStartTimer, &QPushButton::clicked, this, &ClockCounter::StartTimer);
    connect(ui.BtnStopTimer, &QPushButton::clicked, this, &ClockCounter::StopTimer);
    connect(ui.BtnGetPreclickPos, &QPushButton::clicked, this, &ClockCounter::ShowPreClickWindow);
    connect(ui.BtnClearPreclickPos, &QPushButton::clicked, this, &ClockCounter::ClearPreClickInfo);
    connect(&CountTimer, &QTimer::timeout, this, &ClockCounter::CountCallback);
    connect(&WindowUpdater, &QTimer::timeout, this, &ClockCounter::WindowUpdateCallback);
    CountTimer.setInterval(1);
    WindowUpdater.setInterval(50);
    CountTime = 0;
}

ClockCounter::~ClockCounter()
{
}

void ClockCounter::MouseClick(int cnt, QPoint point)
{
    for (int i = 0; i < cnt; i++)
    {
        this->setWindowTitle(QString::asprintf("软件执行计时器: 执行位于(%d, %d)的第%d次预点击", point.x(), point.y(), i));
        SetCursorPos(point.x(), point.y());
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(500);
    }
    return;
}

void ClockCounter::StartTimer()
{
    if (CountTime != 0)
    {
        ui.BtnStartTimer->setText("开始计时");
        CountTime = -1;
        CountCallback();
        if(PreClickCount!=0)
            this->setWindowTitle("软件执行计时器: 预点击指令已激活");
        else
            this->setWindowTitle("软件执行计时器");
    }
    else
    {
        if (PreClickCount > 0)
            MouseClick(PreClickCount, PreClickPosition);
        CountTimer.start();
        this->setWindowTitle("软件执行计时器: 正在计时");
    }
}

void ClockCounter::StopTimer()
{
    CountTimer.stop();
    ui.BtnStartTimer->setText("重置计时器");
    this->setWindowTitle("软件执行计时器: 计时已停止");
}

void ClockCounter::ShowPreClickWindow()
{
    if (!pre_click_window.isActiveWindow())
    {
        pre_click_window.show();
        pre_click_window.activateWindow();
        pre_click_window.setWindowState((pre_click_window.windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
        this->hide();
        WindowUpdater.start();
    }
}

void ClockCounter::ClearPreClickInfo()
{
    PreClickCount = 0;
    PreClickPosition = QPoint(0, 0);
    this->setWindowTitle("软件执行计时器");
    MessageBox(NULL, L"预点击坐标已清空", L"提示", MB_OK | MB_ICONINFORMATION);
}

void ClockCounter::CountCallback()
{
    CountTime++;
    int hour = (CountTime / 1000) / 3600;
    int minute = ((CountTime / 1000) / 60) - (hour * 60);
    int second = (CountTime / 1000) - (hour * 3600) - (minute * 60);
    int millsecond = CountTime - (hour * 3600 * 1000) - (minute * 60 * 1000) - (second * 1000);
    ui.NumHour01->setNumber(hour / 10);
    ui.NumHour02->setNumber(hour % 10);
    ui.NumMinute01->setNumber(minute / 10);
    ui.NumMinute02->setNumber(minute % 10);
    ui.NumSecond01->setNumber(second / 10);
    ui.NumSecond02->setNumber(second % 10);
    ui.NumMillSec01->setNumber(millsecond / 100);
    ui.NumMillSec02->setNumber((millsecond / 10) % 10);
    ui.NumMillSec03->setNumber((millsecond % 100) % 10);
    return;
}

void ClockCounter::WindowUpdateCallback()
{
    if (!pre_click_window.isVisible())
    {
        WindowUpdater.stop();
        this->show();
        this->activateWindow();
        this->setWindowState((this->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
        if (pre_click_window.GetWindowStatus())
        {
            PreClickCount = pre_click_window.GetClickCount();
            PreClickPosition = pre_click_window.GetCursorPosition();
            this->setWindowTitle("软件执行计时器: 预点击指令已激活");
        }
    }
}
