#pragma once

#include "ACIMode.h"
#include <QtWidgets/QMainWindow>
#include "ui_ClockCounter.h"
#include "PreClick.h"
#include <QTimer>
#include <QTime>
#include "GlobalVari.h"

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
    void ShowACIModeWindow();
    void ShowPreClickWindow();
    void ClearPreClickInfo();
    void CountCallback();
    void WindowUpdateCallback();
    void ServerStatusCallback();

private:
    time_t CountTime;
    int PreClickCount;
    QTimer CountTimer;
    QTimer WindowUpdater;
    QPoint PreClickPosition;
    ACIMode aci_mode_window;
    Ui::ClockCounterClass ui;
    PreClick pre_click_window;
    QTimer ServerStatusChecker;
};
