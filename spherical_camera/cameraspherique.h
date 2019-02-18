#ifndef CAMERASPHERIQUE_H
#define CAMERASPHERIQUE_H

#include "camera.h"

class CameraSpherique : public Camera
{
public:
    CameraSpherique();

    GLfloat rho() const;
    void setRho(const GLfloat &rho);

    GLfloat theta() const;
    void setTheta(const GLfloat &theta);

    GLfloat phi() const;
    void setPhi(const GLfloat &phi);

    QVector3D spheriqueTarget() const;
    void setSpheriqueTarget(const QVector3D &spheriqueTarget);

    // override
    void setPosition(const QVector3D &position);

private:
    // distance camera - target
    GLfloat m_rho;
    // angles
    GLfloat m_theta;
    GLfloat m_phi;
    // the target
    QVector3D m_spheriqueTarget;

    void update_position();
};

#endif // CAMERASPHERIQUE_H
