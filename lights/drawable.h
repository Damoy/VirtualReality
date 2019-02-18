// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// 2017_2018
//
// Correction TP3
// -------------
// Updated by FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QMessageBox>

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include "camera.h"
#include "light.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

class Drawable: public QOpenGLFunctions
{
public:
    Drawable();
    virtual ~Drawable();
    virtual void initializeVAO() = 0;
    virtual void draw() = 0;

    // is object transformation matrix
    virtual QMatrix4x4 world() = 0;

    void initializeShader(QString vs, QString fs);

    /** Set drawable's position */
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    /** Add inquired values to drawable's rotation */
    void rotateOf(GLfloat roulis, GLfloat tangage, GLfloat lacet);
    /** Set drawable's rotation to inquired values */
    void setOrientation(GLfloat roulis, GLfloat tangage, GLfloat lacet);

    Camera *camera() const;
    /** Set drawable's camera */
    void setCamera(Camera *camera);

    Light *light() const;
    void setLight(Light *light);

protected:
    // opengl
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;

    // world
    Camera* m_camera;
    QVector3D m_position;
    GLfloat m_roulis, m_tangage, m_lacet;
    Light* m_light;
};

#endif // DRAWABLE_H
