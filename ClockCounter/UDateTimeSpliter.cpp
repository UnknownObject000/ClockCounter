#include "UDateTimeSpliter.h"

UDateTimeSpliter::UDateTimeSpliter(QWidget* parent) : QWidget(parent)
{
	ItemType = Type::Empty;
	TextColor1 = QColor(100, 184, 255, 255);
	TextColor2 = QColor(79, 148, 205, 255);
	Background1 = QColor(100, 100, 100, 255);
	Background2 = QColor(60, 60, 60, 255);
	return;
}

UDateTimeSpliter::Triangle UDateTimeSpliter::GetTriangle(QPoint start, bool left, int xsize, int ysize)
{
	QPolygon triangle;
	int y_half = ysize / 2;
	QPoint top((left ? start.x() + xsize : start.x() - xsize), start.y() + y_half);
	QPoint bottom((left ? start.x() + xsize : start.x() - xsize), start.y() - y_half);
	triangle.setPoints(3, start.x(), start.y(), top.x(), top.y(), bottom.x(), bottom.y());
	QRect equ_rect(QPoint(start.x(), top.y()), bottom);
	return { triangle,equ_rect };
}

void UDateTimeSpliter::setTextColor1(QColor color)
{
	TextColor1 = color;
	return;
}

void UDateTimeSpliter::setTextColor2(QColor color)
{
	TextColor2 = color;
	return;
}

void UDateTimeSpliter::setBackground1(QColor color)
{
	Background1 = color;
	return;
}

void UDateTimeSpliter::setBackground2(QColor color)
{
	Background2 = color;
	return;
}

void UDateTimeSpliter::DrawBackground(QPainter& painter)
{
	QLinearGradient qlg(rect().topLeft(), rect().bottomRight());
	qlg.setColorAt(0, Background1);
	qlg.setColorAt(1, Background2);
	qlg.setSpread(QGradient::PadSpread);
	painter.setBrush(qlg);
	painter.drawRect(rect());
	return;
}

void UDateTimeSpliter::DrawDateSpliter(QPainter& painter)
{
	QPoint text_start(rect().left() + DateSpace, rect().top() + DateSpace);
	QPoint text_end(rect().right() - DateSpace, rect().bottom() - DateSpace);
	QRect text(text_start, text_end);
	QPoint text_y_center_left(text.topLeft().x(), text.topLeft().y() + (text.height() / 2));
	QPoint text_y_center_right(text.topRight().x(), text.topRight().y() + (text.height() / 2));
	Triangle left_triangle = GetTriangle(text_y_center_left, true, DateSpliterTriangleSize, DateSpliterLineSize);
	Triangle right_triangle = GetTriangle(text_y_center_right, false, DateSpliterTriangleSize, DateSpliterLineSize);
	QPolygon full_shape;
	full_shape.setPoints(6, left_triangle.Shape.point(1).x(), left_triangle.Shape.point(1).y(), left_triangle.Shape.point(0).x(), left_triangle.Shape.point(0).y(), left_triangle.Shape.point(2).x(), left_triangle.Shape.point(2).y(), right_triangle.Shape.point(2).x(), right_triangle.Shape.point(2).y(), right_triangle.Shape.point(0).x(), right_triangle.Shape.point(0).y(), right_triangle.Shape.point(1).x(), right_triangle.Shape.point(1).y());
	QLinearGradient linear(left_triangle.EquallyRect.topLeft(), right_triangle.EquallyRect.bottomRight());
	linear.setColorAt(0, TextColor1);
	linear.setColorAt(1, TextColor2);
	linear.setSpread(QGradient::PadSpread);
	painter.setBrush(linear);
	painter.drawPolygon(full_shape);
	return;
}

void UDateTimeSpliter::DrawDotsSpliter(QPainter& painter)
{
	QPoint text_start(rect().left() + DotSpace, rect().top() + DotSpace);
	QPoint text_end(rect().right() - DotSpace, rect().bottom() - DotSpace);
	QRect text(text_start, text_end);
	QPoint dot_center(text.left() + (text.width() / 2), text.bottom() - DotSpace);
	QLinearGradient linear(text.topLeft(), text.bottomRight());
	linear.setColorAt(0, TextColor1);
	linear.setColorAt(1, TextColor2);
	linear.setSpread(QGradient::PadSpread);
	painter.setBrush(linear);
	painter.drawEllipse(dot_center, DotSpliterCircleSize, DotSpliterCircleSize);
	return;
}

void UDateTimeSpliter::DrawTimeSpliter(QPainter& painter)
{
	QPoint text_start(rect().left() + TimeSpace, rect().top() + TimeSpace);
	QPoint text_end(rect().right() - TimeSpace, rect().bottom() - TimeSpace);
	QRect text(text_start, text_end);
	QPoint text_center(text.left() + (text.width() / 2), text.top() + (text.height() / 2));
	QPoint top_circle_center(text_center.x(), text_center.y() + TimeSpliterCircleSpace);
	QPoint bottom_circle_center(text_center.x(), text_center.y() - TimeSpliterCircleSpace);
	QLinearGradient linear(text.topLeft(), text.bottomRight());
	linear.setColorAt(0, TextColor1);
	linear.setColorAt(1, TextColor2);
	linear.setSpread(QGradient::PadSpread);
	painter.setBrush(linear);
	painter.drawEllipse(top_circle_center, TimeSpliterCircleSize, TimeSpliterCircleSize);
	painter.drawEllipse(bottom_circle_center, TimeSpliterCircleSize, TimeSpliterCircleSize);
	return;
}

void UDateTimeSpliter::Init(Type type, QColor tc1, QColor tc2, QColor bg1, QColor bg2)
{
	ItemType = type;
	if (tc1 != QColor())
		TextColor1 = tc1;
	if (tc2 != QColor())
		TextColor2 = tc2;
	if (bg1 != QColor())
		Background1 = bg1;
	if (bg2 != QColor())
		Background2 = bg2;
	return;
}

void UDateTimeSpliter::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//设置抗锯齿
	painter.setPen(Qt::NoPen);
	DrawBackground(painter);
	if (ItemType == Type::Date)
		DrawDateSpliter(painter);
	else if (ItemType == Type::Time)
		DrawTimeSpliter(painter);
	else if (ItemType == Type::Dots)
		DrawDotsSpliter(painter);
	return;
}