#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_alto->hide();
    ui->label_ancho->hide();
    ui->label_tamanio->hide();
    ui->boton_crear->hide();
    ui->ancho->hide();
    ui->alto->hide();
    ui->label_canvas->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCrear_canvas_triggered()
{
    ui->label_alto->show();
    ui->label_ancho->show();
    ui->label_tamanio->show();
    ui->boton_crear->show();
    ui->ancho->show();
    ui->alto->show();

}

void MainWindow::on_boton_crear_clicked()
{
    ui->label_canvas->clear();

    int ancho = ui->ancho->text().toInt();
    int alto = ui->alto->text().toInt();

    ui->label_alto->hide();
    ui->label_ancho->hide();
    ui->label_tamanio->hide();
    ui->boton_crear->hide();
    ui->ancho->clear();
    ui->alto->clear();
    ui->ancho->hide();
    ui->alto->hide();

    ui->label_canvas->show();
    ui->label_canvas->move(0,0);
    ui->label_canvas->resize(ancho,alto);
    ui->label_canvas->setText("Soy un canvas (label gigante)");
    ui->label_canvas->setStyleSheet("QLabel { background-color : lightblue; color : black; }");

    //obtener datos de los pixeles y guardarlos en un pixArray

    int i = 0;
    for(int n=0;n<101;n++){

        anchoPointsToDraw[i]=n;
        altoPointsToDraw[i]=n+10;
        i++;

    }

    actualizar = true;
    update();

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    if(actualizar){
        int h = ui->label_canvas->height();
        int w = ui->label_canvas->width();

        QPixmap pix(w, h);
        pix.fill( Qt::blue);

        lapicero.setColor(QColor(255, 255, 255, 255));
        lapicero.setWidth(1);

        QPainter paint(&pix);
        paint.setPen(lapicero);

        for(int n=0;n<101;n++){
            paint.drawPoint(QPoint(n,n));

        }

        ui->label_canvas->setPixmap(pix);
    }

}


