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
#include "skybox.h"
#include "light.h"

using namespace std;

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private slots:
    /** Update the application */
    void update();
    /** Start the cube animation */
    void startAnimation();
    /** Reset the animation **/
    void resetAnimation();
    /** Change the fov value by the one provided */
    void changeFov(int value);
public:
    WidgetOpenGL(QWidget* parent = nullptr);
    ~WidgetOpenGL();

    /** Add a drawable object to widget list */
    void addDrawable(Drawable* drawable);

    Light *light() const;
    void setLight(Light *light);

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

    // animation
    GLboolean animationRunning;
    QTimer* m_timer;
    void updateAnimation();
    void clearAllDrawables();

    // opengl
    QOpenGLBuffer* m_vbo;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    // world
    CameraSpherique* m_camera;
    QList<Drawable*> m_objects;
    Light* m_light;
};

#endif // WIDGETOPENGL_H
