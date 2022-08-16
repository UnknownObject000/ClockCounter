#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ClockCounter.h"
#include "PreClick.h"
#include <QTimer>
#include <QTime>

class ClockCounter : public QMainWindow
{
    Q_OBJECT

public:
    ClockCounter(QWidget *parent = nullptr);
    ~ClockCounter();

public:
    void MouseClick(int cnt, QPoint point);

public slots:
    void StartTimer();
    void StopTimer();
    void ShowPreClickWindow();
    void ClearPreClickInfo();
    void CountCallback();
    void WindowUpdateCallback();

private:
    time_t CountTime;
    int PreClickCount;
    QTimer CountTimer;
    QTimer WindowUpdater;
    QPoint PreClickPosition;
    Ui::ClockCounterClass ui;
    PreClick pre_click_window;
};
