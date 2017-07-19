#include <QWidget>
#include <QTimer>
#include <QPointF>
#include <random>
#include <cmath>
#include <iostream>
#include "window.h"

namespace {
	const qreal off_x = 500, off_y = 10, leng = 700, dot_size = 1;

	const QPointF t_points[] = {
		{ off_x, off_y },
		{ off_x + leng / 2, off_y + leng * std::sqrt(3) / 2 },
		{ off_x - leng / 2, off_y + leng * std::sqrt(3) / 2 }
	};
	const QPointF start_point(t_points[0]);

	const QColor colors[] = {
		Qt::black,
		Qt::red,
		Qt::green,
		Qt::blue
	};

	const auto TNONE = QTransform();

	uint32_t random_13() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 2);
		return dis(gen);
	}

    uint32_t fibo_13() {
        static uint32_t a1 = 1, a2 = 1;

        uint32_t cur = a1 + a2;
        a1 = a2;
        a2 = cur;
        return cur % 3;
    }
}

CWindow::CWindow(QWidget *parent)
	: QDialog(parent) {

	m_scene = new QGraphicsScene();
	m_view = new QGraphicsView(m_scene);

	m_scene->setSceneRect(0, 0, off_x * 2, off_x * 2);

	m_scene->addRect(t_points[0].x(), t_points[0].y(), dot_size, dot_size);
	m_scene->addRect(t_points[1].x(), t_points[1].y(), dot_size, dot_size);
	m_scene->addRect(t_points[2].x(), t_points[2].y(), dot_size, dot_size);

	m_statsInfo = m_scene->addText("");
    m_statsInfo->setPos(0, 0);
	m_softInfo = m_scene->addText("** Non-threaded, timer-based version **");
    m_softInfo->setPos(0, 60);

	m_view->showMaximized();
	
    QTimer::singleShot(1, this, SLOT(updateData()));
}

void CWindow::updateData() {
	static uint32_t cnt = 0, cnt_dots = 0;
	static QPointF point(start_point);

	auto rnd = random_13();
	auto& px = t_points[rnd];
	point = (point - px) / 2 + px;

	auto pA = m_scene->itemAt(point, TNONE);
	if(!pA) {
		++cnt_dots;
		m_scene->addRect(point.x(),
				point.y(),
				dot_size,
				dot_size,
				QPen(colors[0]),
				QBrush(colors[0]));
	}
	if((++cnt % 10) == 0) {
		m_statsInfo->setPlainText(QString("Iter: ") +
				QString::number(cnt) +
				QString(",  dots: ") +
				QString::number(cnt_dots) +
				QString(",  ") +
				QString::number(cnt_dots * 100 / cnt) +
				QString("%")
				);
	}
	QTimer::singleShot(1, this, SLOT(updateData()));
}

CWindow::~CWindow() {
	delete m_view;
	delete m_scene;
}
