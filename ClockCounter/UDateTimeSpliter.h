#pragma once
#include <QWidget.h>
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QLinearGradient>
#include <QPolygon>

class UDateTimeSpliter : public QWidget
{
	Q_OBJECT;
public:
	enum class Type
	{
		Date,
		Dots,
		Time,
		Empty
	};

	struct Triangle
	{
		QPolygon Shape;
		QRect EquallyRect;
	};
private:
	Type ItemType;
	QColor TextColor1;
	QColor TextColor2;
	QColor Background1;
	QColor Background2;
	const int DotSpace = 14;
	const int DateSpace = 20;
	const int TimeSpace = 20;
	const int DateSpliterLineSize = 10;
	const int DotSpliterCircleSize = 6;
	const int TimeSpliterCircleSize = 7;
	const int TimeSpliterCircleSpace = 25;
	const int DateSpliterTriangleSize = 6;
private:
	Triangle GetTriangle(QPoint start, bool left, int xsize, int ysize);
	void DrawBackground(QPainter& painter);
	void DrawDateSpliter(QPainter& painter);
	void DrawDotsSpliter(QPainter& painter);
	void DrawTimeSpliter(QPainter& painter);
public:
	UDateTimeSpliter(QWidget* parent = nullptr);
public:
	void Init(Type type, QColor tc1 = QColor(), QColor tc2 = QColor(), QColor bg1 = QColor(), QColor bg2 = QColor());
	void setTextColor1(QColor color);
	void setTextColor2(QColor color);
	void setBackground1(QColor color);
	void setBackground2(QColor color);
protected:
	virtual void paintEvent(QPaintEvent* event) override;
};

