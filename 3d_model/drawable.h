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
    virtual void initializeVAO(){}
    virtual void draw(){}

    // is object transformation matrix
    QMatrix4x4 world();

    void initializeShader(QString vs, QString fs);

    /** Set drawable's position */
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setPosition(QVector3D newPosition);

    // roulis pour tourner sur les cotes (roll)
    // (tangage) pitch pour monter / descendre
    // lacet (yaw) changer de direction
    /** Add inquired values to drawable's rotation */
    virtual void rotateOf(GLfloat tangage, GLfloat lacet, GLfloat roulis);
    /** Set drawable's rotation to inquired values */
    void setOrientation(GLfloat tangage, GLfloat lacet, GLfloat roulis);

    virtual Camera *camera() const;
    /** Set drawable's camera */
    virtual void setCamera(Camera *camera);

    Light *light() const;
    void setLight(Light *light);

    float scale() const;
    virtual void setScale(float scale);

    QVector3D position() const;
    GLfloat roulis() const;
    void setRoulis(const GLfloat &roulis);

    GLfloat tangage() const;
    void setTangage(const GLfloat &tangage);

    GLfloat lacet() const;
    void setLacet(const GLfloat &lacet);

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
    float m_scale;
};

#endif // DRAWABLE_H
