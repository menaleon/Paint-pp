#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <PixelMatrix.h>
#include <Pixel.h>
#include <bmp.h>


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
    //ui->label_canvas->clear();

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

    //ui->label_canvas->show();
    //ui->label_canvas->move(0,0);
    //ui->label_canvas->resize(ancho,alto);
    ui->label_canvas->setText("Soy un canvas (label gigante)");
    ui->label_canvas->setStyleSheet("QLabel { background-color : lightblue; color : black; }");
    pMatrix = new PixelMatrix(ancho, alto);

    //obtener datos de los pixeles y guardarlos en un pixArray

    int i = 0;
    for(int n=0;n<101;n++){

        anchoPointsToDraw[i]=n;
        altoPointsToDraw[i]=n+10;
        i++;

    }

    actualizar = true;
    undo = false;
    update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    PixelMatrix *pMatrixToUse = NULL;
    if(actualizar){
        if (zoom==true)
        {
            pMatrixToUse = pMatrixZoom;
        } else
        {
            pMatrixToUse = pMatrix;
        }
        int w = pMatrixToUse->getWidth();
        int h = pMatrixToUse->getHeight();
        ui->label_canvas->clear();
        ui->label_canvas->show();
        ui->label_canvas->move(0,0);
        ui->label_canvas->resize(w,h);
        QPixmap pix(w, h);
        QPen lapicero;
        lapicero.setWidth(1);
        QPainter paint(&pix);

        for(int i =0;i<h;i++){
            for(int j=0;j<w;j++){
                Pixel p = pMatrixToUse->getPixel(j,i);
                lapicero.setColor(QColor(p.getR(), p.getG(), p.getB(), p.getA()));
                paint.setPen(lapicero);
                paint.drawPoint(QPoint(j,i));
            }
        }
        ui->label_canvas->setPixmap(pix);
    }

}

void MainWindow::on_actionFiltro1_triggered()
{
    if (pMatrix != NULL) {
        pMatrixOld = pMatrix->clone();
        pMatrix->applyNegativeFilter();
        undo = false;
    }
}

void MainWindow::on_actionFiltro2_triggered()
{
    if (pMatrix != NULL) {
        pMatrixOld = pMatrix->clone();
        pMatrix->applyGrayFilter();
        undo = false;
    }
}

void MainWindow::on_actionFiltro3_triggered()
{
    if (pMatrix != NULL) {
        pMatrixOld = pMatrix->clone();
        pMatrix->applySepiaFilter();
        undo = false;
    }
}

void MainWindow::on_actionAbrir_bmp_triggered()
{
    if (pMatrix != NULL) {
        pMatrixOld = pMatrix->clone();
    }
    BMP bmp("/home/gabriel/Paintpp/sample.bmp");
    int h = bmp.get_height();
    int w = bmp.get_width();
    ui->label_canvas->clear();
    ui->label_canvas->show();
    ui->label_canvas->move(0,0);
    ui->label_canvas->resize(w,h);
    pMatrix = new PixelMatrix(w, h);
    actualizar = true;

    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            int R = bmp.get_pixelR(j,i);
            int G = bmp.get_pixelG(j,i);
            int B = bmp.get_pixelB(j,i);
            int A = bmp.get_pixelA(j,i);
            Pixel *p = new Pixel(R,G,B,A);
            pMatrix->setPixel(j,h-i-1,*p);
        }
    }
    undo = false;
}

void MainWindow::on_actionGuardar_bmp_triggered()
{
    int w = pMatrix->getWidth();
    int h = pMatrix->getHeight();
    BMP bmp(w,h,true);

    for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                Pixel p = pMatrix->getPixel(j,i);
                bmp.set_pixel(j,h-i-1,p.getB(),p.getG(),p.getR(),p.getA());
            }
        }
    bmp.write("/home/gabriel/Paintpp/sample.bmp");
}

void MainWindow::on_actionRotar_180_triggered()
{
    if (zoom == true) {
        zoom = false;
    }
    else {
        pMatrixZoom = pMatrix->zoom();
        zoom = true;
    }
}

void MainWindow::on_actionDeshacer_triggered()
{
    if (pMatrixOld != NULL) {
        PixelMatrix* temp = pMatrixOld->clone();
        pMatrixOld = pMatrix->clone();
        pMatrix = temp->clone();
        undo = true;
    }
}

void MainWindow::on_actionRehacer_triggered()
{
    if (undo == true && pMatrixOld != NULL) {
        PixelMatrix* temp = pMatrixOld->clone();
        pMatrixOld = pMatrix->clone();
        pMatrix = temp->clone();
        undo = false;
    }
}
