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


    // Dibujar aristas
    painter.setPen(QPen(Qt::black)); // Escogemos el color y la anchura de la linea
    if(!puntosEnvolventeConvexa.empty()) { // Si la lista de puntos de la envolvente convexa esta vacia no hacemos nada

        // Definimos el primer punto de la lista
        QPoint primerPunto(
            static_cast<int>(puntosEnvolventeConvexa.first().x()),
            static_cast<int>(puntosEnvolventeConvexa.first().y())
        );

        QPoint puntoAnterior = primerPunto;

        // Recorremos punto a punto y dibujamos una linea entre el punto anterior y el punto actual
        for(int i = 1; i < puntosEnvolventeConvexa.size(); ++i) {
            QPoint puntoActual(
                static_cast<int>(puntosEnvolventeConvexa.at(i).x()),
                static_cast<int>(puntosEnvolventeConvexa.at(i).y())
            );

            painter.drawLine(puntoAnterior, puntoActual);

            puntoAnterior = puntoActual;
        }

        // Dibujamos una linea entre el ultimo punto y el primero de la lista para cerrar la envolvente
        painter.drawLine(puntoAnterior, primerPunto);

    }

    painter.end();
    QWidget::paintEvent(event);
}
