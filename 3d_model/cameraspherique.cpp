#include "cameraspherique.h"

CameraSpherique::CameraSpherique()
    : Camera::Camera(){
    m_rho = 0.0f;
    m_phi = 0.0f;
    m_theta = 0.0f;
    update_position();
}

CameraSpherique::~CameraSpherique(){

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

void CameraSpherique::update_position(){
    GLfloat x = m_target.x() + (m_rho * qCos(m_phi) * qCos(m_theta));
    GLfloat y = m_target.y() + (m_rho * qSin(m_phi)); // m_theta ?
    GLfloat z = m_target.z() + (m_rho * qCos(m_phi) * qSin(m_theta));
    Camera::m_position.setX(x);
    Camera::m_position.setY(y);
    Camera::m_position.setZ(z);
}

void CameraSpherique::setPosition(const QVector3D &position){
    m_position = position;
    update_position();
}
