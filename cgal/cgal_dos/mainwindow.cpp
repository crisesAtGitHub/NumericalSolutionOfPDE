#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Vertex_handle va = cdt.insert(Point(40,40));
    Vertex_handle vb = cdt.insert(Point(440,40));
    Vertex_handle vc = cdt.insert(Point(440,440));
    Vertex_handle vd = cdt.insert(Point(40,440));
    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);

    Vertex_handle ve= cdt.insert(Point(80,120));
    Vertex_handle vf= cdt.insert(Point(160,240));
    cdt.insert_constraint(ve, vf);
    cdtPivote=cdt;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(recalcular()));
    connect(ui->actionInformaci_n, SIGNAL(triggered()), this, SLOT(showInfo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showInfo()
{
    QString title = "Información";
    QString message = "Este programa calcula una malla";
    QMessageBox::information(this, title, message);
}

void MainWindow::recalcular()
{
    cdtPivote=cdt;
    CGAL::refine_Delaunay_mesh_2(cdtPivote, Criteria(0.125,ui->spinBox->value()));
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::white);
//    for(CDT::Finite_vertices_iterator
//          vit = cdt.finite_vertices_begin(),
//          end = cdt.finite_vertices_end();
//          vit!= end; ++vit)
//      {
//            painter.drawEllipse(vit->point().x(),vit->point().y(),10,10);
//      }
    for(CDT::Finite_edges_iterator
          eit = cdtPivote.finite_edges_begin(),
          end = cdtPivote.finite_edges_end();
          eit!= end; ++eit)
      {
            CDT::Segment seg = cdtPivote.segment( *eit );

            CDT::Point p0 = seg.point(0);
            CDT::Point p1 = seg.point(1);
            painter.drawLine(p0.x(),p0.y(),p1.x(),p1.y());
      }
    painter.setPen(Qt::red);
    painter.drawLine(80,120,160,240);
}
