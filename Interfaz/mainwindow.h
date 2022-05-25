#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPaintEngine>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

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

private:
    Ui::MainWindow *ui;
    int anchoPointsToDraw[100];
    int altoPointsToDraw[100];
    bool actualizar = false;
    QPen lapicero;

protected:
    void paintEvent(QPaintEvent* e);

};

#endif // MAINWINDOW_H
