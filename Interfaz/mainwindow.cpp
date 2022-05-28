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
/*
    if (pMatrix != NULL) {
        pMatrixOld = pMatrix->clone();
        pMatrix = pMatrix->flipY();
        undo = false;
    }
*/
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
        zoom = false;
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

void MainWindow::on_actionRotar_90_triggered()
{
    if (pMatrix != NULL) {
        pMatrixOld = pMatrix->clone();
        pMatrix = pMatrix->rotate90();
        undo = false;
    }
}

void MainWindow::on_actionRectangulo_triggered()
{
    if (pMatrix != NULL) {
        int w = pMatrix->getWidth();
        int h = pMatrix->getHeight();
        pMatrixOld = pMatrix->clone();

        Pixel *p = new Pixel(0,0,0,255);
        int x1 = w/4;
        int y1 = h/4;
        int x2 = w*3/4;
        int y2 = h*3/4;
        pMatrix->drawLine(x1,y1,x2,y1, *p);
        pMatrix->drawLine(x1,y1,x1,y2, *p);
        pMatrix->drawLine(x2,y1,x2,y2, *p);
        pMatrix->drawLine(x1,y2,x2,y2, *p);

        undo = false;
    }
}

void MainWindow::on_actionTriangulo_triggered()
{
    if (pMatrix != NULL) {
        int w = pMatrix->getWidth();
        int h = pMatrix->getHeight();
        pMatrixOld = pMatrix->clone();
        Pixel *p = new Pixel(0,0,0,255);
        int x1 = w/4;
        int y1 = h*3/4;
        int x2 = w/2;
        int y2 = h/4;
        int x3 = w*3/4;
        int y3 = h*3/4;
        pMatrix->drawLine(x1,y1,x2,y2, *p);
        pMatrix->drawLine(x2,y2,x3,y3, *p);
        pMatrix->drawLine(x1,y1,x3,y3, *p);
        undo = false;
    }
}

void MainWindow::on_actionCirculo_triggered()
{
    if (pMatrix != NULL) {
        int w = pMatrix->getWidth();
        int h = pMatrix->getHeight();
        pMatrixOld = pMatrix->clone();
        Pixel *p = new Pixel(0,0,0,255);
        int x1 = w/2;
        int y1 = h/2;
        int r = w/4;
        if (w>h){
            r = h/4;
        }
        pMatrix->drawCircle(x1,y1,r, *p);
        undo = false;
    }
}
