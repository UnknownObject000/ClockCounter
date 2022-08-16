#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_PreClick.h"
#include <QTimer>
#include <Windows.h>
#include <QKeyEvent>
#include <QCloseEvent>

class PreClick : public QMainWindow
{
    Q_OBJECT;

public:
    PreClick(QWidget* parent = nullptr);
    ~PreClick();

public:
    bool GetWindowStatus();
    int GetClickCount();
    QPoint GetCursorPosition();

public slots:
    void UpdateCursorPosition();
    void StartCursorTrack();
    void OnBnClickedOK();
    void OnBnClickedCancel();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

private:
    QTimer CursorUpdate;
    Ui::PreClickWindow ui;
    QPoint CursorPosition;
    int ClickCount;
    bool WindowStatus;
};

