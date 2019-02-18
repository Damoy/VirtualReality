#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cube.h"
#include "cubeTex.h"
#include "deAJouer.h"
#include "cubeeclaire.h"
#include "light.h"
#include "QColorDialog.h"

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
//    /** Create a new colored cube */
//    void createColoredCube();
//    /** Create a new textured cube */
//    void createTexturedCube();
//    /** Create de a jouer */
//    void createDeAJouer();
//    /** Create enlightened cube */
//    void createEnlightenedCube();
//    /** Create plane */
//    void createPlane();
//    /** Change Ambient Light */
//    void changeAmbientLight();
//    /** Change Diffuse Light */
//    void changeDiffuseLight();
//    /** Change Specular Light */
//    void changeSpecularLight();
//    /** Change light position */
//    void changeLightPosition();
//    /** Change specular reflection coefficient */
//    void changeSpecularReflectionCoefficient();
};

#endif // MAINWINDOW_H
