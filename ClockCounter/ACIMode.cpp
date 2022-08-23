#include "ACIMode.h"

ACIMode::ACIMode(QWidget* parent) : QMainWindow(parent)
{
	client = nullptr;
	server = nullptr;
	OperationMode = -3;
	ServerRunning = false;
	ui.setupUi(this);
	ui.Workmode_Client->setChecked(true);
	ui.Workmode_Server->setChecked(false);
	ui.IP->installEventFilter(this);
	ui.PortNumber->installEventFilter(this);
	connect(ui.BtnStart, &QCommandLinkButton::clicked, this, &ACIMode::StartACISystem);
}

ACIMode::~ACIMode()
{
}

int ACIMode::ProcessRadio(bool client, bool server)
{
	if (client && server)
		return -1;
	else if ((!client) && (!server))
		return -2;
	else if (client)
		return 0;
	else
		return 1;
}

void ACIMode::CleanUp()
{
	if (client != nullptr)
	{
		delete client;
		client = nullptr;
	}
	if (server != nullptr)
	{
		server->Stop();
		delete server;
		server = nullptr;
	}
	OperationMode = -3;
}

void ACIMode::StartACISystem()
{
	OperationMode = ProcessRadio(ui.Workmode_Client->isChecked(), ui.Workmode_Server->isChecked());
	switch (OperationMode)
	{
	case 0:
	{
		CleanUp();
		OperationMode = 0;
		client = new ACIClient(ui.PortNumber->toPlainText().toInt(), ui.IP->toPlainText().toStdString());
		this->hide();
		break;
	}
	case 1:
	{
		if (ServerRunning)
		{
			CleanUp();
			ServerRunning = false;
			ui.BtnStart->setText("启动通信系统");
		}
		else
		{
			server = new ACIServer(ui.PortNumber->toPlainText().toInt());
			ServerDataStorage::DDROutputAdd("start-timer", RequestedTimerStart);
			server->ThreadRun();
			ServerRunning = true;
			ui.BtnStart->setText("关闭通信系统");
		}
		break;
	}
	default:
	{
		MessageBox(NULL, L"通信参数错误", L"错误", MB_OK | MB_ICONERROR);
		break;
	}
	}
}

int ACIMode::GetOperationMode()
{
	return OperationMode;
}

void ACIMode::RequestRemoteTimer()
{
	if (client != nullptr)
		client->RequestData("start-timer");
}

void ACIMode::closeEvent(QCloseEvent* event)
{
	this->hide();
	event->ignore();
}

bool ACIMode::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == ui.IP)
	{
		if (event->type() == QEvent::FocusIn)
			ui.IP->grabKeyboard();
	}
	else if (watched == ui.PortNumber)
	{
		if (event->type() == QEvent::FocusIn)
			ui.PortNumber->grabKeyboard();
	}
	return QWidget::eventFilter(watched, event);
}

std::string RequestedTimerStart(std::string json)
{
	GlobalVari::ServerRequested = true;
	return "successed";
}
