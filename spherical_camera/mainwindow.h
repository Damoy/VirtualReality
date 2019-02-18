#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cube.h"
#include "cubeTex.h"
#include "deAJouer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    /** Create a new colored cube */
    void createColoredCube();
    /** Create a new textured cube */
    void createTexturedCube();
    /** Create de */
    void createDeAJouer();
};

#endif // MAINWINDOW_H
