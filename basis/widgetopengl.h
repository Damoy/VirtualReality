// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

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
using namespace std;

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private slots:
    void update();
    void startAnimation();
    void changeFov(int value);
    void changeOpacity(int value);

public:
    WidgetOpenGL(QWidget* parent = nullptr);
    ~WidgetOpenGL();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void initializeVAO();
    void initializeShader();

private:
    // rotation
    GLfloat m_angleX;
    GLfloat m_angleY;
    GLfloat m_angleZ;
    GLfloat m_angleDx;
    GLfloat m_angleDy;
    GLfloat m_angleDz;
    QPoint lastPos;

    // animation
    boolean animationRunning;
    QTimer* m_timer;
    int fov;
    float m_opacity;
    void updateAnimation();
    void resetAnimation();

    // opengl
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // WIDGETOPENGL_H
