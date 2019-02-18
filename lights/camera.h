// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QtGui>
#include <iostream>

class Camera {

public:
    Camera();
    /** Create a view matrix */
    QMatrix4x4 view();
    /** Create a projection matrix */
    QMatrix4x4 projection();

    // -- getters / setters --
    GLfloat fov() const;
    void setFov(GLfloat fov);

    GLfloat aspect_ratio() const;
    void setAspect_ratio(GLfloat aspect_ratio);

    GLfloat zmin() const;
    void setZmin(GLfloat zmin);

    GLfloat zmax() const;
    void setZmax(GLfloat zmax);

    QVector3D position() const;
    virtual void setPosition(const QVector3D &position);

    QVector3D target() const;
    void setTarget(const QVector3D &target);

    QVector3D up() const;
    void setUp(const QVector3D &up);

protected:
    // projection-related
    GLfloat m_fov;
    GLfloat m_aspect_ratio;
    GLfloat m_zmin;
    GLfloat m_zmax;

    // view-related
    QVector3D m_position;
    QVector3D m_target;
    QVector3D m_up;
};

#endif // CAMERA_H
