#pragma once
#include "ACIFullVersion.h"
#include <QtWidgets/QMainWindow>
#include "ui_ACIMode.h"
#include <QTimer>
#include <QKeyEvent>
#include <QCloseEvent>
#include <Windows.h>
#include "GlobalVari.h"

class ACIMode : public QMainWindow
{
    Q_OBJECT;

public:
    ACIMode(QWidget* parent = nullptr);
    ~ACIMode();

public:
    int ProcessRadio(bool client, bool server);
    void CleanUp();
    void StartACISystem();
    int GetOperationMode();
    void RequestRemoteTimer();

protected:
    void closeEvent(QCloseEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    int OperationMode;
    ACIClient* client;
    ACIServer* server;
    bool ServerRunning;
    Ui::ACIModeWindow ui;
};

std::string RequestedTimerStart(std::string json);