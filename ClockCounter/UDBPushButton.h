#pragma once
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class UDBPushButton : public QPushButton
{
	Q_OBJECT;

public:
	UDBPushButton(QWidget* parent);
	~UDBPushButton();

protected:
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

signals:
	void db_clicked();
	void rclicked();
	void center_clicked();
};

