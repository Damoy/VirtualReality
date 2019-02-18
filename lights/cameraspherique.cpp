#include "cameraspherique.h"

CameraSpherique::CameraSpherique()
    : Camera::Camera(){
    m_rho = 10;
    m_phi = 0.0f;
    m_theta = 0.0f;
    m_spheriqueTarget = QVector3D(0.0f, 0.0f, 0.0f);
    update_position();
}

GLfloat CameraSpherique::rho() const
{
    return m_rho;
}

void CameraSpherique::setRho(const GLfloat &rho)
{
    if(rho > 0) {
        m_rho = rho;
        update_position();
    }
}

GLfloat CameraSpherique::theta() const
{
    return m_theta;
}

void CameraSpherique::setTheta(const GLfloat &theta)
{
    m_theta = theta;
    update_position();
}

GLfloat CameraSpherique::phi() const
{
    return m_phi;
}

void CameraSpherique::setPhi(const GLfloat &phi)
{
    if(phi > -M_PI_2 && phi < M_PI_2){
        m_phi = phi;
        update_position();
    }
}

QVector3D CameraSpherique::spheriqueTarget() const
{
    return m_spheriqueTarget;
}

void CameraSpherique::setSpheriqueTarget(const QVector3D &spheriqueTarget)
{
    m_spheriqueTarget = spheriqueTarget;
}

void CameraSpherique::update_position(){
    GLfloat x = m_spheriqueTarget.x() + (m_rho * qCos(m_phi) * qCos(m_theta));
    GLfloat y = m_spheriqueTarget.y() + (m_rho * qSin(m_phi));
    GLfloat z = m_spheriqueTarget.z() + (m_rho * qCos(m_phi) * qSin(m_theta));
    Camera::m_position.setX(x);
    Camera::m_position.setY(y);
    Camera::m_position.setZ(z);
}

void CameraSpherique::setPosition(const QVector3D &position){
    m_position = position;
    update_position();
}
