#ifndef CAMERASPHERIQUE_H
#define CAMERASPHERIQUE_H

#include "camera.h"

class CameraSpherique : public Camera
{
public:
    CameraSpherique();
    ~CameraSpherique();

    GLfloat rho() const;
    void setRho(const GLfloat &rho);

    GLfloat theta() const;
    void setTheta(const GLfloat &theta);

    GLfloat phi() const;
    void setPhi(const GLfloat &phi);

    void update_position();

    // override
    void setPosition(const QVector3D &position);

private:
    // distance camera - target
    GLfloat m_rho;
    GLfloat m_theta;
    GLfloat m_phi;
};

#endif // CAMERASPHERIQUE_H
