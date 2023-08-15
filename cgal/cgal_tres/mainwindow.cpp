#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    puntos.append(Point_2(event->pos().x(),event->pos().y()));
    puntosEnvolventeConvexa.clear();
    CGAL::convex_hull_2(puntos.begin(),puntos.end(),std::back_inserter(puntosEnvolventeConvexa));
    repaint();
    QWidget::mousePressEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush(Qt::blue);
    Point_2 q;
    Point_2 r;
    for(QList<Point_2>::iterator it=puntos.begin(); it != puntos.end(); ++it){
        q=it.operator *();
        painter.drawEllipse(q.x()-5,q.y()-5,10,10);
    }
    painter.setBrush(Qt::red);
    for(QList<Point_2>::iterator it=puntosEnvolventeConvexa.begin(); it != puntosEnvolventeConvexa.end(); ++it){
        q=it.operator *();
        painter.drawEllipse(q.x()-5,q.y()-5,10,10);
    }
    painter.end();
    QWidget::paintEvent(event);
}
