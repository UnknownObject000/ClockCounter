#include "UDBPushButton.h"

UDBPushButton::UDBPushButton(QWidget* parent) : QPushButton(parent)
{
}

UDBPushButton::~UDBPushButton()
{
}

void UDBPushButton::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit db_clicked();
}

void UDBPushButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
    else if (event->button() == Qt::RightButton)
        emit rclicked();
    else if (event->button() == Qt::MiddleButton)
        emit center_clicked();
}
