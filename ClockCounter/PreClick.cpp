#include "PreClick.h"

PreClick::PreClick(QWidget* parent) : QMainWindow(parent)
{
	ClickCount = 1;
	WindowStatus = false;
	CursorPosition = QPoint(0, 0);
	ui.setupUi(this);
	ui.ClickCount->setValue(1);
	ui.ClickCount->setMinimum(1);
	ui.ClickCount->setMaximum(10);
	connect(ui.BtnGetPos, &QPushButton::clicked, this, &PreClick::StartCursorTrack);
	connect(ui.BtnOK, &QPushButton::clicked, this, &PreClick::OnBnClickedOK);
	connect(ui.BtnCancel, &QPushButton::clicked, this, &PreClick::OnBnClickedCancel);
	connect(&CursorUpdate, &QTimer::timeout, this, &PreClick::UpdateCursorPosition);
	CursorUpdate.setInterval(50);
	this->grabKeyboard();
}

PreClick::~PreClick()
{
}

bool PreClick::GetWindowStatus()
{
	return WindowStatus;
}

int PreClick::GetClickCount()
{
	return ClickCount;
}

QPoint PreClick::GetCursorPosition()
{
	return CursorPosition;
}

void PreClick::UpdateCursorPosition()
{
	POINT point;
	GetCursorPos(&point);
	ui.PosX->setText(QString::asprintf("%ld", point.x));
	ui.PosY->setText(QString::asprintf("%ld", point.y));
}

void PreClick::StartCursorTrack()
{
	if (CursorUpdate.isActive())
	{
		CursorUpdate.stop();
		ui.BtnGetPos->setText("获取坐标");
	}
	else
	{
		CursorUpdate.start();
		ui.BtnGetPos->setText("停止获取");
	}
}

void PreClick::OnBnClickedOK()
{
	CursorPosition = QPoint(ui.PosX->toPlainText().toInt(), ui.PosY->toPlainText().toInt());
	ClickCount = ui.ClickCount->value();
	WindowStatus = true;
	this->hide();
}

void PreClick::OnBnClickedCancel()
{
	WindowStatus = false;
	this->hide();
}

void PreClick::keyPressEvent(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Space) && CursorUpdate.isActive())
	{
		CursorUpdate.stop();
		ui.BtnGetPos->setText("获取坐标");
	}
}

void PreClick::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}
