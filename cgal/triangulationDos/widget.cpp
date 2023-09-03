#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // Creacion del menu y la accion showInfo
    boxLayout = new QVBoxLayout(this); // Main layout del widget
    menuBar = new QMenuBar();
    helpMenu = new QMenu("Menu");
    showInfoAction = new QAction("Show Info", this);
    menuBar->addMenu(helpMenu);
    helpMenu->addAction(showInfoAction);
    this->layout()->setMenuBar(menuBar);

    connect(showInfoAction, SIGNAL(triggered()), this, SLOT(showInfo()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showInfo()
{
    QString title = "Ayuda";
    QString text = "Al dar click sobre la ventana de esta aplicación se agregaran puntos y se mostrará la correspondiente triangulación de Delaunay";
    QMessageBox::information(this, title, text);
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    t.push_back(Point(event->pos().x(),event->pos().y()));
    repaint();
    qDebug() <<"Number of vertices:" << t.number_of_vertices();

    QWidget::mousePressEvent(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush(Qt::blue);
    for(Finite_edges_iterator fei=t.finite_edges_begin(); fei != t.finite_edges_end(); ++fei){
        //painter.drawLine(t.segment(fei)[0].x(),t.segment(fei)[0].y(),t.segment(fei)[1].x(),t.segment(fei)[1].y());
        painter.drawLine(fei->first->vertex(((fei->second)+1)%3)->point().x(),t.segment(fei)[0].y(),t.segment(fei)[1].x(),t.segment(fei)[1].y());
    }
    Point q;
    for(Point_iterator it=t.points_begin(); it != t.points_end(); ++it){
        q=it.operator *();
        painter.drawEllipse(q.x()-5,q.y()-5,10,10);
    }

    painter.end();
    QWidget::paintEvent(event);
}
