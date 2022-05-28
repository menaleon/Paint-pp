#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPaintEngine>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <PixelMatrix.h>
#include <Pixel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCrear_canvas_triggered();

    void on_boton_crear_clicked();

    void on_actionFiltro1_triggered();

    void on_actionFiltro2_triggered();

    void on_actionFiltro3_triggered();

    void on_actionAbrir_bmp_triggered();

    void on_actionGuardar_bmp_triggered();

    void on_actionRotar_180_triggered();

    void on_actionDeshacer_triggered();

    void on_actionRehacer_triggered();

private:
    Ui::MainWindow *ui;
    int anchoPointsToDraw[100];
    int altoPointsToDraw[100];
    bool actualizar = false;
    bool zoom = false;
    bool undo = false;
    PixelMatrix* pMatrix = NULL;
    PixelMatrix* pMatrixOld = NULL;
    PixelMatrix* pMatrixZoom = NULL;

protected:
    void paintEvent(QPaintEvent* e);

};

#endif // MAINWINDOW_H
