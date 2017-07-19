#ifndef CWINDOW_H
#define CWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>

class CWindow : public QDialog
{
    Q_OBJECT

    public slots:
        void updateData();

    public:
        CWindow(QWidget *parent = 0);
        virtual ~CWindow();

    private:
        QGraphicsScene* m_scene;
        QGraphicsView* m_view;
        QGraphicsTextItem* m_statsInfo;
        QGraphicsTextItem* m_softInfo;
};

#endif
