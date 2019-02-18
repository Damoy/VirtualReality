// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19
// -------------
// Updated by FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QtGui>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QTimer>

#include <iostream>
#include "cameraspherique.h"
#include "cube.h"
#include "cubetex.h"
#include "cubeeclaire.h"
#include "deAJouer.h"
#include "model.h"
#include "light.h"
#include "skybox.h"
#include "plan.h"
#include "avion.h"

using namespace std;

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private slots:
    /** Update the application */
    void update();

public:
    WidgetOpenGL(QWidget* parent = nullptr);
    ~WidgetOpenGL();

    Light *light() const;
    void setLight(Light *light);

    Plan *plan() const;
    void setPlan(Plan *plan);

    Avion *avion() const;
    void setAvion(Avion *avion);
    void keyPressEvent(QKeyEvent *event);

    /** Change the fov value by the one provided */
    void changeFov(int value);

protected:
    /** Initialize GL capabilities */
    void initializeGL();
    /** Resize GL window */
    void resizeGL(int width, int height);
    /** Render method */
    void paintGL();

private:
    // used to keep mouse event position
    QPoint lastPos;

    // opengl
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    // world
    CameraSpherique* m_camera;
    Light* m_light;
    Plan* m_plan;
    Avion* m_avion;
};

#endif // WIDGETOPENGL_H
